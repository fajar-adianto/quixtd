#ifndef QX_TD_MESSAGE_SENDER_USER_H
#define QX_TD_MESSAGE_SENDER_USER_H

#include "qx_td_message_sender.h"
#include "user/qx_td_user.h"

/**
 * @brief The QxTdMessageSenderUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_sender_user.html
 */
class QxTdMessageSenderUser : public QxTdMessageSender
{
    Q_OBJECT
    Q_PROPERTY(QxTdUser *user READ user NOTIFY userChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY userChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageSenderUser(QObject *parent = nullptr);

    QxTdUser *user() const;
    QString displayName() const override;
    QString fullName() const override;
    QxTdPhoto *photo() const override;
    QString smallPhotoPath() const;
    QString initials() const override;
    QJsonObject marshalJson() const override;

    void unmarshalJson(const QJsonObject &json, const QString &id_key) override;
signals:
    void userChanged();

private:
    Q_DISABLE_COPY(QxTdMessageSenderUser)
    QxTdUser *m_user;
    bool m_waitingForUser;

    void updateUser(const qint64 &userId);
};

#endif // QX_TD_MESSAGE_SENDER_USER_H
