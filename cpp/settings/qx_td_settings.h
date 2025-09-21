#ifndef QX_TD_SETTINGS_H
#define QX_TD_SETTINGS_H

#include <QObject>
#include <QScopedPointer>
#include "common/qx_td_object.h"
#include "models/qx_td_object_list_model.h"
#include "qx_td_proxy.h"

class QxTdSettings : public QxTdObject {

    Q_OBJECT
    Q_PROPERTY(QObject *proxies READ qmlProxies NOTIFY proxiesChanged)
    QML_ELEMENT
public:
    explicit QxTdSettings(QObject *parent = nullptr);

    QObject *qmlProxies() const;
    QxTdObjectListModel<QxTdProxy> *proxies() const;

    Q_INVOKABLE void addOrEditProxyServer(qint32 id, QString server, qint32 port, qint32 type, QString username, QString password, QString secret, bool httpOnly, bool enable);
    Q_INVOKABLE void deleteProxyServer(qint32 id);
    Q_INVOKABLE void enableProxyServer(qint32 id);
    Q_INVOKABLE void disableProxyServer();
    Q_INVOKABLE void fetchProxyServers();

signals:
    void proxiesChanged();
    void proxyManagementError(QString errorMessage);
    void proxyPingError(int id, QString errorMessage);

private:
    void handleProxyServers(const QJsonObject &json);

    QScopedPointer<QxTdObjectListModel<QxTdProxy>> m_proxies;
};

#endif // QX_TD_SETTINGS_H
