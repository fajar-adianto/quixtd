#include "qx_td_message_list_model.h"

#include "qx_td_message_content_factory.h"
#include "qx_td_message_content.h"
#include "qx_td_message_sender_user.h"
#include "qx_td_message_sender_chat.h"
#include "chat/requests/qx_td_report_chat_request.h"
#include "chat/requests/qx_td_search_chat_messages_request.h"
#include "client/qx_td_client.h"
#include "common/qx_td_helpers.h"
#include "requests/qx_td_input_message_content_attachment_caption.h"
#include "requests/qx_td_input_message_content_factory.h"
#include "requests/qx_td_send_message_request.h"
#include "requests/qx_td_send_message_album_request.h"
#include "requests/qx_td_get_chat_history_request.h"
#include "requests/qx_td_edit_message_text_request.h"
#include "requests/qx_td_edit_message_caption_request.h"
#include "requests/content/qx_td_input_message_text.h"
#include "requests/content/qx_td_input_message_video.h"
#include "requests/content/qx_td_input_message_audio.h"
#include "requests/content/qx_td_input_message_document.h"
#include "requests/content/qx_td_input_message_audio.h"
#include "requests/content/qx_td_input_message_contact.h"
#include "requests/content/qx_td_input_message_video.h"
#include "requests/content/qx_td_input_message_location.h"
#include "requests/content/qx_td_input_message_sticker.h"
#include "requests/content/qx_td_input_message_voice_note.h"
#include "requests/qx_td_get_message_link_request.h"
#include "requests/content/qx_td_input_message_photo.h"
#include "requests/qx_td_toggle_message_sender_is_blocked_request.h"
#include "messages/requests/qx_td_view_messages_request.h"
#include "messages/requests/qx_td_delete_messages_request.h"
#include "utils/qx_td_translate_tools.h"
#include "utils/qx_td_await.h"

#include <QJsonArray>
#include <QtPositioning/QGeoCoordinate>
#include <QTimer>

#include <QMediaRecorder>
#include <QMediaCaptureSession>
#include <QAudioInput>
#include <QMediaFormat>
#include <QStandardPaths>

// Global objects
Q_GLOBAL_STATIC(QMediaRecorder, m_voiceNoteRecorder)
Q_GLOBAL_STATIC(QAudioInput, m_audioInput)
Q_GLOBAL_STATIC(QMediaCaptureSession, m_captureSession)

//Q_GLOBAL_STATIC(QAudioRecorder, m_voiceNoteRecorder)

QxTdMessageListModel::QxTdMessageListModel(QObject *parent)
    : QObject(parent)
    , m_model(nullptr)
    , m_chat(nullptr)
    , m_messageHandler(nullptr)
    , m_jumpToMessageId(0)
    , m_highlightJumpedMessage(false)
    , m_isHandleUpdateLastChatMessageConnected(false)
    , m_mediaSizeExtractor(new QxTdMediaSizeExtractor(this))
{
    m_model = new QxTdObjectListModel<QxTdMessage>(this, "", "id");
    connect(QxTdClient::instance(), &QxTdClient::messages, this, &QxTdMessageListModel::handleMessages);
    connect(QxTdClient::instance(), &QxTdClient::updateMessageSendStatus, this, &QxTdMessageListModel::handleUpdateMessageSendStatus);
    connect(QxTdClient::instance(), &QxTdClient::updateMessageContent, this, &QxTdMessageListModel::handleUpdateMessageContent);
    connect(QxTdClient::instance(), &QxTdClient::updateDeleteMessages, this, &QxTdMessageListModel::handleUpdateDeleteMessages);
    connect(QxTdClient::instance(), &QxTdClient::updateMessageEdited, this, &QxTdMessageListModel::handleUpdateMessageEdited);
    connect(QxTdClient::instance(), &QxTdClient::updateFileGenerationStart, this, &QxTdMessageListModel::handleUpdateFileGenerationStart);
    connect(QxTdClient::instance(), &QxTdClient::updateFileGenerationStop, this, &QxTdMessageListModel::handleUpdateFileGenerationStop);
    connect(QxTdClient::instance(), &QxTdClient::updateMessageInteractionInfo, this, &QxTdMessageListModel::handleUpdateMessageInteractionInfo);
    connect(QxTdClient::instance(), &QxTdClient::messageLink, this, &QxTdMessageListModel::handleRequestMessageLinkCompleted);

    // Setup recorder if not already initialized
    if (m_voiceNoteRecorder->outputLocation().isEmpty()) {
        // Attach audio input to capture session
        m_captureSession->setAudioInput(m_audioInput);
        m_captureSession->setRecorder(m_voiceNoteRecorder);

        // Configure media format
        QMediaFormat format;
        format.setFileFormat(QMediaFormat::Ogg);
        format.setAudioCodec(QMediaFormat::AudioCodec::Opus);
        m_voiceNoteRecorder->setMediaFormat(format);

        // Quality & encoding mode
        m_voiceNoteRecorder->setQuality(QMediaRecorder::HighQuality);
        m_voiceNoteRecorder->setEncodingMode(QMediaRecorder::ConstantQualityEncoding);

        // Volume (now on the input, not the recorder)
        m_audioInput->setVolume(1.0);

        // Output file
        QString path = QStandardPaths::writableLocation(QStandardPaths::CacheLocation) + "/ok.ogg";
        m_voiceNoteRecorder->setOutputLocation(QUrl::fromLocalFile(path));
    }
}

