#ifndef QX_TD_MESSAGE_SUPER_GROUP_CHAT_CREATE_H
#define QX_TD_MESSAGE_SUPER_GROUP_CHAT_CREATE_H

#include "messages/qx_td_message_content.h"

/**
 * @brief The QxTdMessageSuperGroupChatCreate class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_super_group_chat_create.html
 */
class QxTdMessageSuperGroupChatCreate : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageSuperGroupChatCreate)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageSuperGroupChatCreate(QObject *parent = nullptr);

    QString title() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void titleChanged();

private:
    QString m_title;
};

#endif // QX_TD_MESSAGE_SUPER_GROUP_CHAT_CREATE_H
