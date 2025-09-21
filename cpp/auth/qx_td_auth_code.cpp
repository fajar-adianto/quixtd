#include "qx_td_auth_code.h"
#include <QDebug>

QxTdAuthCode::QxTdAuthCode(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdAuthCodeTelegramMessage::QxTdAuthCodeTelegramMessage(QObject *parent)
    : QxTdAuthCode(parent)
    , m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_TELEGRAM_MESSAGE);
}

QString QxTdAuthCodeTelegramMessage::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QxTdAuthCodeTelegramMessage::length() const
{
    return m_length.value();
}

void QxTdAuthCodeTelegramMessage::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthCode::unmarshalJson(json);
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
}

QxTdAuthCodeSms::QxTdAuthCodeSms(QObject *parent)
    : QxTdAuthCode(parent)
    , m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_SMS);
}

QString QxTdAuthCodeSms::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QxTdAuthCodeSms::length() const
{
    return m_length.value();
}

void QxTdAuthCodeSms::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthCode::unmarshalJson(json);
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
}

QxTdAuthCodeCall::QxTdAuthCodeCall(QObject *parent)
    : QxTdAuthCode(parent)
    , m_length(0)
{
    setType(AUTHENTICATION_CODE_TYPE_CALL);
}

QString QxTdAuthCodeCall::qmlLength() const
{
    return m_length.toQmlValue();
}

qint32 QxTdAuthCodeCall::length() const
{
    return m_length.value();
}

void QxTdAuthCodeCall::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthCode::unmarshalJson(json);
    if (json.contains("length")) {
        m_length = json["length"];
        emit lengthChanged();
    }
}

QxTdAuthCodeFlashCall::QxTdAuthCodeFlashCall(QObject *parent)
    : QxTdAuthCode(parent)
{
    setType(AUTHENTICATION_CODE_TYPE_FLASH_CALL);
}

QString QxTdAuthCodeFlashCall::pattern() const
{
    return m_pattern;
}

void QxTdAuthCodeFlashCall::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthCode::unmarshalJson(json);
    if (json.contains("pattern")) {
        m_pattern = json["pattern"].toString();
        emit patternChanged();
    }
}

QxTdAuthCodeInfo::QxTdAuthCodeInfo(QObject *parent)
    : QxTdObject(parent)
    , m_timeout(0)
    , m_type(0)
    , m_nextType(0)
{
    // Intentionally left empty.
}

QString QxTdAuthCodeInfo::qmlTimeout() const
{
    return m_timeout.toQmlValue();
}

qint32 QxTdAuthCodeInfo::timeout() const
{
    return m_timeout.value();
}

QxTdAuthCode *QxTdAuthCodeInfo::type() const
{
    return m_type;
}

QxTdAuthCode *QxTdAuthCodeInfo::nextType() const
{
    return m_nextType;
}

void QxTdAuthCodeInfo::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_timeout = json["timeout"];
    if (m_type) {
        delete m_type;
        m_type = 0;
    }
    m_type = QxTdAuthCodeInfo::create(json["type"].toObject(), this);
    if (m_nextType) {
        delete m_nextType;
        m_nextType = 0;
    }
    m_nextType = QxTdAuthCodeInfo::create(json["next_type"].toObject(), this);
    emit infoChanged();
}

QxTdAuthCode *QxTdAuthCodeInfo::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    if (type == QStringLiteral("authenticationCodeTypeSms")) {
        QxTdAuthCodeSms *sms = new QxTdAuthCodeSms(parent);
        sms->unmarshalJson(json);
        return sms;
    } else if (type == QStringLiteral("authenticationCodeTypeTelegramMessage")) {
        QxTdAuthCodeTelegramMessage *msg = new QxTdAuthCodeTelegramMessage(parent);
        msg->unmarshalJson(json);
        return msg;
    } else if (type == QStringLiteral("authenticationCodeTypeCall")) {
        QxTdAuthCodeCall *msg = new QxTdAuthCodeCall(parent);
        msg->unmarshalJson(json);
        return msg;
    } else if (type == QStringLiteral("authenticationCodeTypeFlashCall")) {
        QxTdAuthCodeFlashCall *msg = new QxTdAuthCodeFlashCall(parent);
        msg->unmarshalJson(json);
        return msg;
    }
    return nullptr;
}
