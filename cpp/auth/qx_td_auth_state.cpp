#include "qx_td_auth_state.h"

QxTdAuthStateWaitParams::QxTdAuthStateWaitParams(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS);
}

QxTdAuthStateWaitEncryptionKey::QxTdAuthStateWaitEncryptionKey(QObject *parent)
    : QxTdAuthState(parent)
    , m_encrypted(false)
{
    setType(AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY);
}

bool QxTdAuthStateWaitEncryptionKey::isEncrypted() const
{
    return m_encrypted;
}

void QxTdAuthStateWaitEncryptionKey::setIsEncrypted(const bool encrypted)
{
    if (encrypted != m_encrypted) {
        m_encrypted = encrypted;
        emit isEncryptedChanged(m_encrypted);
    }
}

void QxTdAuthStateWaitEncryptionKey::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthState::unmarshalJson(json);
    if (json.contains("is_encrypted")) {
        setIsEncrypted(json["is_encrypted"].toBool());
    }
}

QxTdAuthStateWaitRegistration::QxTdAuthStateWaitRegistration(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_REGISTRATION);
}

QxTdAuthStateWaitPhoneNumber::QxTdAuthStateWaitPhoneNumber(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_WAIT_PHONE_NUMBER);
}

QxTdAuthStateWaitCode::QxTdAuthStateWaitCode(QObject *parent)
    : QxTdAuthState(parent)
    , m_info(0)
{
    setType(AUTHORIZATION_STATE_WAIT_CODE);
}

QxTdAuthCodeInfo *QxTdAuthStateWaitCode::info() const
{
    return m_info;
}

void QxTdAuthStateWaitCode::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthState::unmarshalJson(json);
    m_info = new QxTdAuthCodeInfo(this);
    m_info->unmarshalJson(json["code_info"].toObject());
    emit infoChanged();
}

QxTdAuthStateWaitPassword::QxTdAuthStateWaitPassword(QObject *parent)
    : QxTdAuthState(parent)
    , m_hasRecovery(false)
{
    setType(AUTHORIZATION_STATE_WAIT_PASSWORD);
}

QString QxTdAuthStateWaitPassword::passwordHint() const
{
    return m_hint;
}

QString QxTdAuthStateWaitPassword::recoveryEmail() const
{
    return m_recovery;
}

bool QxTdAuthStateWaitPassword::hasRecoveryEmail() const
{
    return m_hasRecovery;
}

void QxTdAuthStateWaitPassword::unmarshalJson(const QJsonObject &json)
{
    QxTdAuthState::unmarshalJson(json);
    m_hint = json["password_hint"].toString();
    m_recovery = json["recovery_email_address_pattern"].toString();
    m_hasRecovery = json["has_recovery_email_address"].toBool();
    emit dataChanged();
}

QxTdAuthStateReady::QxTdAuthStateReady(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_READY);
}

QxTdAuthStateLoggingOut::QxTdAuthStateLoggingOut(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_LOGGING_OUT);
}

QxTdAuthStateClosing::QxTdAuthStateClosing(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_CLOSING);
}

QxTdAuthStateClosed::QxTdAuthStateClosed(QObject *parent)
    : QxTdAuthState(parent)
{
    setType(AUTHORIZATION_STATE_CLOSED);
}
