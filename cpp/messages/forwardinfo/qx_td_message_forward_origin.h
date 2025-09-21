#ifndef QX_TD_MESSAGE_FORWARD_ORIGIN_H
#define QX_TD_MESSAGE_FORWARD_ORIGIN_H

#include "common/qx_abstract_int64_id.h"

/**
 * @brief The QxTdMessageForwardOrigin class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_message_forward_origin.html
 */
class QxTdMessageForwardOrigin : public QxTdObject
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdMessageForwardOrigin)
    Q_PROPERTY(QString originSummary READ originSummary NOTIFY forwardOriginChanged)
public:
    explicit QxTdMessageForwardOrigin(QObject *parent = nullptr);
    virtual QString originSummary() const = 0;

signals:
    void forwardOriginChanged();
};

/**
     * @brief The QxTdMessageForwardOriginChat class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_chat.html
 */
class QxTdMessageForwardOriginChat : public QxTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdMessageForwardOriginChat)

public:
    explicit QxTdMessageForwardOriginChat(QObject *parent = nullptr);

    QString originSummary() const override;
    QString qmlChatId() const;
    qint64 chatId() const;
    QString authorSignature() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QxTdInt64 m_senderChatId;
    QString m_authorSignature;
    QString m_senderChatname;
};

/**
     * @brief The QxTdMessageForwardOriginChannel class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_channel.html
 */
class QxTdMessageForwardOriginChannel : public QxTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdMessageForwardOriginChannel)

public:
    explicit QxTdMessageForwardOriginChannel(QObject *parent = nullptr);

    QString originSummary() const override;
    QString qmlChatId() const;
    qint64 chatId() const;
    QString qmlMessageId() const;
    qint64 messageId() const;
    QString authorSignature() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QxTdInt64 m_chatId;
    QxTdInt64 m_messageId;
    QString m_authorSignature;
    QString m_senderChannelname;
};

/**
 * @brief The QxTdMessageForwardOriginHiddenUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_hidden_user.html
 */
class QxTdMessageForwardOriginHiddenUser : public QxTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdMessageForwardOriginHiddenUser)

public:
    explicit QxTdMessageForwardOriginHiddenUser(QObject *parent = nullptr);

    QString originSummary() const override;
    QString senderName() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QString m_senderName;
};

/**
 * @brief The QxTdMessageForwardOriginUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_origin_user.html
 */
class QxTdMessageForwardOriginUser : public QxTdMessageForwardOrigin
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdMessageForwardOriginUser)

public:
    explicit QxTdMessageForwardOriginUser(QObject *parent = nullptr);

    QString originSummary() const override;
    QString qmlSenderUserId() const;
    qint64 senderUserId() const;

    void unmarshalJson(const QJsonObject &json) override;

private:
    QxTdInt64 m_senderUserId;
    QString m_senderUsername;
};

#endif // QX_TD_MESSAGE_FORWARD_ORIGIN_H
