#ifndef QX_TD_MESSAGE_CHAT_UPGRADE_FROM_H
#define QX_TD_MESSAGE_CHAT_UPGRADE_FROM_H

#include "common/qx_abstract_int64_id.h"
#include "messages/qx_td_message_content.h"

/**
 * @brief The QxTdMessageChatUpgradeFrom class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_upgrade_from.html
 */
class QxTdMessageChatUpgradeFrom : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageChatUpgradeFrom)
    Q_PROPERTY(QString title READ title NOTIFY contentChanged)
    Q_PROPERTY(QString basicGroupId READ qmlBasicGroupId NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatUpgradeFrom cannot be created in QML.")
public:
    explicit QxTdMessageChatUpgradeFrom(QObject *parent = nullptr);
    QString title() const;
    QString qmlBasicGroupId() const;
    qint64 basicGroupId() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_title;
    QxTdInt64 m_groupdId;
};

#endif // QX_TD_MESSAGE_CHAT_UPGRADE_FROM_H
