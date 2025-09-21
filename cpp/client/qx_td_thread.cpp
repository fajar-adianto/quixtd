#include "qx_td_thread.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>
#include <QCoreApplication>

#include <td/telegram/td_json_client.h>

QxTdWorker::QxTdWorker(QObject *parent)
    : QObject(parent)
    , m_tdlib(QxTdHandle::instance())
{
    // Intentionally left empty.
}

QxTdWorker::~QxTdWorker()
{
    m_tdlib.clear();
    emit destroyed();
}

void QxTdWorker::run()
{
    // enter the tdlib event loop
    forever {
        const QByteArray rcv = QByteArray(td_json_client_receive(m_tdlib->handle(), 1));
        if (!rcv.isEmpty()) {
            const QJsonObject json = QJsonDocument::fromJson(rcv).object();
            if (!json.isEmpty()) {
                emit recv(json);
                // if this is an authorizationStateClosed we should exit the event loop and destroy
                // the client.
                if (json["@type"] == "updateAuthorizationState") {
                    const QJsonObject state = json["authorization_state"].toObject();
                    if (state["@type"] == "authorizationStateClosed") {
                        emit finished();
                        break;
                    }
                }
            }
        }
    }
}
