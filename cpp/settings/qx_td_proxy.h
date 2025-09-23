#ifndef QX_TD_PROXY_H
#define QX_TD_PROXY_H

#include <QObject>

#include "qx_td_proxy_type.h"
#include "common/qx_abstract_int64_id.h"

class QxTdProxy : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString server READ server NOTIFY dataChanged)
    Q_PROPERTY(qint32 port READ port NOTIFY dataChanged)
    Q_PROPERTY(qint32 lastUsedDate READ lastUsedDate NOTIFY dataChanged)
    Q_PROPERTY(bool isEnabled READ isEnabled NOTIFY dataChanged)
    Q_PROPERTY(QxTdProxyType *type READ type NOTIFY dataChanged)
    Q_PROPERTY(double ping READ ping NOTIFY pingChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdProxy cannot be created in QML.")
public:
    explicit QxTdProxy(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json) override;

    QString server();
    qint32 port();
    qint32 lastUsedDate();
    bool isEnabled();
    QxTdProxyType *type();
    double ping();
    void setPing(double value);
    
signals:
    void dataChanged();
    void pingChanged();
    void pingError(int id, QString errorMessage);

private:
    void requestProxyServerPing();
    QString m_server;
    qint32 m_port;
    qint32 m_lastUsedDate;
    bool m_isEnabled;
    std::unique_ptr<QxTdProxyType> m_type;
    double m_ping;
};

#endif // QX_TD_PROXY_H
