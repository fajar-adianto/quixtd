#ifndef QX_TD_CLIENT_H
#define QX_TD_CLIENT_H

#include <functional>
#include <QPointer>
#include <QSharedPointer>
#include <QHash>
#include <QFuture>
#include <QThread>
#include <QtConcurrent>
#include <QWaitCondition>

#include "auth/qx_td_auth_state.h"
#include "connections/qx_td_connection_state.h"
#include "common/qx_td_response.h"

#include "../auxdb/auxdb.h"
#include "../auxdb/postal-client.h"

// callback to trigger on received messages from tdlib.
typedef std::function<void(QJsonObject)> ReceiveCallback;

class QxTdRequest; // Forward declaration.

/**
 * @brief The QxTdClient class
 *
 * QxTdClient is the main interface for communication with
 * the tdlib backend. A static instance is used to easily share
 * between components.
 */
class QxTdClient : public QObject
{
    Q_OBJECT
public:
    explicit QxTdClient(QObject *parent = nullptr);

    /**
     * @brief Shared static instance in the main thread.
     */
    static QxTdClient *instance();

    /**
     * @brief The current authentication state
     */
    QxTdAuthState *authState() const;
    /**
     * @brief The current connection state
     */
    QxTdConnectionState *connectionState() const;

    /**
     * @brief send
     *
     * Send a request in another thread.
     */
    void send(QxTdRequest *obj);
    void send(const QJsonObject &json);

    /**
     * @brief sendAsync
     * @param obj is the QxTdRequest to send
     * @param void(QxTdClient::*s)(QJsonObject) is the signal the response will come down
     * @return QFuture<QxTdResponse> - QxTdResponse will either contain an `error` or the requested return types json object
     *
     * Send an asynchronous request that can be waited on for a response.
     *
     * @example
     * std::unique_ptr<QxTdGetChatsRequest> req(new QxTdGetChatsRequest);
     *
     * The response to getChats comes down the `chats` signal
     * QFuture<QxTdResponse> resp = QxTdClient::instance()->sendAsync(req, &QxTdClient::chats);
     *
     * You can either use a QFutureWatcher to wait for the resp or you can use the new
     * `await` helper `#include "utils/await.h"` which uses QFutureWatcher internally but also allows a timeout
     * so you don't wait forever.
     * await(resp);
     *
     * if (resp.result().isError()) {
     *   // handle error
     *   qWarning() << resp.result().errorCode() << resp.result().errorString();
     * }
     * // access json
     * qDebug() << resp.result().json()
     *
     */
    QFuture<QxTdResponse> sendAsync(QxTdRequest *obj, void (QxTdClient::*signal)(QJsonObject));

    /**
     * @brief Execute synchronous request in another Thread
     *
     * This is a synchronous action in another
     * thread and will return the result via the
     * returned QFuture
     *
     * Note: there is only a limited set of actions that can be sent
     * through exec. Still need to figure out what they are. Once
     * found it will be indicated in each QxTdRequest derived class
     * documentation
     */
    QFuture<QJsonObject> exec(QxTdRequest *obj);
    QFuture<QJsonObject> exec(const QJsonObject &json);

    /**
     * @brief Retrieve a Telegram server option by name
     *
     * Retrieves an option that has been received from the Telegram server upon login or after an update
     * Clients should subscribe for the updateOption signal and then call this method with the appropriate name
     * Returns an empty QVariant if the option is not found.
     */
    QVariant getOption(const QString name);

