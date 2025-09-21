#ifndef QX_TD_AUTH_STATE_H
#define QX_TD_AUTH_STATE_H

#include "common/qx_td_object.h"
#include "qx_td_auth_code.h"

/**
 * @brief The QxTdAuthState class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_authorization_state.html
 */
class QxTdAuthState : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthState(QObject *parent = nullptr)
        : QxTdObject(parent)
    {
        // Intentionally left empty.
    }
};

/**
 * @brief The QxTdAuthStateWaitParams class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_tdlib_parameters.html
 */
class QxTdAuthStateWaitParams : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateWaitParams(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateWaitEncryptionKey class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_encryption_key.html
 */
class QxTdAuthStateWaitEncryptionKey : public QxTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(bool isEncrypted READ isEncrypted NOTIFY isEncryptedChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateWaitEncryptionKey(QObject *parent = nullptr);

    bool isEncrypted() const;

signals:
    void isEncryptedChanged(bool encrypted);

protected:
    void setIsEncrypted(const bool encrypted);

private:
    bool m_encrypted;

    // QAbstractTdObject interface
public:
    void unmarshalJson(const QJsonObject &json) override;
};

/**
 * @brief The QxTdAuthStateWaitRegistration class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_registration.html
 */
class QxTdAuthStateWaitRegistration : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
    // TODO termsOfService
public:
    explicit QxTdAuthStateWaitRegistration(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateWaitPhoneNumber class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_phone_number.html
 */
class QxTdAuthStateWaitPhoneNumber : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateWaitPhoneNumber(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateWaitCode class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_code.html
 */
class QxTdAuthStateWaitCode : public QxTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(QxTdAuthCodeInfo *info READ info NOTIFY infoChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateWaitCode(QObject *parent = nullptr);

    QxTdAuthCodeInfo *info() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void infoChanged();
    void isRegisteredChanged();

private:
    bool m_isRegistered;
    QxTdAuthCodeInfo *m_info;
};

/**
 * @brief The QxTdAuthStateWaitPassword class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_wait_password.html
 */
class QxTdAuthStateWaitPassword : public QxTdAuthState
{
    Q_OBJECT
    Q_PROPERTY(QString passwordHint READ passwordHint NOTIFY dataChanged)
    Q_PROPERTY(bool hasRecoveryEmail READ hasRecoveryEmail NOTIFY dataChanged)
    Q_PROPERTY(QString recoveryEmail READ recoveryEmail NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateWaitPassword(QObject *parent = nullptr);

    QString passwordHint() const;
    QString recoveryEmail() const;
    bool hasRecoveryEmail() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void dataChanged();

private:
    QString m_hint;
    bool m_hasRecovery;
    QString m_recovery;
};

/**
 * @brief The QxTdAuthStateReady class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_ready.html
 */
class QxTdAuthStateReady : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateReady(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateLoggingOut class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_logging_out.html
 */
class QxTdAuthStateLoggingOut : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateLoggingOut(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateClosing class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_closing.html
 */
class QxTdAuthStateClosing : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateClosing(QObject *parent = nullptr);
};

/**
 * @brief The QxTdAuthStateClosed class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1authorization_state_closed.html
 */
class QxTdAuthStateClosed : public QxTdAuthState
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAuthState and its derived classes cannot be created in QML.")
public:
    explicit QxTdAuthStateClosed(QObject *parent = nullptr);
};

#endif // QX_TD_AUTH_STATE_H
