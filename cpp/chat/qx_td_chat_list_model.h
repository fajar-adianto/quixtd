#ifndef QX_TD_CHAT_LIST_MODEL_H
#define QX_TD_CHAT_LIST_MODEL_H

#include <QTimer>
#include <QtPositioning/QGeoPositionInfoSource>

#include "qx_td_chat.h"
#include "auth/qx_td_auth_state.h"
#include "chat/qx_td_chat_invite_link_info.h"
#include "models/qx_td_object_list_model.h"

class PinnedChat
{
private:
    qint64 m_id;
    long long m_order;

public:
    PinnedChat(qint64 id, long long order)
    {
        m_id = id;
        m_order = order;
    }

    qint64 id() const
    {
        return m_id;
    }

    long long order() const
    {
        return m_order;
    }

    bool operator==(const PinnedChat &other) const
    {
        return this->id() == other.id();
    }

    bool operator<(const PinnedChat &other) const
    {
        if (other.order() == this->order()) {
            return other.id() < this->id();
        }
        return other.order() < this->order();
    }

    operator QString() const {
        return QString("(id: %1, order: %2)").arg(QString::number(id()), QString::number(order()));
    }
};

typedef QList<PinnedChat> PinnedChats;

class QxTdChatListModel : public QObject
{

    Q_OBJECT
    Q_PROPERTY(QObject *model READ model NOTIFY modelChanged)
    Q_PROPERTY(QxTdChat *currentChat READ currentChat WRITE setCurrentChat NOTIFY currentChatChanged)
    Q_PROPERTY(ListMode listMode READ listMode WRITE setListMode NOTIFY listModeChanged)
    Q_PROPERTY(qint32 forwardingMessagesCount READ forwardingMessagesCount NOTIFY modelChanged)
    Q_PROPERTY(QxTdChat *forwardedFromChat READ forwardedFromChat WRITE setForwardedFromChat NOTIFY modelChanged)
    Q_PROPERTY(QStringList forwardingMessages READ forwardingMessages WRITE setForwardingMessages NOTIFY modelChanged)
    QML_ELEMENT
public:
    enum ListMode { Idle,
                    ForwardingMessages,
                    ImportingAttachments };
    Q_ENUM(ListMode)

    explicit QxTdChatListModel(QObject *parent = nullptr);

    static QxTdChatListModel *instance();

    QxTdObjectListModel<QxTdChat> *model() const;
    QxTdChat *currentChat() const;
    QxTdChat *chatById(const qint64 &chatId) const;
    QxTdChat *forwardedFromChat() const;
    qint32 forwardingMessagesCount() const;
    ListMode listMode() const;
    QStringList forwardingMessages() const;
    Q_INVOKABLE qint64 chatIdByUsername(const QString &username);

public slots:
    void setCurrentChat(QxTdChat *currentChat);
    void setCurrentChatById(const qint64 &chatId);
    void setCurrentChatByUsername(const QString &username);
    void createOrOpenPrivateChat(const qint64 &userId);
    void createOrOpenSavedMessages();
    void createOrOpenSecretChat(const qint64 &userId);
    void setForwardedFromChat(QxTdChat *currentChat);
    void setForwardingMessages(QStringList forwardingMessages);
    void setListMode(ListMode listMode);
    void sendForwardMessage(const QStringList &forwardMessageIds,
                            const qint64 &recievingChatId,
                            const qint64 &fromChatId,
                            const QString &message);
    void requestPositionInfo();
    void cancelPositionInfo();
    void setChatDraftMessage(const QString &draftText,
                             const qint64 &replyToMessageId,
                             const qint64 &chatId);
    void joinChat(const qint64 &chatId) const;
    void checkChatInviteLink(const QString &inviteLink);
    void joinChatByInviteLink(const QString &inviteLink);
    void setChatToOpenOnUpdate(const qint64 &chatId);
    void openMessageContent(const QString chatId, const QString messageId);

    void loadMoreChats(const QString &chatList);

    void sendSetTTL(const QString &chatId, const int &ttl);
    void togglePinChat(const qint64 &chatId, const bool &pinned);

    void setPollAnswer(const QString &chatId, const QString &messageId, const QVariantList &optionIds);
    
signals:
    void modelChanged(QObject *model);
    void contentsChanged();
    void chatCreated(const qint64 &chatId);
    void chatStatusChanged();
    void currentChatChanged();
    void listModeChanged();
    void positionInfoReceived(double latitude, double longitude);
    void positionInfoTimeout();
    void invalidChatUsername(const QString &username);
    void modelPopulatedCompleted();
    void showChatInviteLinkInfo(QxTdChatInviteLinkInfo *info, const QString &inviteLink);
    void showNotification(const QString &message);

private slots:
    void handleChats(const QJsonObject &data);
    void handleChat(const QJsonObject &data);
    void handleUpdateNewChat(const QJsonObject &data);
    void handleUpdateChatPosition(const QJsonObject &data);
    void handleUpdateChatLastMessage(const QJsonObject &data);
    void handleAuthStateChanges(const QxTdAuthState *state);
    void updateChatReadInbox(const QJsonObject &data);
    void updateChatReadOutbox(const QJsonObject &data);
    void handleUpdateChatPhoto(const QJsonObject &data);
    void handleUpdateChatReplyMarkup(const QJsonObject &data);
    void handleUpdateChatDraftMessage(const QJsonObject &data);
    void handleUpdateChatTitle(const QJsonObject &data);
    void handleUpdateChatUnreadMentionCount(const QJsonObject &data);
    void handleUpdateChatNotificationSettings(const QJsonObject &data);
    void handleUpdateChatOnlineMemberCount(const QJsonObject &data);
    void handleForwardingMessagesAction();
    void positionUpdated(const QGeoPositionInfo &info);
    void onPositionInfoTimeout();

private:
    Q_DISABLE_COPY(QxTdChatListModel)
    QPointer<QxTdObjectListModel<QxTdChat>> m_model;
    static QPointer<QxTdChatListModel> s_chatlistmodel;
    PinnedChats m_pinnedChats;
    QPointer<QxTdChat> m_currentChat;
    qint64 m_chatToOpenOnUpdate;
    ListMode m_listMode;
    QStringList m_forwardingMessages;
    QPointer<QxTdChat> m_forwardedFromChat;
    QList<qint64> m_receivedChatIds;
    QPointer<QGeoPositionInfoSource> m_positionInfoSource;
    QTimer *m_positionWaitTimer;
};

#endif // QX_TD_CHAT_LIST_MODEL_H
