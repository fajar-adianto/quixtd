#ifndef QX_TD_ENABLE_NOTIFICATIONS_H
#define QX_TD_ENABLE_NOTIFICATIONS_H

#include <QObject>
#include <QMutex>
#include <QFutureWatcher>
#include <QtQmlIntegration/qqmlintegration.h>

#include "common/qx_td_response.h"

class QxTdEnableNotifications : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
    QML_ELEMENT
public:
    explicit QxTdEnableNotifications(QObject *parent = nullptr);

    QString token() const;

    void setToken(const QString &token);

    ~QxTdEnableNotifications();

signals:
    void enabled();
    void error(QString error);
    void tokenChanged();

private slots:
    void registerDevice();
    void handleResponse();

private:
    Q_DISABLE_COPY(QxTdEnableNotifications)
    QString m_token;
    QMutex threadLocker;
    QFutureWatcher<QxTdResponse> m_watcher;
    std::unique_ptr<QThread> m_registrationThread;

};

#endif // QX_TD_ENABLE_NOTIFICATIONS_H
