#include "qx_contacts.h"
#include "user/qx_td_users.h"

QxContacts::QxContacts(QObject *parent)
    : QObject(parent)
{
    emit modelChanged();
    connect(QxTdUsers::instance(), &QxTdUsers::meMyselfChanged, this, &QxContacts::meChanged);
}

QObject *QxContacts::model() const
{
    return QxTdUsers::instance()->contactsmodel();
}

QxTdUser *QxContacts::meMyself() const
{
    return QxTdUsers::instance()->meMyself();
}
