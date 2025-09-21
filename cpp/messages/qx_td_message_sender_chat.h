#ifndef QX_TD_MESSAGE_SENDER_CHAT_H
#define QX_TD_MESSAGE_SENDER_CHAT_H

#include "qx_td_message_sender.h"

class QxTdChat; // Forward declaration.

/**
 * @brief The QxTdMessageSenderChat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_sender_chat.html
 */
class QxTdMessageSenderChat : public QxTdMessageSender
{
    Q_OBJECT
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY chatChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageSenderChat(QObject *parent = nullptr);

    QString displayName() const override;
    QString fullName() const override;
    QxTdPhoto *photo() const override;
    QString smallPhotoPath() const;
    QString initials() const override;
    QJsonObject marshalJson() const override;

    void unmarshalJson(const QJsonObject &json, const QString &id_key) override;
signals:
    void chatChanged();

private:
    Q_DISABLE_COPY(QxTdMessageSenderChat)
    QxTdChat *m_chat;
    bool m_waitingForChat;

    void updateChat(const qint64 &chatId);
};

#endif // QX_TD_MESSAGE_SENDER_CHAT_H
