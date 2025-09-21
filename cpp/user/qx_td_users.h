#ifndef QX_TD_USERS_H
#define QX_TD_USERS_H

#include <QPointer>
#include <QSortFilterProxyModel>

#include "auth/qx_td_auth_state.h"
#include "models/qx_td_object_list_model.h"
#include "user/qx_td_user.h"


/**
 * @brief The QxTdUsersSortFilterModel class
 *
 * Filters users to only show the allowed user ids
 *
 * This makes it easier to reuse the global user instance
 * to just show a subset of user.
 */
class QxTdUsersSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdUsersSortFilterModel)
    Q_PROPERTY(int count READ rowCount NOTIFY rowCountChanged)
    QML_ELEMENT
public:
    explicit QxTdUsersSortFilterModel(QObject *parent = nullptr);
    Q_INVOKABLE QxTdUser *get(const int &row);

public slots:
    void setAllowedUsers(QList<qint64> user_ids);

signals:
    void countChanged();
    void allowedUsersChanged();
    void rowCountChanged();

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const;

private:
    QList<qint64> m_uids;
};

class QxTdUsers : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QObject* model READ qmlModel NOTIFY modelChanged)
    Q_PROPERTY(QxTdUser* me READ meMyself NOTIFY meMyselfChanged)
    Q_PROPERTY(QObject *contactsmodel READ qmlContactsModel NOTIFY contactsChanged)
    QML_ELEMENT
public:
    explicit QxTdUsers(QObject *parent = nullptr);
    ~QxTdUsers();

    static QxTdUsers *instance();

    QObject* qmlModel() const;
    QObject *qmlContactsModel() const;
    QxTdUser* meMyself() const;

    QxTdObjectListModel<QxTdUser> *model() const;
    QxTdUsersSortFilterModel *contactsmodel() const;

public slots:
    void deleteUser(const int &userId);
    void addUser(const QString &userName, const QString &firstName, const QString &lastName);
    void addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId);
    void blockUser(const qint64 userId);
    void handleUpdateUser(const QJsonObject &user);

signals:
    void modelChanged(QObject* model);
    void userCreated(qint64 id);
    void meMyselfChanged(QxTdUser *meMyself);
    void contactsChanged();
    void contactsImported(int existingUsers, int importedContacts);

private slots:
    void handleUpdateUserStatus(const QString &userId, const QJsonObject &status);
    void handleAuthStateChanged(const QxTdAuthState *state);
    void handleContacts(const QJsonObject &contacts);
    void handleUpdateUserFullInfo(const QString &userId, const QJsonObject &fullInfo);

private:
    Q_DISABLE_COPY(QxTdUsers)
    QxTdObjectListModel<QxTdUser> *m_model;
    QPointer<QxTdUser> m_meMyself;
    QxTdUsersSortFilterModel *m_contactsmodel;
    QList<qint64> m_contact_ids;
    void getAllContacts();
};

#endif // QX_TD_USERS_H
