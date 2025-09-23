#include "qx_td_auth_manager.h"
#include <QDebug>

#include "client/qx_td_client.h"
#include "requests/qx_td_auth_encryption_key_response.h"
#include "requests/qx_td_auth_parameters_response.h"
#include "requests/qx_td_auth_phone_number_response.h"
#include "requests/qx_td_auth_code_response.h"
#include "requests/qx_td_auth_registration_response.h"
#include "requests/qx_td_auth_logout_response.h"
#include "requests/qx_td_auth_password_response.h"
#include "requests/qx_td_auth_delete_account_response.h"
#include "requests/qx_td_auth_resend_code_request.h"

#include "utils/qx_td_await.h"

QxTdAuthManager::QxTdAuthManager(QObject *parent)
    : QObject(parent)
    , m_state(Invalid)
    , m_params(0)
{
    connect(QxTdClient::instance(),
            &QxTdClient::authStateChanged,
            this,
            &QxTdAuthManager::handleAuthStateChanged);

    // Manually run the update now as the client may already be initialized
    // so we want the *current* state to set us up correctly.
    if (QxTdClient::instance()->authState()) {
        handleAuthStateChanged(QxTdClient::instance()->authState());
    }
}

QxTdAuthManager::State QxTdAuthManager::state() const
{
    return m_state;
}

QxTdAuthState *QxTdAuthManager::type() const
{
    return QxTdClient::instance()->authState();
}

QxTdAuthParams *QxTdAuthManager::params() const
{
    return m_params;
}

void QxTdAuthManager::setParams(QxTdAuthParams *params)
{
    if (m_params == params)
        return;

    m_params = params;
    emit paramsChanged(m_params);
}

void QxTdAuthManager::sendParams()
{
    if (!m_params) {
        qWarning() << "Missing auth params. aborting...";
        return;
    }

    if (m_state != WaitTdParams) {
        qWarning() << "TDLib isn't waiting for this so not sending!";
        return;
    }
    std::unique_ptr<QxTdAuthParametersResponse> resp(new QxTdAuthParametersResponse);
    resp->setParameters(m_params);
    QxTdClient::instance()->send(resp.get());
}

void QxTdAuthManager::setEncryptionKey(const QString &key)
{
    if (m_state != WaitEncryptionKey) {
        qWarning() << "TDLib isn't waiting for the encryption key";
        return;
    }
    std::unique_ptr<QxTdAuthEncryptionKeyResponse> resp(new QxTdAuthEncryptionKeyResponse);
    resp->setKey(key);
    QxTdClient::instance()->send(resp.get());
}

void QxTdAuthManager::sendPhoneNumber(const QString &number)
{
    if (m_state != WaitPhoneNumber) {
        qWarning() << "TDLib isn't waiting for the phone number";
        return;
    }
    std::unique_ptr<QxTdAuthPhoneNumberResponse> autPhoneNoResp(new QxTdAuthPhoneNumberResponse);
    autPhoneNoResp->setPhoneNumber(number);
    QFuture<QxTdResponse> resp = autPhoneNoResp->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        emit phoneNumberError(resp.result().errorString());
        return;
    }
}

void QxTdAuthManager::shutDown()
{
    QxTdClient::instance()->shutDown();
}

void QxTdAuthManager::logOut()
{
    std::unique_ptr<QxTdAuthLogOutResponse> resp(new QxTdAuthLogOutResponse);
    QxTdClient::instance()->send(resp.get());
}

void QxTdAuthManager::deleteAccount(const QString &reason)
{
    std::unique_ptr<QxTdAuthDeleteAccountResponse> resp(new QxTdAuthDeleteAccountResponse);
    resp->setReason(reason);
    qWarning() << "Account deletion is disabled!";
    //QxTdClient::instance()->send(resp.get());
}

void QxTdAuthManager::sendCode(const QString &code)
{
    if (m_state != WaitCode) {
        qWarning() << "TDLib isn't waiting for a code";
        return;
    }
    std::unique_ptr<QxTdAuthCodeResponse> authCodeResp(new QxTdAuthCodeResponse);
    authCodeResp->setCode(code);
    QFuture<QxTdResponse> resp = authCodeResp->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QxTdAuthManager::resendCode()
{
    if (m_state != WaitCode) {
        qWarning() << "TDLib isn't waiting for a code";
        return;
    }
    std::unique_ptr<QxTdAuthResendCodeRequest> authResendCodeReq(new QxTdAuthResendCodeRequest);
    QFuture<QxTdResponse> resp = authResendCodeReq->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QxTdAuthManager::registerUser(const QString &firstname, const QString &lastname)
{
    if (m_state != WaitRegistration) {
        qWarning() << "TDLib isn't waiting for registration";
        return;
    }
    std::unique_ptr<QxTdAuthRegistrationResponse> authRegistrationResp(new QxTdAuthRegistrationResponse);
    authRegistrationResp->setFirstName(firstname);
    authRegistrationResp->setLastName(lastname);
    QFuture<QxTdResponse> resp = authRegistrationResp->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        emit codeError(resp.result().errorString());
        return;
    }
}

void QxTdAuthManager::sendPassword(const QString &password)
{
    if (m_state != WaitPassword) {
        qWarning() << "TDLib isn't waiting for a password";
        return;
    }
    std::unique_ptr<QxTdAuthPasswordResponse> authPasswordResp(new QxTdAuthPasswordResponse);
    authPasswordResp->setPassword(password);
    QFuture<QxTdResponse> resp = authPasswordResp->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        emit passwordError(resp.result().errorString());
        return;
    }
}

void QxTdAuthManager::handleAuthStateChanged(QxTdAuthState *state)
{
    if (!state)
        return;
    switch (state->type()) {
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_TDLIB_PARAMETERS: {
        m_state = WaitTdParams;
        emit waitingForTdParams();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_ENCRYPTION_KEY: {
        m_state = WaitEncryptionKey;
        emit waitingForEncryptionKey();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_REGISTRATION: {
        m_state = WaitRegistration;
        emit waitingForRegistration();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PHONE_NUMBER: {
        m_state = WaitPhoneNumber;
        emit waitingForPhoneNumber();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_CODE: {
        auto currentState = (QxTdAuthStateWaitCode *)state;
        emit waitingForCode(currentState->info()->type(), currentState->info()->nextType(), currentState->info()->timeout());
        m_state = WaitCode;
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_WAIT_PASSWORD: {
        m_state = WaitPassword;
        auto currentState = (QxTdAuthStateWaitPassword *)state;
        emit waitingForPassword(currentState->passwordHint(), currentState->hasRecoveryEmail(), currentState->recoveryEmail());
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_READY: {
        m_state = Ready;
        emit ready();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_LOGGING_OUT: {
        m_state = LoggingOut;
        emit loggingOut();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_CLOSING: {
        m_state = Closing;
        emit closing();
        break;
    }
    case QxTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
        m_state = Closed;
        emit closed();
        QCoreApplication::quit();
        break;
    }
    default:
        return;
    }
    emit stateChanged(m_state);
}
