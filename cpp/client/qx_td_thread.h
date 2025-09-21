#ifndef QX_TD_THREAD_H
#define QX_TD_THREAD_H

#include <QObject>
#include <QDebug>
#include <QJsonObject>
#include "qx_td_handle.h"

/**
 * @brief The QxTdWorker class
 *
 * This worker is designed to be run on a QThread and events
 * proxied back
 */
class QxTdWorker : public QObject
{
    Q_OBJECT
public:
    explicit QxTdWorker(QObject *parent = nullptr);
    ~QxTdWorker();

signals:
    void recv(const QJsonObject &data);
    void finished();
    void destroyed();

public slots:
    void run();

private:
    Q_DISABLE_COPY(QxTdWorker)
    QSharedPointer<Handle> m_tdlib;
};

#endif // QX_TD_THREAD_H
