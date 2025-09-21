#ifndef QX_CONTACTS_H
#define QX_CONTACTS_H

#include "user/qx_td_user.h"

class QxContacts : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ model NOTIFY modelChanged)
    Q_PROPERTY(QxTdUser* me READ meMyself NOTIFY meChanged)
    QML_ELEMENT
public:
    explicit QxContacts(QObject *parent = nullptr);

    QObject* model() const;
    QxTdUser* meMyself() const;

signals:
    void modelChanged();
    void meChanged();
};

#endif // USERS_H