QxTdChat *QxTdMessageListModel::chat() const
{
    return m_chat;
}

QObject *QxTdMessageListModel::qmlModel() const
{
    return m_model;
}

bool QxTdMessageListModel::isUpToDateAndFollowing() const
{
    return m_isHandleUpdateLastChatMessageConnected;
}

bool QxTdMessageListModel::hasNewer() const
{
    if (m_model->isEmpty())
    {
        return false;
    }

    // when setting messages read, model is already up to date, but hasUnreadMessages still true
    bool hasUnread = m_chat->hasUnreadMessages();

    // this fails if the first message is a date label, which actually should never be the case
    bool lastMessageVisible = m_chat->lastMessage()->id() == m_model->first()->id();

    return hasUnread || !lastMessageVisible;
}

void QxTdMessageListModel::setChat(QxTdChat *chat)
{
    if (m_chat == chat && chat && chat->isOpen())
        return;
    if (m_chat)
    {
        disconnect(m_chat, &QxTdChat::closed, this, &QxTdMessageListModel::cleanUp);
    }

    if (!m_model->isEmpty())
    {
        cleanUp();
    }

    m_chat = chat;
    emit chatChanged(m_chat);

    if (!m_chat) {
        return;
    }

    connect(m_chat, &QxTdChat::closed, this, &QxTdMessageListModel::cleanUp);
    m_highlightJumpedMessage = false;
    if (m_chat->hasUnreadMessages()) {
        m_jumpToMessageId = m_chat->lastReadInboxMessageId();
        m_messageHandler = &jumpToWindowMessageHandler;
        loadMessages(m_chat->lastReadInboxMessageId(), MESSAGE_LOAD_WINDOW / 2, MESSAGE_LOAD_WINDOW / 2);
    } else {
        m_messageHandler = &olderMessagesHandler;
        std::unique_ptr<QxTdMessage> lastMessage(new QxTdMessage());
        lastMessage->unmarshalJson(m_chat->lastMessageJson());
        loadMessages(lastMessage->id(), MESSAGE_LOAD_WINDOW, 1);
        connect(QxTdClient::instance(), &QxTdClient::updateChatLastMessage, this, &QxTdMessageListModel::handleUpdateChatLastMessage);
    }
    m_chat->openChat();
}

void QxTdMessageListModel::loadNewer()
{
    if (!m_chat) {
        return;
    }
    //This is to avoid loading messages when messages list is at the bottom (latest message shown)
    //and user scrolls down
    if (isUpToDateAndFollowing()) {
        return;
    }
    if (m_messageHandler) {
        return;
    }
    m_messageHandler = &newerMessagesHandler;
    loadMessages(m_model->first()->id(), 0, MESSAGE_LOAD_WINDOW);
}

void QxTdMessageListModel::loadOlder()
{
    if (!m_chat) {
        return;
    }
    if (m_messageHandler) {
        return;
    }
    m_messageHandler = &olderMessagesHandler;
    loadMessages(m_model->last()->id(), MESSAGE_LOAD_WINDOW, 0);
}

