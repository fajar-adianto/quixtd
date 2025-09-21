#ifndef QX_USERS_H
#define QX_USERS_H

#include "user/qx_td_user.h"

class QxUsers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *model READ model NOTIFY modelChanged)
    Q_PROPERTY(QxTdUser *me READ meMyself NOTIFY meChanged)
    QML_ELEMENT
public:
    explicit QxUsers(QObject *parent = nullptr);

    QObject *model() const;
    QxTdUser *meMyself() const;

public slots:
    void deleteUser(const int &userId);
    void addUser(const QString &userName, const QString &firstName, const QString &lastName);
    void addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId);
    void blockUser(const qint64 userId);

signals:
    void modelChanged();
    void meChanged();
};

#endif // QX_USERS_H