    void setAvatarMapEntry(const qint64 id, const QString path);
    void setUnreadMapEntry(const qint64 id, const qint32 unread_count);
    void removeMapEntry(const qint64 id);
    void clearNotificationFor(const qint64 id);
    void shutDown();
    
signals:
    void authStateChanged(QxTdAuthState *state);
    void connectionStateChanged(QxTdConnectionState *state);
    void updateUser(QJsonObject user);
    void updateUserStatus(const QString &user_id, const QJsonObject &status);
    void updateUserFullInfo(const QString &user_id, const QJsonObject &fullInfo);
    void updateFile(const QJsonObject &file);
    void updateNewChat(const QJsonObject &chat);
    void updateChatPosition(const QJsonObject &chat);
    void updateChatLastMessage(const QJsonObject &chat);
    void updateChatActionBar(const QJsonObject &chat);
    void updateMessageSendStatus(const QJsonObject &chat);
    void updateMessageContent(const QJsonObject &chat);
    void updateBasicGroup(const QJsonObject &group);
    void updateBasicGroupFullInfo(const QJsonObject &group);
    void updateSecretChat(const QJsonObject &chat);
    void updateSuperGroup(const QJsonObject &group);
    void updateSupergroupFullInfo(const QJsonObject &group);
    void updateChatReadInbox(const QJsonObject &chat);
    void updateChatReadOutbox(const QJsonObject &chat);
    void updateChatPhoto(const QJsonObject &photo);
    void updateChatReplyMarkup(const QJsonObject &chat);
    void updateChatDraftMessage(const QJsonObject &chat);
    void updateChatTitle(const QJsonObject &chat);
    void updateChatUnreadMentionCount(const QJsonObject &chat);
    void updateChatAction(const QJsonObject &chat);
    void updateChatNotificationSettings(const QJsonObject &chat);
    void updateDeleteMessages(const QJsonObject &messages);
    void updateOption(const QJsonObject &option);
    void updateUnreadMessageCount(const QJsonObject &message);
    void updateScopeNotificationSettings(const QJsonObject &message);
    void updateMessageEdited(const QJsonObject &message);
    void updateUnreadChatCount(const QJsonObject &message);
    void updateNewMessage(const QJsonObject &message);
    void updateMessageInteractionInfo(const QJsonObject &message);
    void updateChatOnlineMemberCount(const QJsonObject &data);
    void updateFileGenerationStart(const QJsonObject &data);
    void updateFileGenerationStop(const QJsonObject &data);
    void updateChatIsBlocked(const QJsonObject &data);

    // Response signals
    void error(QJsonObject error);
    void ok(QJsonObject message);
    void chats(QJsonObject chats);
    void chat(QJsonObject chat);
    void basicGroup(QJsonObject group);
    void secretChat(QJsonObject chat);
    void superGroup(QJsonObject group);
    void supergroupFullInfo(QJsonObject group);
    void messages(QJsonObject messages);
    void message(QJsonObject message);
    void messageLink(QJsonObject messageLink);
    void file(QJsonObject file);
    void user(QJsonObject user);
    void users(QJsonObject users);
    void importedContacts(QJsonObject importedContacts);
    void userFullInfo(QJsonObject userFullInfo);
    void stickerSets(QJsonObject stickerSets);
    void stickerSet(QJsonObject stickerSet);
    void updateInstalledStickerSets(QJsonObject stickerSetsUpdate);
    void chatInviteLinkInfo(QJsonObject chatInviteLinkInfo);
    void pushReceiverId(QJsonObject);
    void proxies(QJsonObject);
    void proxy(QJsonObject);
    void seconds(QJsonObject);
    void toggleMessageSenderIsBlocked(QJsonObject);
    void foundChatMessages(QJsonObject);

private slots:
    void handleRecv(const QJsonObject &data);

private:
    Q_DISABLE_COPY(QxTdClient)
    bool m_debug;
    void init();
    void handleUpdateOption(const QJsonObject &json);
    std::unique_ptr<QThread> m_worker;
    QPointer<QxTdAuthState> m_authState;
    QPointer<QxTdConnectionState> m_connectionState;
    QHash<QString, ReceiveCallback> m_events;
    QHash<QString, QVariant> m_options;

    QString getTag();
    int m_tagcounter;
    AuxDatabase m_auxdb;
    PostalClient m_postalClient;
};

#endif // QX_TD_CLIENT_H
