#ifndef QX_TD_MESSAGE_BASIC_GROUP_CHAT_CREATE_H
#define QX_TD_MESSAGE_BASIC_GROUP_CHAT_CREATE_H

#include "qx_td_message_chat_add_members.h"

/**
 * @brief The QxTdMessageBasicGroupChatCreate class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_basic_group_chat_create.html
 */
class QxTdMessageBasicGroupChatCreate : public QxTdMessageChatAddMembers
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageBasicGroupChatCreate)
    Q_PROPERTY(QString title READ title NOTIFY titleChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageBasicGroupChatCreate cannot be created in QML.")
public:
    explicit QxTdMessageBasicGroupChatCreate(QObject *parent = nullptr);

    QString title() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void titleChanged();

private:
    QString m_title;
};

#endif // QX_TD_MESSAGE_BASIC_GROUP_CHAT_CREATE_H