void QxTdMessageListModel::cleanUp()
{
    m_isHandleUpdateLastChatMessageConnected = false;
    disconnect(QxTdClient::instance(), &QxTdClient::updateChatLastMessage, this, &QxTdMessageListModel::handleUpdateChatLastMessage);
    if (m_model->isEmpty()) {
        return;
    }
    m_model->clear();
}

void QxTdMessageListModel::handleMessages(const QJsonObject &json)
{
    QJsonArray messages = json["messages"].toArray();
    if (messages.count() == 0) {
        if (m_model->count() > 0 && m_model->last()->id() != 0) {
            auto dateMessage = getDateLabelIfNeeded(m_model->last(), nullptr);
            if (dateMessage) {
                m_model->append(dateMessage);
            }
        }
        m_messageHandler = nullptr;
        return;
    }

    if (!m_messageHandler) {
        return;
    }

    m_messageHandler->handle(*this, messages);

    emit modelChanged();

    if (m_model->count() < MESSAGE_LOAD_WINDOW) {
        m_messageHandler = &olderMessagesHandler;
        qint64 lastValidMessageId;
        auto i = m_model->count() - 1;
        do {
            lastValidMessageId = m_model->at(i)->id();
        } while (--i > 0 && lastValidMessageId == 0);
        loadMessages(lastValidMessageId, MESSAGE_LOAD_WINDOW, 0);
    } else {
        m_messageHandler = nullptr;
    }

    //When user jumped to an old message and the current view does not contain latest message
    //we don't want to enter this if block, otherwise scrolling down would not load messages
    //and messages list would be stuck in a wrong state.
    //hasNewer will tell if that is the case returning true when latest message is not in current messages list
    if (!hasNewer() && !m_isHandleUpdateLastChatMessageConnected) {
        connect(QxTdClient::instance(), &QxTdClient::updateChatLastMessage, this, &QxTdMessageListModel::handleUpdateChatLastMessage);
        m_isHandleUpdateLastChatMessageConnected = true;
        m_chat->positionMessageListViewAtIndex(-1);
    }
}

void QxTdMessageListModel::QxTdOlderMessagesHandler::handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    for (unsigned int index = 0; index < messages.count(); index++) {
        auto *message = messageFromJson(messages[index]);
        messageListModel.appendMessage(message);
    }
}

void QxTdMessageListModel::QxTdNewerMessagesHandler::handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    QList<qint64> unreadMessages;

    for (int index = messages.count() - 1; index >= 0; index--) {
        auto *message = messageFromJson(messages[index]);
        messageListModel.prependMessage(message);
        unreadMessages << message->id();
    }

    messageListModel.setMessagesRead(unreadMessages);
}

void QxTdMessageListModel::QxTdJumpToWindowMessageHandler::handle(QxTdMessageListModel &messageListModel, const QJsonArray &messages) const
{
    QList<qint64> unreadMessages;

    for (unsigned int index = 0; index < messages.count(); index++) {
        auto *message = messageFromJson(messages[index]);
        if (message->id() == messageListModel.m_chat->lastReadInboxMessageId() &&
            message->id() != messageListModel.m_chat->lastMessage()->id()) {
            auto *unreadLabel = new QxTdMessage;
            unreadLabel->unmarshalJson(QJsonObject{ { "unreadLabel", qxTranslate("Unread Messages") } });
            messageListModel.m_model->append(unreadLabel);
        }

        messageListModel.appendMessage(message);
        unreadMessages << message->id();
    }

    int jumpToMessageIndex = messageListModel.m_model->indexOf(QString::number(messageListModel.m_jumpToMessageId));
    messageListModel.m_chat->positionMessageListViewAtIndex(jumpToMessageIndex+1);
    messageListModel.setMessagesRead(unreadMessages);
    if (messageListModel.m_highlightJumpedMessage) {
        emit messageListModel.m_model->getByUid(QString::number(messageListModel.m_jumpToMessageId))->highlight();
    }
}

QxTdMessage *QxTdMessageListModel::getDateLabelIfNeeded(QxTdMessage *firstMessage, QxTdMessage *secondMessage)
{
    const QDate firstDate = firstMessage->qmlDate().date();
    const QDate secondDate = secondMessage
            ? secondMessage->qmlDate().date()
            : QDate();
    if (firstDate.year() > secondDate.year()
        || firstDate.month() > secondDate.month()
        || firstDate.day() > secondDate.day()) {
        auto *dateMessage = new QxTdMessage;
        dateMessage->unmarshalJson(QJsonObject{ { "dateLabel", firstMessage->date() } });
        return dateMessage;
    } else {
        return nullptr;
    }
}

