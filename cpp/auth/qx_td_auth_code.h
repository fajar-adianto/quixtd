#ifndef QX_TD_AUTH_CODE_H
#define QX_TD_AUTH_CODE_H

#include "common/qx_td_object.h"
#include "common/qx_td_int.h"

/**
 * @brief The QxTdAuthCode class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_authentication_code_type.html
 */
class QxTdAuthCode : public QxTdObject
{
    Q_OBJECT
public:
    explicit QxTdAuthCode(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthCodeTelegramMessage class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_telegram_message.html
 */
class QxTdAuthCodeTelegramMessage : public QxTdAuthCode
{
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthCode and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthCodeTelegramMessage(QObject *parent = 0);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void lengthChanged();

private:
    QxTdInt32 m_length;
};

/**
 * @brief The QxTdAuthCodeSms class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_sms.html
 */
class QxTdAuthCodeSms : public QxTdAuthCode
{
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthCode and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthCodeSms(QObject *parent = nullptr);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void lengthChanged();

private:
    QxTdInt32 m_length;
};

/**
 * @brief The QxTdAuthCodeCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_call.html
 */
class QxTdAuthCodeCall : public QxTdAuthCode
{
    Q_OBJECT
    Q_PROPERTY(QString length READ qmlLength NOTIFY lengthChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthCode and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthCodeCall(QObject *parent = nullptr);

    QString qmlLength() const;
    qint32 length() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void lengthChanged();

private:
    QxTdInt32 m_length;
};

/**
 * @brief The QxTdAuthCodeFlashCall class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_type_flash_call.html
 */
class QxTdAuthCodeFlashCall : public QxTdAuthCode
{
    Q_OBJECT
    Q_PROPERTY(QString pattern READ pattern NOTIFY patternChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthCode and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthCodeFlashCall(QObject *parent = nullptr);

    QString pattern() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void patternChanged();

private:
    QString m_pattern;
};

/**
 * @brief The QxTdAuthCodeInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authentication_code_info.html
 */
class QxTdAuthCodeInfo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString timeout READ qmlTimeout NOTIFY infoChanged)
    Q_PROPERTY(QxTdAuthCode *type READ type NOTIFY infoChanged)
    Q_PROPERTY(QxTdAuthCode *nextType READ nextType NOTIFY infoChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthCodeInfo cannot be created in QML.")
public:
    explicit QxTdAuthCodeInfo(QObject *parent = nullptr);

    QString qmlTimeout() const;
    qint32 timeout() const;

    QxTdAuthCode *type() const;
    QxTdAuthCode *nextType() const;

    void unmarshalJson(const QJsonObject &json) override;

    static QxTdAuthCode *create(const QJsonObject &json, QObject *parent);

signals:
    void infoChanged();

private:
    QxTdInt32 m_timeout;
    QxTdAuthCode *m_type;
    QxTdAuthCode *m_nextType;
};

#endif // QX_TD_AUTH_CODE_H
