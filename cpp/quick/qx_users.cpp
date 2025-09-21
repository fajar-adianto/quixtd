#include "qx_users.h"
#include "user/qx_td_users.h"

QxUsers::QxUsers(QObject *parent)
    : QObject(parent)
{
    emit modelChanged();
    connect(QxTdUsers::instance(), &QxTdUsers::meMyselfChanged, this, &QxUsers::meChanged);
}

QObject *QxUsers::model() const
{
    return QxTdUsers::instance()->model();
}

QxTdUser *QxUsers::meMyself() const
{
    return QxTdUsers::instance()->meMyself();
}

void QxUsers::deleteUser(const int &userId)
{
    QxTdUsers::instance()->deleteUser(userId);
}

void QxUsers::addUser(const QString &userName, const QString &firstName, const QString &lastName)
{
    QxTdUsers::instance()->addUser(userName, firstName, lastName);
}

void QxUsers::addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId) {
    QxTdUsers::instance()->addContact(phoneNumber, firstName, lastName, userId);
}

void QxUsers::blockUser(const qint64 userId)
{
    QxTdUsers::instance()->blockUser(userId);
}