void QxTdMessageListModel::appendMessage(QxTdMessage *message)
{
    if (m_model->isEmpty()) {
        m_model->append(message);
        return;
    }
    if (m_model->getByUid(message->qmlId())) {
        return;
    }
    auto *last = m_model->last();
    message->setPreviousSender(last->sender());
    last->setNextSender(message->sender());

    if (!message->sendingState()) {
        auto dateMessage = getDateLabelIfNeeded(last, message);
        if (dateMessage) {
            m_model->append(dateMessage);
        }
    }

    m_model->append(message);
}

void QxTdMessageListModel::prependMessage(QxTdMessage *message)
{
    if (m_model->isEmpty()) {
        m_model->prepend(message);
        return;
    }
    if (m_model->getByUid(message->qmlId())) {
        return;
    }
    auto *first = m_model->first();
    message->setNextSender(first->sender());
    first->setPreviousSender(message->sender());

    if (!message->sendingState()) {
        auto dateMessage = getDateLabelIfNeeded(message, first);
        if (dateMessage) {
            m_model->prepend(dateMessage);
        }
    }

    m_model->prepend(message);
}

void QxTdMessageListModel::loadMessages(qint64 fromMsgId, unsigned int amountOlder, unsigned int amountNewer)
{
    std::unique_ptr<QxTdGetChatHistoryRequest> request(new QxTdGetChatHistoryRequest);
    request->setChatId(m_chat->id());
    request->setFromMessageId(fromMsgId);
    request->setLimit(static_cast<int>(amountOlder + amountNewer + 1));
    request->setOffset(static_cast<int>(-amountNewer));
    request->sendAsync();
}

void QxTdMessageListModel::handleUpdateChatLastMessage(const QJsonObject &json)
{
    if (!m_chat || json.isEmpty()) {
        return;
    }

    const qint64 id = json["chat_id"].toVariant().toLongLong();
    if (id != m_chat->id()) {
        return;
    }

    const QJsonObject messageJson = json["last_message"].toObject();

    const qint64 messageId = messageJson["id"].toVariant().toLongLong();
    auto *message = m_model->getByUid(QString::number(messageId));
    bool newMessage = false;
    if (!message) {
        message = new QxTdMessage();
        newMessage = true;
    }
    message->unmarshalJson(messageJson);
    if (newMessage) {
        prependMessage(message);
        QList<qint64> unreadMessages;
        unreadMessages << messageId;
        setMessagesRead(unreadMessages);
    }

    emit modelChanged();
}

void QxTdMessageListModel::handleUpdateMessageSendStatus(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    const qint64 oldMid = json["old_message_id"].toVariant().toLongLong();
    auto *msgSent = m_model->getByUid(QString::number(oldMid));
    if (msgSent) {
        const QJsonObject message = json["message"].toObject();
        msgSent->unmarshalJson(message);
    }
    if (json["@type"].toString() == "updateMessageSendFailed") {
        qWarning() << "Message send error" << json["error_code"].toVariant().toLongLong() << json["error_message"].toString();
    }
}

void QxTdMessageListModel::handleUpdateMessageEdited(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    auto messageId = QString::number(json["message_id"].toVariant().toLongLong(), 'f', 0);
    QxTdMessage *message = m_model->getByUid(messageId);
    if (!message) {
        return;
    }
    message->setIsEdited(true);
}

void QxTdMessageListModel::handleUpdateDeleteMessages(const QJsonObject &json)
{
    if (json.isEmpty() || json["from_cache"].toBool()) {
        return;
    }
    const QJsonArray messagesToDelete = json["message_ids"].toArray();
    foreach (QJsonValue messageToDelete, messagesToDelete) {
        qint64 id = messageToDelete.toVariant().toLongLong();
        auto messageId = QString::number(id, 'f', 0);
        QxTdMessage *message = m_model->getByUid(messageId);
        if (!message) {
            continue;
        }
        foreach (QxTdMessage *msg, m_model->toList()) {
            if (msg->messageRepliedTo() && msg->messageRepliedTo()->id() == id) {
                msg->messageRepliedTo()->unmarshalJson(QJsonObject{{"date",0}});
                emit msg->messageRepliedToChanged();
            }
        }
        m_model->remove(message);
    }
}

