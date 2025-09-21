#include "qx_td_connection_manager.h"
#include <QDebug>
#include <QtGui/QGuiApplication>
#include "client/qx_td_client.h"

QxTdConnectionManager::QxTdConnectionManager(QObject *parent)
    : QObject(parent)
    , m_connectionState(WaitingForNetwork)
{
    connect(QxTdClient::instance(),
            &QxTdClient::connectionStateChanged,
            this,
            &QxTdConnectionManager::handleConnectionStateChanged);

    // Manually run the update now as the client may already be initialized
    // so we want the *current* state to set us up correctly.
    if (QxTdClient::instance()->connectionState()) {
        handleConnectionStateChanged(QxTdClient::instance()->connectionState());
    }
    connect(qGuiApp, &QGuiApplication::applicationStateChanged, this,
            &QxTdConnectionManager::handleApplicationStateChanged);
}

QxTdConnectionManager::ConnectionState QxTdConnectionManager::connectionState() const
{
    return m_connectionState;
}

bool QxTdConnectionManager::connectivityOnline() const
{
    return m_connectivity_online;
}

void QxTdConnectionManager::setConnectivityOnline(bool value)
{
#if defined(__amd64__)
    qDebug() << "ConnectivityOnline on amd64 as online";
    value = 1;
#endif
    if (m_connectivity_online != value) {
        m_connectivity_online = value;
        emit connectivityOnlineChanged(value);
        setTdLibNetworkState();
    }
}

void QxTdConnectionManager::handleConnectionStateChanged(QxTdConnectionState *state)
{
    if (!state)
        return;
    switch (state->type()) {
    case QxTdConnectionState::Type::CONNECTION_STATE_WAITING_FOR_NETWORK: {
        m_connectionState = WaitingForNetwork;
        emit waitingForNetwork();
        break;
    }
    case QxTdConnectionState::Type::CONNECTION_STATE_CONNECTING_TO_PROXY: {
        m_connectionState = ConnectingToProxy;
        emit connectingToProxy();
        break;
    }
    case QxTdConnectionState::Type::CONNECTION_STATE_CONNECTING: {
        m_connectionState = Connecting;
        emit connecting();
        break;
    }
    case QxTdConnectionState::Type::CONNECTION_STATE_UPDATING: {
        m_connectionState = Updating;
        emit updating();
        break;
    }
    case QxTdConnectionState::Type::CONNECTION_STATE_READY: {
        m_connectionState = Ready;
        emit ready();
        break;
    }
    default:
        return;
    }
    emit connectionStateChanged(m_connectionState);
}

void QxTdConnectionManager::handleApplicationStateChanged(Qt::ApplicationState state)
{
    auto application_suspended = state == Qt::ApplicationState::ApplicationSuspended;
    if (m_application_suspended != application_suspended) {
        m_application_suspended = application_suspended;
        setTdLibNetworkState();
    }
}

void QxTdConnectionManager::setTdLibNetworkState()
{
    if (m_connectivity_online && !m_application_suspended) {
        QxTdClient::instance()->send(QJsonObject{
                { "@type", "setNetworkType" },
                { "type", QJsonObject{ { "@type", "networkTypeMobile" } } } });
    } else {
        QxTdClient::instance()->send(QJsonObject{
                { "@type", "setNetworkType" },
                { "type", QJsonObject{ { "@type", "networkTypeNone" } } } });
    }
}
