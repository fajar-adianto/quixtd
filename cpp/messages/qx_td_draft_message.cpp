#include "qx_td_draft_message.h"

QxTdDraftMessage::QxTdDraftMessage(QObject *parent)
    : QxTdObject(parent)
    , m_replyToMessageId(0)
    , m_inputMessageText(new QxTdInputMessageText)
{
    // Intentionally left empty.
}

QString QxTdDraftMessage::qmlReplyToMessageId() const
{
    return m_replyToMessageId.toQmlValue();
}
qint64 QxTdDraftMessage::replyToMessageId() const
{
    return m_replyToMessageId.value();
}

QxTdInputMessageText *QxTdDraftMessage::inputMessageText() const
{
    return m_inputMessageText.data();
}

void QxTdDraftMessage::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    if (!json.isEmpty()) {
        m_replyToMessageId = json["reply_to_message_id"].toVariant().toLongLong();
        emit replyToMessageIdChanged();
        const QJsonObject inputMessageText = json["input_message_text"].toObject();
        if (inputMessageText.isEmpty()) {
            m_inputMessageText.reset(new QxTdInputMessageText);
            emit inputMessageTextChanged();
        } else {
            const QString inputMessageTextType = inputMessageText["@type"].toString();
            //this should always be of type inputMessageText.
            if (inputMessageTextType == "inputMessageText") {
                m_inputMessageText->unmarshalJson(inputMessageText);
                emit inputMessageTextChanged();
            }
        }
    }
}

void QxTdDraftMessage::setReplyToMessageId(const qint64 &replyToMessageId)
{
    m_replyToMessageId = replyToMessageId;
    emit replyToMessageIdChanged();
}
void QxTdDraftMessage::setInputMessageText(QxTdInputMessageText *inputMessageText)
{
    m_inputMessageText.reset(inputMessageText);
    emit inputMessageTextChanged();
}
QJsonObject QxTdDraftMessage::marshalJson()
{

    return QJsonObject {
        { "@type", "draftMessage" },
        { "input_message_text", m_inputMessageText->marshalJson() },
        { "reply_to_message_id", replyToMessageId() }
    };
}