void QxTdMessageListModel::handleUpdateMessageContent(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }

    const qint64 messageId = json["message_id"].toVariant().toLongLong();
    const QJsonObject newContent = json["new_content"].toObject();
    QxTdMessage *message = m_model->getByUid(QString::number(messageId));
    if (!message) {
        return;
    }
    message->unmarshalUpdateContent(newContent);
}

void QxTdMessageListModel::sendMessage(const QString &fullmessage, const bool clearDraft, const bool disableNotification, const qint32 sendDate, const QString &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    QString plainText;
    QJsonArray formatEntities = QxTdHelpers::formatPlainTextMessage(fullmessage, plainText);
    bool isFirstMessage = true;
    qint32 currentMessagePos = 0;
    qint32 currentMessageLength = 0;
    qint32 maxMessageLength = QxTdClient::instance()->getOption("message_text_length_max").toInt();
    do {
        QString message = plainText.mid(currentMessagePos, maxMessageLength);
        std::unique_ptr<QxTdSendMessageRequest> request(new QxTdSendMessageRequest);
        request->setChatId(m_chat->id());
        request->setDisableNotification(disableNotification);
        request->setSendDate(sendDate);
        std::unique_ptr<QxTdInputMessageText> messageText(new QxTdInputMessageText);
        messageText->setText(message);
        messageText->setEntities(formatEntities);
        messageText->setClearDraft(clearDraft);
        request->setContent(messageText.get());
        if (isFirstMessage) {
            request->setReplyToMessageId(replyToMessageId.toLongLong());
            isFirstMessage = false;
        }
        currentMessageLength = message.length();
        request->sendAsync();
        currentMessagePos += maxMessageLength;
    } while (currentMessagePos < plainText.length());
}

void QxTdMessageListModel::setCaptionProperties(IMessageCaptionContent *contentObj, const QString &caption)
{
    if (contentObj != nullptr) {
        QString plainText;
        qint32 maxCaptionLength = QxTdClient::instance()->getOption("message_caption_length_max").toInt();
        QJsonArray formatEntities = QxTdHelpers::formatPlainTextMessage(caption, plainText);
        contentObj->setCaption(plainText.left(maxCaptionLength));
        contentObj->setCaptionEntities(formatEntities);
    }
}

void QxTdMessageListModel::setAttachmentProperties(IMessageAttachmentContent *contentObj, const QString &attachmentUrl)
{
    if (contentObj != nullptr) {
        contentObj->setAttachmentPath(attachmentUrl);
    }
}

void QxTdMessageListModel::prepareAndSendAttachmentMessage(QxTdInputMessageContent *content, const qint64 &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    std::unique_ptr<QxTdSendMessageRequest> request(new QxTdSendMessageRequest);
    request->setChatId(m_chat->id());
    request->setContent(content);
    request->setReplyToMessageId(replyToMessageId);
    QxTdClient::instance()->sendAsync(request.get(), &QxTdClient::message);
}

void QxTdMessageListModel::prepareAndSendAttachmentMessageAlbum(const QList<QxTdInputMessageContent *> &contents, const qint64 &replyToMessageId)
{
    if (!m_chat) {
        return;
    }
    std::unique_ptr<QxTdSendMessageAlbumRequest> request(new QxTdSendMessageAlbumRequest);
    request->setChatId(m_chat->id());
    request->setContents(contents);
    request->setReplyToMessageId(replyToMessageId);
    QxTdClient::instance()->sendAsync(request.get(), &QxTdClient::message);
}

void QxTdMessageListModel::sendMedia(const QString &url, const QString &caption, const qint64 &replyToMessageId, InputMessageType inputMessageType)
{
    QxTdInputMessageContentAttachmentCaption* messageContent(QxTdInputMessageContentFactory::create(inputMessageType));
    setAttachmentProperties(messageContent, url);
    setCaptionProperties(messageContent, caption);
    prepareAndSendAttachmentMessage(messageContent, replyToMessageId);
}

void QxTdMessageListModel::sendPhoto(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Photo);
}

void QxTdMessageListModel::sendPhotoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Photo);
}

void QxTdMessageListModel::sendVideoAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Video);
}

