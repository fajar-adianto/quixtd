#include "qx_td_connection_state_factory.h"
#include "qx_td_connection_state.h"
#include <QDebug>

QxTdConnectionState *QxTdConnectionStateFactory::create(const QJsonObject &json, QObject *parent)
{
    const auto state = json["state"].toObject();
    const QString type = state["@type"].toString();
    if (type == "connectionStateReady") {
        return new QxTdConnectionStateReady(parent);
    } else if (type == "connectionStateUpdating") {
        return new QxTdConnectionStateUpdating(parent);
    } else if (type == "connectionStateConnecting") {
        return new QxTdConnectionStateConnecting(parent);
    } else if (type == "connectionStateConnectingToProxy") {
        return new QxTdConnectionStateConnectingToProxy(parent);
    } else if (type == "connectionStateWaitingForNetwork") {
        return new QxTdConnectionStateWaitingForNetwork(parent);
    }
    return nullptr;
}
