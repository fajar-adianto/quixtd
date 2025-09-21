#include "qx_td_auth_state_factory.h"
#include "qx_td_auth_state.h"

#include <QDebug>

QxTdAuthState *QxTdAuthStateFactory::create(const QJsonObject &data, QObject *parent)
{
    const QJsonObject state = data["authorization_state"].toObject();
    const QString type = state["@type"].toString();
    qDebug() << "[AUTHSTATE] " << type;
    QxTdAuthState *stateObj = nullptr;
    if (type == "authorizationStateWaitTdlibParameters") {
        stateObj = new QxTdAuthStateWaitParams(parent);
    } else if (type == "authorizationStateWaitEncryptionKey") {
        stateObj = new QxTdAuthStateWaitEncryptionKey(parent);
    } else if (type == "authorizationStateWaitRegistration") {
        stateObj = new QxTdAuthStateWaitRegistration(parent);
    } else if (type == "authorizationStateWaitPhoneNumber") {
        stateObj = new QxTdAuthStateWaitPhoneNumber(parent);
    } else if (type == "authorizationStateWaitCode") {
        stateObj = new QxTdAuthStateWaitCode(parent);
    } else if (type == "authorizationStateReady") {
        stateObj = new QxTdAuthStateReady(parent);
    } else if (type == "authorizationStateLoggingOut") {
        stateObj = new QxTdAuthStateLoggingOut(parent);
    } else if (type == "authorizationStateClosing") {
        stateObj = new QxTdAuthStateClosing(parent);
    } else if (type == "authorizationStateClosed") {
        stateObj = new QxTdAuthStateClosed(parent);
    } else if (type == "authorizationStateWaitPassword") {
        stateObj = new QxTdAuthStateWaitPassword(parent);
    } else {
        qWarning() << "Unknown auth state type: " << type;
    }

    if (stateObj) {
        stateObj->unmarshalJson(state);
    }
    return stateObj;
}
