#include "qx_td_connection_state.h"

QxTdConnectionState::QxTdConnectionState(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdConnectionStateWaitingForNetwork::QxTdConnectionStateWaitingForNetwork(QObject *parent)
    : QxTdConnectionState(parent)
{
    setType(CONNECTION_STATE_WAITING_FOR_NETWORK);
}

QxTdConnectionStateConnectingToProxy::QxTdConnectionStateConnectingToProxy(QObject *parent)
    : QxTdConnectionState(parent)
{
    setType(CONNECTION_STATE_CONNECTING_TO_PROXY);
}

QxTdConnectionStateConnecting::QxTdConnectionStateConnecting(QObject *parent)
    : QxTdConnectionState(parent)
{
    setType(CONNECTION_STATE_CONNECTING);
}

QxTdConnectionStateUpdating::QxTdConnectionStateUpdating(QObject *parent)
    : QxTdConnectionState(parent)
{
    setType(CONNECTION_STATE_UPDATING);
}

QxTdConnectionStateReady::QxTdConnectionStateReady(QObject *parent)
    : QxTdConnectionState(parent)
{
    setType(CONNECTION_STATE_READY);
}
