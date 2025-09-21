#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include "qx_td_auth_state.h"
#include "qx_td_auth_params.h"
#include "auth/qx_td_auth_code.h"

class QxTdAuthManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(State state READ state NOTIFY stateChanged)
    Q_PROPERTY(QxTdAuthState *type READ type NOTIFY stateChanged)
    Q_PROPERTY(QxTdAuthParams *params READ params WRITE setParams NOTIFY paramsChanged)
    QML_ELEMENT
public:
    explicit QxTdAuthManager(QObject *parent = nullptr);

    enum State {
        Invalid,
        WaitTdParams,
        WaitEncryptionKey,
        WaitRegistration,
        WaitPhoneNumber,
        WaitCode,
        WaitPassword,
        Ready,
        LoggingOut,
        Closing,
        Closed
    };
    Q_ENUM(State)
    State state() const;
    QxTdAuthState *type() const;

    QxTdAuthParams *params() const;

public slots:
    void setParams(QxTdAuthParams *params);
    void sendParams();
    void setEncryptionKey(const QString &key);
    void sendPhoneNumber(const QString &number);
    void sendCode(const QString &code);
    void resendCode();
    void registerUser(const QString &firstname, const QString &lastname = "");
    void sendPassword(const QString &password);
    void shutDown();
    void logOut();
    void deleteAccount(const QString &reason);

signals:
    void stateChanged(State state);
    void waitingForTdParams();
    void waitingForEncryptionKey();
    void waitingForRegistration();
    void waitingForPhoneNumber();
    void waitingForCode(QxTdAuthCode *type, QxTdAuthCode *nextType, qint32 resendTimeout);
    void waitingForPassword(QString passwordHint, bool hasRecoveryEmailAddress, QString recoveryEmailAddressPattern);
    void phoneNumberError(QString message);
    void codeError(QString message);
    void passwordError(QString message);
    void ready();
    void loggingOut();
    void closing();
    void closed();

    void paramsChanged(QxTdAuthParams *params);

private slots:
    void handleAuthStateChanged(QxTdAuthState *state);

private:
    State m_state;
    QxTdAuthParams *m_params;
};

#endif // AUTHMANAGER_H
