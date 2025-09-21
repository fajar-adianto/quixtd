#ifndef QX_TD_MESSAGE_CHAT_DELETE_MEMBER_H
#define QX_TD_MESSAGE_CHAT_DELETE_MEMBER_H

#include <QFutureWatcher>
#include <QPointer>
#include "common/qx_td_response.h"
#include "messages/qx_td_message_content.h"
#include "user/qx_td_user.h"

/**
 * @brief The QxTdMessageChatDeleteMember class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_delete_member.html
 */
class QxTdMessageChatDeleteMember : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdUser *user READ user NOTIFY userChanged)
    Q_PROPERTY(QString userId READ qmlUserId NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatDeleteMember cannot be created in QML.")
public:
    explicit QxTdMessageChatDeleteMember(QObject *parent = nullptr);

    QxTdUser *user() const;
    QString qmlUserId() const;
    qint64 userId() const;
    void setSenderUserId(const qint64 senderUserId);

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();
    void userChanged();

private slots:
    void handleResponse();

private:
    void updateTypeText();
    QPointer<QxTdUser> m_user;
    QxTdInt64 m_uid;
    QFutureWatcher<QxTdResponse> m_watcher;
    qint64 m_senderUserId;
};

#endif // QX_TD_MESSAGE_CHAT_DELETE_MEMBER_H
