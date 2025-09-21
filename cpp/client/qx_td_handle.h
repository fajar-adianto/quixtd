#ifndef QX_TD_HANDLE_H
#define QX_TD_HANDLE_H

#include <QObject>
#include <QSharedPointer>

/**
 * @brief The Handle class
 *
 * Wraps the td_json_client handle so it can
 * be stored in a QSharedPointer allowing sharing
 * of the instance across threads
 */
class Handle
{
    void *m_handle;

public:
    explicit Handle();
    void *handle();
};

/**
 * @brief The QxTdHandle class
 *
 * Holds a static QSharedPointer<Handle> instance
 *
 * Access to the underlying handle can be done with
 *
 * QxTdHandle::instance()->handle()
 */
struct QxTdHandle
{
    static QSharedPointer<Handle> instance();
};

#endif // QX_TD_HANDLE_H