void QxTdMessageListModel::sendAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId, const InputMessageType type)
{
    //sendMessageAlbum size must be between 2 and 10
    //so if we have more than 10 urls we send multiple messageAlbum
    for (int i = 0; i < urls.size(); i+=10) {
        QList<QxTdInputMessageContent *> messageContents;
        for (int j = 0; j < 10 && j+i < urls.size(); j++) {
            QxTdInputMessageContentAttachmentCaption *messageContent = QxTdInputMessageContentFactory::create(type);
            setAttachmentProperties(messageContent, urls.at(j+i));
            if (i == 0 && j == 0) {
                setCaptionProperties(messageContent, caption);
            }
            messageContents.append(messageContent);
        }
        prepareAndSendAttachmentMessageAlbum(messageContents, replyToMessageId);
    }
}

void QxTdMessageListModel::sendAudio(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Audio);
}

void QxTdMessageListModel::sendAudioAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Audio);
}

void QxTdMessageListModel::sendVideo(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Video);
}

void QxTdMessageListModel::sendContact(const QString &firstName, const QString &lastName, const QString &phone, const qint64 &replyToMessageId)
{
    std::unique_ptr<QxTdInputMessageContact> messageContent(new QxTdInputMessageContact);
    messageContent->contact()->setFirstName(firstName);
    messageContent->contact()->setLastName(lastName);
    messageContent->contact()->setPhoneNumber(phone);
    prepareAndSendAttachmentMessage(messageContent.get(), replyToMessageId);
}

void QxTdMessageListModel::sendDocument(const QString &url, const QString &caption, const qint64 &replyToMessageId)
{
    sendMedia(url, caption, replyToMessageId, Document);
}

void QxTdMessageListModel::sendDocumentAlbum(const QList<QString> &urls, const QString &caption, const qint64 &replyToMessageId)
{
    sendAlbum(urls, caption, replyToMessageId, Document);
}

void QxTdMessageListModel::sendLocation(const double latitude, const double longitude, const qint32 livePeriod, const qint64 &replyToMessageId)
{
    std::unique_ptr<QxTdInputMessageLocation> messageContent(new QxTdInputMessageLocation);
    messageContent->setLocation(latitude, longitude);
    messageContent->setLivePeriod(livePeriod);
    prepareAndSendAttachmentMessage(messageContent.get(), replyToMessageId);
}

void QxTdMessageListModel::sendSticker(QxTdSticker *sticker, const QString &replyToMessageId)
{
    std::unique_ptr<QxTdInputMessageSticker> messageContent(new QxTdInputMessageSticker);
    messageContent->setSticker(sticker);
    prepareAndSendAttachmentMessage(messageContent.get(), replyToMessageId.toLongLong());
}

void QxTdMessageListModel::sendVoiceNote(const QString &filename, const qint64 &replyToMessageId)
{
    if (m_voiceNoteRecorder->duration() > 0) {
        std::unique_ptr<QxTdInputMessageVoiceNote> messageContent(new QxTdInputMessageVoiceNote);
        setAttachmentProperties(messageContent.get(), filename);
        prepareAndSendAttachmentMessage(messageContent.get(), replyToMessageId);
    }
}

void QxTdMessageListModel::editMessageText(qint64 messageId, const QString &message)
{
    if (!m_chat) {
        return;
    }

    QString plainText;
    QJsonArray formatEntities = QxTdHelpers::formatPlainTextMessage(message, plainText);

    std::unique_ptr<QxTdEditMessageTextRequest> request(new QxTdEditMessageTextRequest);
    request->setChatId(m_chat->id());
    request->setMessageId(messageId);
    request->setText(plainText);
    request->setEntities(formatEntities);

    QFuture<QxTdResponse> response = request->sendAsync();
    qxAwait(response);
    if (response.result().isError()) {
        emit error(response.result().errorString());
    }
}

void QxTdMessageListModel::editMessageText(const QString &messageId, const QString &message)
{
    editMessageText(messageId.toLongLong(), message);
}

void QxTdMessageListModel::editMessageCaption(qint64 messageId, const QString &message)
{
    if (!m_chat) {
        return;
    }

    QString plainText;
    QJsonArray formatEntities = QxTdHelpers::formatPlainTextMessage(message, plainText);

    std::unique_ptr<QxTdEditMessageCaptionRequest> request(new QxTdEditMessageCaptionRequest);
    request->setChatId(m_chat->id());
    request->setMessageId(messageId);
    request->setText(plainText);
    request->setEntities(formatEntities);

    QFuture<QxTdResponse> response = request->sendAsync();
    qxAwait(response);
    if (response.result().isError()) {
        emit error(response.result().errorString());
    }
}

