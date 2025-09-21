#ifndef QX_TD_AWAIT_H
#define QX_TD_AWAIT_H
#include <QFuture>
#include <QFutureWatcher>
#include <QEventLoop>
#include <QTimer>

template<typename T>
inline void qxAwait(QFuture<T> future, int timeout = -1)
{
    if (future.isFinished()) {
        return;
    }

    QFutureWatcher<T> watcher;
    watcher.setFuture(future);
    QEventLoop loop;

    if (timeout > 0) {
        QTimer::singleShot(timeout, &loop, &QEventLoop::quit);
    }

    QObject::connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
    loop.exec();
}

#endif // QX_TD_AWAIT_H
