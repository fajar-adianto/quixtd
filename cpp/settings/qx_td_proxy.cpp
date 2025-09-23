#include "qx_td_proxy.h"

#include "requests/qx_td_ping_proxy_request.h"

#include "asyncfuture.h"
using namespace AsyncFuture;

QxTdProxy::QxTdProxy(QObject *parent)
    : QxAbstractInt64Id(parent)
{
    // Intentionally left empty.
}

QString QxTdProxy::server() {
    return m_server;
}

qint32 QxTdProxy::port() {
    return m_port;
}

qint32 QxTdProxy::lastUsedDate() {
    return m_lastUsedDate;
}

bool QxTdProxy::isEnabled() {
    return m_isEnabled;
}

QxTdProxyType *QxTdProxy::type() {
    return m_type.get();
}

double QxTdProxy::ping()
{
    return m_ping;
}

void QxTdProxy::setPing(double value)
{
    if (m_ping != value) {
        m_ping = value;
        emit pingChanged();
    }
}

void QxTdProxy::unmarshalJson(const QJsonObject &json)
{
    QxAbstractInt64Id::unmarshalJson(json);
    m_server = json["server"].toString();
    m_port = (int)json["port"].toDouble();
    m_lastUsedDate = (int)json["last_used_date"].toDouble();
    m_isEnabled = json["is_enabled"].toBool();
    m_type.reset(QxTdProxyType::create(json["type"].toObject(), this));
    requestProxyServerPing();
    emit dataChanged();
}


void QxTdProxy::requestProxyServerPing() {
    m_ping = -1;
    std::unique_ptr<QxTdPingProxyRequest> req(new QxTdPingProxyRequest);
    req->setId(id());
    auto future = req->sendAsync();
    AsyncFuture::observe(future).subscribe([this](QxTdResponse resp) {
        if (resp.isError()) {
            auto errorMessage = resp.errorString();
            qWarning() << "Error during pinging proxy:" << errorMessage;
            emit pingError(id(), errorMessage);
            return;
        }
        setPing(resp.json()["seconds"].toDouble() * 1000);
        emit pingError(id(), "");
    });
}