void QxTdMessageListModel::editMessageCaption(const QString &messageId, const QString &message)
{
    editMessageCaption(messageId.toLongLong(), message);
}

void QxTdMessageListModel::deleteMessage(const qint64 messageId, const bool revoke)
{
    QList<qint64> messages;
    messages << messageId;
    deleteMessages(messages, revoke);
}

void QxTdMessageListModel::deleteMessages(const QList<qint64> &messageIds, const bool revoke)
{
    std::unique_ptr<QxTdDeleteMessagesRequest> req(new QxTdDeleteMessagesRequest);
    req->setChatId(m_chat->id());
    req->setMessageIds(messageIds);
    req->setRevoke(revoke);
    QxTdClient::instance()->send(req.get());
}

void QxTdMessageListModel::setMessagesRead(QList<qint64> &messages)
{
    // TODO: Determine how to detect which messages are in the visible part of the window
    std::unique_ptr<QxTdViewMessagesRequest> req(new QxTdViewMessagesRequest);
    req->setChatId(m_chat->id());
    req->setMessageIds(messages);
    QxTdClient::instance()->send(req.get());
    if (messages.contains(m_chat->lastMessage()->id())) {
        QxTdClient::instance()->clearNotificationFor(m_chat->id());
    }
}

void QxTdMessageListModel::jumpToMessage(const qint64 messageId, const bool isToBeHighlighted)
{
    int messageToJumpToIndex = m_model->indexOf(QString::number(messageId));
    if (messageToJumpToIndex > -1) {
        m_chat->positionMessageListViewAtIndex(messageToJumpToIndex+1);
        if (isToBeHighlighted) {
            emit m_model->getByUid(QString::number(messageId))->highlight();
        }
    } else {
        cleanUp();
        m_jumpToMessageId = messageId;
        m_highlightJumpedMessage = isToBeHighlighted;
        m_isHandleUpdateLastChatMessageConnected = false;
        m_messageHandler = &jumpToWindowMessageHandler;
        loadMessages(messageId, MESSAGE_LOAD_WINDOW / 2, MESSAGE_LOAD_WINDOW / 2);
    }
}

void QxTdMessageListModel::handleUpdateFileGenerationStart(const QJsonObject &json)
{
    QString destinationPath = json["destination_path"].toString();
    if (QFile::exists(destinationPath)) {
        QFile::remove(destinationPath);
    }

    m_fileGenerationId = json["generation_id"].toString();
    QJsonObject finishReq = QJsonObject {
        { "@type", "finishFileGeneration" },
        { "generation_id", m_fileGenerationId }
    };
    QString originalPath = json["original_path"].toString();
    QString conversion = json["conversion"].toString();
    bool result;
    if (conversion == "attachment") {
        result = QFile::copy(originalPath, destinationPath);
    } else {
        result = QFile::rename(originalPath, destinationPath);
    }
    if (!result) {
        qWarning() << "Could not move" << originalPath << "to" << destinationPath;
        QJsonObject error = QJsonObject {
            { "@type", "error" },
            { "code", "500" }
        };
        finishReq.insert("error", error);
    }
    QxTdClient::instance()->send(finishReq);
    emit importFileFinished(originalPath);
}

void QxTdMessageListModel::handleUpdateFileGenerationStop(const QJsonObject &json)
{
    m_fileGenerationId = "";
}

void QxTdMessageListModel::handleUpdateMessageInteractionInfo(const QJsonObject &json)
{

    auto chatId = qint64(json["chat_id"].toDouble());
    if (!m_chat || m_chat->id() != chatId) {
        return;
    }

    auto messageId = qint64(json["message_id"].toDouble());
    auto message = m_model->getByUid(QString::number(messageId));
    if (!message) {
        return;
    }

    auto interactionInfo = json["interaction_info"].toObject();
    message->interactionInfo()->unmarshalJson(interactionInfo);
}

void QxTdMessageListModel::handleRequestMessageLinkCompleted(const QJsonObject &json)
{
    auto link = json["link"].toString();
    emit messageLinkReceived(link);
}

void QxTdMessageListModel::registerVoiceNote(const QString &filename)
{
    m_voiceNoteRecorder->setOutputLocation(QUrl(filename));
    m_voiceNoteRecorder->record();
}

