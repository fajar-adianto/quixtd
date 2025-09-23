#include "qx_td_settings.h"

#include <QJsonObject>
#include <QJsonArray>

#include "utils/qx_td_await.h"
#include "client/qx_td_client.h"
#include "requests/qx_td_get_proxies_request.h"
#include "requests/qx_td_add_proxy_request.h"
#include "requests/qx_td_edit_proxy_request.h"
#include "requests/qx_td_remove_proxy_request.h"
#include "requests/qx_td_enable_proxy_request.h"
#include "requests/qx_td_disable_proxy_request.h"

QxTdSettings::QxTdSettings(QObject *parent)
    : QxTdObject(parent)
{
    m_proxies.reset(new QxTdObjectListModel<QxTdProxy>(this, "", "id"));
    connect(QxTdClient::instance(), &QxTdClient::proxy, this, &QxTdSettings::fetchProxyServers);
}

QObject *QxTdSettings::qmlProxies() const
{
    return m_proxies.get();
}

QxTdObjectListModel<QxTdProxy> *QxTdSettings::proxies() const
{
    return m_proxies.get();
}

void QxTdSettings::addOrEditProxyServer(qint32 id, QString server, qint32 port, qint32 type, QString username, QString password, QString secret, bool httpOnly, bool enable)
{
    std::unique_ptr<QxTdProxyType> typeObject;
    QxTdProxyType *proxyType = nullptr;
    switch(type) {
        case 0:
        {
            proxyType = new QxTdProxyTypeHttp();
            proxyType->setUsername(username);
            proxyType->setPassword(password);
            proxyType->setHttpOnly(httpOnly);
            break;
        }
        case 1:
        {
            proxyType = new QxTdProxyTypeMtproto();
            proxyType->setSecret(secret);
            break;
        }
        case 2:
        {
            proxyType = new QxTdProxyTypeSocks5();
            proxyType->setUsername(username);
            proxyType->setPassword(password);
            break;
        }
    }
    typeObject.reset(proxyType);

    QFuture<QxTdResponse> resp;
    if (id == -1) {
        std::unique_ptr<QxTdAddProxyRequest> req(new QxTdAddProxyRequest());
        req->setServer(server);
        req->setPort(port);
        req->setType(typeObject.get());
        req->setEnable(enable);
        resp = req->sendAsync();
    } else {
        std::unique_ptr<QxTdEditProxyRequest> req(new QxTdEditProxyRequest());
        req->setId(id);
        req->setServer(server);
        req->setPort(port);
        req->setType(typeObject.get());
        req->setEnable(enable);
        resp = req->sendAsync();
    }
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during adding/editing proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
    }
}

void QxTdSettings::deleteProxyServer(qint32 id)
{
    std::unique_ptr<QxTdRemoveProxyRequest> req(new QxTdRemoveProxyRequest());
    req->setId(id);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during deleting proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    auto proxy = (QxTdProxy*) m_proxies->get(QString::number(id));
    m_proxies->remove(proxy);
    fetchProxyServers();
}

void QxTdSettings::disableProxyServer()
{
    std::unique_ptr<QxTdDisableProxyRequest> req(new QxTdDisableProxyRequest());
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during disabling proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    fetchProxyServers();
}

void QxTdSettings::enableProxyServer(qint32 id)
{
    std::unique_ptr<QxTdEnableProxyRequest> req(new QxTdEnableProxyRequest());
    req->setId(id);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during enabling proxy:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    fetchProxyServers();
}

void QxTdSettings::fetchProxyServers()
{
    std::unique_ptr<QxTdGetProxiesRequest> req(new QxTdGetProxiesRequest);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Error during getting proxies:" << resp.result().errorString();
        emit proxyManagementError(resp.result().errorString());
        return;
    }
    handleProxyServers(resp.result().json());

}

void QxTdSettings::handleProxyServers(const QJsonObject &json)
{
    auto array = json["proxies"].toArray();
    for (auto value : array) {
        auto json = value.toObject();
        auto proxy = (QxTdProxy*) m_proxies->get(QString::number(json["id"].toDouble()));
        if (!proxy) {
            proxy = new QxTdProxy(this);
            connect(proxy, &QxTdProxy::pingError, this, &QxTdSettings::proxyPingError);
            m_proxies.get()->append(proxy);
        }       
        proxy->unmarshalJson(json);
    }
    emit proxiesChanged();
}

