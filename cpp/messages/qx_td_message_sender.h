#ifndef QX_TD_MESSAGE_SENDER_H
#define QX_TD_MESSAGE_SENDER_H

#include "files/qx_td_photo.h"

/**
 * @brief The QxTdMessageSender class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_message_sender.html
 */
class QxTdMessageSender : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageSender)
    Q_PROPERTY(QString fullName READ fullName NOTIFY dataChanged)
    Q_PROPERTY(QString displayName READ displayName NOTIFY dataChanged)
    Q_PROPERTY(QxTdPhoto *photo READ photo NOTIFY dataChanged)
    Q_PROPERTY(QString avatarColor READ avatarColor NOTIFY dataChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageSender cannot be created in QML.")
public:
    explicit QxTdMessageSender(QObject *parent = nullptr);

    enum SenderType {
        User,
        Chat
    };
    Q_ENUM(SenderType)

    virtual QString displayName() const = 0;
    virtual QString fullName() const = 0;
    virtual QxTdPhoto *photo() const = 0;
    virtual QString avatarColor() const;
    virtual QString initials() const = 0;
    virtual QJsonObject marshalJson() const = 0;

signals:
    void dataChanged();
};

/**
 * @brief The QxTdMessageSenderUnimplemented class
 *
 * Stops the app from crashing if Telegram adds an unsupported sender type
 */
class QxTdMessageSenderUnimplemented : public QxTdMessageSender
{
    Q_OBJECT
public:
    explicit QxTdMessageSenderUnimplemented(QObject *parent = nullptr);

    QString displayName() const;
    QString fullName() const;
    QxTdPhoto *photo() const;
    QString initials() const;
    QJsonObject marshalJson() const;

private:
    Q_DISABLE_COPY(QxTdMessageSenderUnimplemented)
};

struct QxTdMessageSenderFactory
{
    static QxTdMessageSender *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_MESSAGE_SENDER_H