void QxTdMessageListModel::stopVoiceNote()
{
    qWarning() << "Stopping voice note recording";
    m_voiceNoteRecorder->stop();
}

void QxTdMessageListModel::deleteVoiceNote(const QString &filename)
{
    QFile file(filename);
    if (!file.remove()) {
        qWarning() << "Could not delete temp voice note:" << filename;
    }
}

void QxTdMessageListModel::removeChatActionBar()
{
    QJsonObject removeChatActionBarRequest = QJsonObject {
        { "@type", "removeChatActionBar" },
        { "chat_id", m_chat->id() }
    };
    QxTdClient::instance()->send(removeChatActionBarRequest);
}

void QxTdMessageListModel::reportChat(const QString chatId, const QxTdChatReportReason::ChatReportReasonType &reason, const QString &text)
{

    std::unique_ptr<QxTdReportChatRequest> req(new QxTdReportChatRequest);
    req->setChatId(chatId);
    // req->setMessageIds(messages);
    std::unique_ptr<QxTdChatReportReason> reasonObj;
    switch (reason) {
    case QxTdChatReportReason::ChatReportReasonChildAbuse:
        reasonObj.reset(new QxTdChatReportReasonChildAbuse());
        break;
    case QxTdChatReportReason::ChatReportReasonCopyright:
        reasonObj.reset(new QxTdChatReportReasonCopyright());
        break;
    case QxTdChatReportReason::ChatReportReasonCustom:
        reasonObj.reset(new QxTdChatReportReasonCustom());
        break;
    case QxTdChatReportReason::ChatReportReasonFake:
        reasonObj.reset(new QxTdChatReportReasonFake());
        break;
    case QxTdChatReportReason::ChatReportReasonPornography:
        reasonObj.reset(new QxTdChatReportReasonPornograhpy());
        break;
    case QxTdChatReportReason::ChatReportReasonSpam:
        reasonObj.reset(new QxTdChatReportReasonSpam());
        break;
    case QxTdChatReportReason::ChatReportReasonUnrelatedLocation:
        reasonObj.reset(new QxTdChatReportReasonUnrelatedLocation());
        break;
    case QxTdChatReportReason::ChatReportReasonViolence:
        reasonObj.reset(new QxTdChatReportReasonViolence());
        break;
    }
    req->setReason(reasonObj.get());
    req->setText(text);
    req->sendAsync();
}

void QxTdMessageListModel::requestMessageLink(const QString chatId, const QString messageId)
{
    std::unique_ptr<QxTdGetMessageLinkRequest> req(new QxTdGetMessageLinkRequest);
    req->setChatId(chatId.toLong());
    req->setMessageId(messageId.toLong());
    req->sendAsync();
}

void QxTdMessageListModel::toggleMessageSenderIsBlocked(const qint64 id, const bool isBlocked, const QxTdMessageSender::SenderType type)
{
    QxTdMessageSender *sender;
    QJsonObject messageSender;
    switch (type) {
        case QxTdMessageSender::User:
            messageSender = QJsonObject{
                    {"@type",   "messageSenderUser"},
                    {"user_id", id}
            };
            sender = new QxTdMessageSenderUser;
            sender->unmarshalJson(messageSender, "user_id");
            break;
        case QxTdMessageSender::Chat:
            messageSender = QJsonObject{
                    {"@type",   "messageSenderChat"},
                    {"chat_id", id}
            };
            sender = new QxTdMessageSenderChat;
            sender->unmarshalJson(messageSender, "chat_id");
            break;
    }
    std::unique_ptr<QxTdToggleMessageSenderIsBlockedRequest> req(new QxTdToggleMessageSenderIsBlockedRequest);
    req->setSenderId(sender);
    req->setIsBlocked(isBlocked);
    req->sendAsync();
    delete sender;
}

void QxTdMessageListModel::searchChatMessages(const QString chatId, const QString query, const QString fromMessageId)
{
    std::unique_ptr<QxTdSearchChatMessagesRequest> req(new QxTdSearchChatMessagesRequest);
    req->setChatId(chatId.toLong());
    req->setQuery(query);
    req->setFromMessageId(fromMessageId.toLong());
    req->setLimit(100);
    req->setOffset(0);
    req->setMessageThreadId(0);
    req->sendAsync();
}
