#include "qx_td_enable_notifications.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QThread>
#include "client/qx_td_client.h"
#include "qx_td_register_device_request.h"

#define PUSHTOKEN_REREGISTER_TIME 14400

QxTdEnableNotifications::QxTdEnableNotifications(QObject *parent)
    : QObject(parent),
    m_registrationThread(nullptr)
{
    connect(QxTdClient::instance(), &QxTdClient::authStateChanged, [=](QxTdAuthState *state) {
        if (!m_token.isEmpty() && state->type() == QxTdAuthState::Type::AUTHORIZATION_STATE_READY) {
            registerDevice();
        }
    });

    connect(&m_watcher, &QFutureWatcher<QxTdResponse>::finished, this, &QxTdEnableNotifications::handleResponse);
}

QString QxTdEnableNotifications::token() const
{
    return m_token;
}

void QxTdEnableNotifications::setToken(const QString &token)
{
    if (token != m_token) {
        m_token = token;
    }
    emit tokenChanged();

    // Only register the device if we are authenticated and state is ready
    // We don't want to be sending this early as it could be sent before an account
    // is even configured (first time setup) and then it would require an app restart
    // to get this to send again. If it isn't sent now the authStateChanged connection
    // will register the device once ready.
    if (!m_token.isEmpty() && QxTdClient::instance()->authState()->type() == QxTdAuthState::Type::AUTHORIZATION_STATE_READY) {
        return registerDevice();
    }
    qDebug() << "Delaying registering device for push notification until account is authenticated";
}

void QxTdEnableNotifications::registerDevice()
{
    if (m_token.isEmpty()) {
        qWarning() << "Cannot register device. No push token set";
        return;
    }
    threadLocker.lock();
    if (m_registrationThread) {
        qWarning() << "push notification registration thread already running!";
        return;
    }
    m_registrationThread.reset(QThread::create([this]{
    QScopedPointer<QxTdRegisterDeviceRequest> req(new QxTdRegisterDeviceRequest);
    req->setToken(m_token);
        while(true) {
            qDebug() << "Registering device for push notifications";
            m_watcher.setFuture(req->sendAsync());
            QThread::sleep(PUSHTOKEN_REREGISTER_TIME);
        }
    }));
    m_registrationThread->start();
    threadLocker.unlock();
}

void QxTdEnableNotifications::handleResponse()
{
    const QxTdResponse resp = m_watcher.result();
    if (resp.isOk()) {
        qDebug() << "Push notifications enabled";
        emit enabled();
        return;
    }
    if (resp.isError()) {
        emit error(resp.errorString());
    }
}

QxTdEnableNotifications::~QxTdEnableNotifications()
{
    m_registrationThread->terminate();
}
