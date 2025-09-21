#ifndef QX_TD_MESSAGE_CHAT_UPGRADE_TO_H
#define QX_TD_MESSAGE_CHAT_UPGRADE_TO_H

#include "common/qx_abstract_int64_id.h"
#include "messages/qx_td_message_content.h"

class QxTdMessageChatUpgradeTo : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageChatUpgradeTo)
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatUpgradeTo cannot be created in QML.")
public:
    explicit QxTdMessageChatUpgradeTo(QObject *parent = nullptr);

    QString qmlSuperGroupId() const;

    qint64 superGroupId() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QxTdInt64 m_sgId;
};

#endif // QX_TD_MESSAGE_CHAT_UPGRADE_TO_H
