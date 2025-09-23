#include "qx_td_users.h"

#include "qx_td_user_status_factory.h"
#include "client/qx_td_client.h"
#include "common/qx_td_int.h"
#include "requests/qx_td_block_user_request.h"
#include "requests/qx_td_get_contacts_request.h"
#include "requests/qx_td_get_user_request.h"
#include "requests/qx_td_import_contacts_request.h"
#include "requests/qx_td_remove_contacts_request.h"
#include "utils/qx_td_await.h"

QxTdUsers::QxTdUsers(QObject *parent)
    : QObject(parent)
    , m_model(nullptr)
    , m_contactsmodel(new QxTdUsersSortFilterModel)
    , m_meMyself(nullptr)
{
    m_model = new QxTdObjectListModel<QxTdUser>(this, "", "id");
    m_contactsmodel->setSourceModel(m_model);
    m_meMyself = new QxTdUser(this);
    connect(QxTdClient::instance(), &QxTdClient::updateUser, this, &QxTdUsers::handleUpdateUser);
    connect(QxTdClient::instance(), &QxTdClient::updateUserStatus, this, &QxTdUsers::handleUpdateUserStatus);
    connect(QxTdClient::instance(), &QxTdClient::authStateChanged, this, &QxTdUsers::handleAuthStateChanged);
    connect(QxTdClient::instance(), &QxTdClient::updateUserFullInfo, this, &QxTdUsers::handleUpdateUserFullInfo);
}

QxTdUsers::~QxTdUsers()
{
    m_model->clear();
}

QObject *QxTdUsers::qmlModel() const
{
    return m_model;
}

QObject *QxTdUsers::qmlContactsModel() const
{
    return m_contactsmodel;
}

QxTdObjectListModel<QxTdUser> *QxTdUsers::model() const
{
    return m_model;
}

QxTdUsersSortFilterModel *QxTdUsers::contactsmodel() const
{
    return m_contactsmodel;
}

static QPointer<QxTdUsers> s_users;
QxTdUsers *QxTdUsers::instance()
{
    if (s_users.isNull()) {
        s_users = new QxTdUsers();
    }
    return s_users;
}

QxTdUser *QxTdUsers::meMyself() const
{
    return m_meMyself;
}

void QxTdUsers::addUser(const QString &userName, const QString &firstName, const QString &lastName)
{
    qWarning() << "Trying to find and add user" << userName << firstName << lastName;
    std::unique_ptr<QxTdContact> newContact(new QxTdContact);
    newContact->setPhoneNumber(userName);
    newContact->setFirstName(firstName);
    newContact->setLastName(lastName);
    std::unique_ptr<QxTdImportContactsRequest> importContactsReq(new QxTdImportContactsRequest());
    QList<QxTdContact *> contacts;
    contacts.append(newContact.get());
    importContactsReq->setContacts(contacts);
    QFuture<QxTdResponse> resp = importContactsReq->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to import contacts with error: " << resp.result().errorString();
        return;
    }
    QJsonObject result = resp.result().json();
    auto existingUsers = result["user_ids"].toArray();
    auto importedContacts = (int)result["importer_count"].toDouble();
    emit contactsImported(existingUsers.count(), importedContacts);
    getAllContacts();
}

void QxTdUsers::addContact(const QString &phoneNumber, const QString &firstName, const QString &lastName, const qint64 userId) {
    std::unique_ptr<QxTdContact> newContact(new QxTdContact);
    newContact->setPhoneNumber(phoneNumber);
    newContact->setFirstName(firstName);
    newContact->setLastName(lastName);
    newContact->setUserId(userId);
    QJsonObject addContactRequest = QJsonObject {
        { "@type", "addContact" },
        { "contact", newContact->marshalJson() }
    };
    QxTdClient::instance()->send(addContactRequest);
}

void QxTdUsers::deleteUser(const int &userId)
{
    QList<qint64> deleteUserIds;
    deleteUserIds.append(userId);
    std::unique_ptr<QxTdRemoveContactsRequest> deleteUserReq(new QxTdRemoveContactsRequest);
    deleteUserReq->setUserIds(deleteUserIds);
    QFuture<QxTdResponse> resp = deleteUserReq->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get contacts with error: " << resp.result().errorString();
        return;
    }
    getAllContacts();
}

void QxTdUsers::blockUser(const qint64 userId) {
    std::unique_ptr<QxTdBlockUserRequest> req(new QxTdBlockUserRequest);
    req->setUserId(userId);
    req->sendAsync();
}

void QxTdUsers::handleUpdateUser(const QJsonObject &user)
{
    const qint64 uid = user["id"].toVariant().toLongLong();
    // Need to remember the model actually indexes on the qmlId variant which is a QString
    QxTdUser *tduser = m_model->getByUid(QString::number(uid));
    if (!tduser) {
        tduser = new QxTdUser();
        tduser->unmarshalJson(user);
        m_model->append(tduser);
        emit userCreated(uid);
    } else {
        tduser->unmarshalJson(user);
    }

    const qint64 myId = QxTdClient::instance()->getOption("my_id").toLongLong();
    if (uid == myId) {
        m_meMyself->unmarshalJson(user);
        emit meMyselfChanged(m_meMyself);
    }
}

void QxTdUsers::handleUpdateUserStatus(const QString &userId, const QJsonObject &status)
{
    QxTdUser *tduser = m_model->getByUid(userId);
    if (tduser) {
        tduser->setStatus(QxTdUserStatusFactory::create(status, tduser));
    }

    const qint64 uid = userId.toLongLong();
    const qint64 myId = QxTdClient::instance()->getOption("my_id").toLongLong();
    if (uid == myId) {
        m_meMyself->setStatus(QxTdUserStatusFactory::create(status, m_meMyself));
    }
}

void QxTdUsers::getAllContacts()
{
    std::unique_ptr<QxTdGetContactsRequest> req(new QxTdGetContactsRequest);
    QFuture<QxTdResponse> resp = req->sendAsync();
    qxAwait(resp);
    if (resp.result().isError()) {
        qWarning() << "Failed to get contacts with error: " << resp.result().errorString();
        return;
    }
    handleContacts(resp.result().json());
}

void QxTdUsers::handleAuthStateChanged(const QxTdAuthState *state)
{
    switch (state->type()) {
        case QxTdAuthState::Type::AUTHORIZATION_STATE_READY: {
            getAllContacts();
            break;
        }
        case QxTdAuthState::Type::AUTHORIZATION_STATE_CLOSED: {
            m_model->clear();
            break;
        }
        default:
            break;
    }
}

void QxTdUsers::handleContacts(const QJsonObject &contacts)
{
    const QJsonArray contactlist = contacts["user_ids"].toArray();
    std::unique_ptr<QxTdGetUserRequest> getUserReq(new QxTdGetUserRequest);
    m_contact_ids.clear();
    for (const QJsonValue &contact : contactlist) {
        qint64 contactId = contact.toVariant().toLongLong();
        QxTdUser *contactObj = m_model->getByUid(QString::number(contactId));
        m_contact_ids.append(contactId);
        if (!contactObj) {
            qWarning() << "Trying to load missing contact:" << contactId;
            getUserReq->setUserId(contactId);
            getUserReq->sendAsync();
        }
    }
    m_contactsmodel->setAllowedUsers(m_contact_ids);
    emit contactsChanged();
}

void QxTdUsers::handleUpdateUserFullInfo(const QString &userId, const QJsonObject &fullInfo)
{
    QxTdUser *tduser = m_model->getByUid(userId);
    if (tduser) {
        tduser->fullInfo()->unmarshalJson(fullInfo);
    }
}

QxTdUsersSortFilterModel::QxTdUsersSortFilterModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setDynamicSortFilter(true);
    sort(0, Qt::AscendingOrder);
    connect(this, &QxTdUsersSortFilterModel::countChanged, this, &QxTdUsersSortFilterModel::rowCountChanged);
}

QxTdUser *QxTdUsersSortFilterModel::get(const int &row)
{
    QModelIndex idx = index(row, 0);
    if (idx.isValid()) {
        QModelIndex srcIdx = mapToSource(idx);
        if (srcIdx.isValid()) {
            QxTdObjectListModel<QxTdUser> *model = static_cast<QxTdObjectListModel<QxTdUser> *>(sourceModel());
            return model->at(srcIdx.row());
        }
    }
    return nullptr;
}

void QxTdUsersSortFilterModel::setAllowedUsers(QList<qint64> user_ids)
{
    if (user_ids == m_uids) {
        return;
    }
    m_uids = user_ids;
    emit allowedUsersChanged();
    invalidateFilter();
}

bool QxTdUsersSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QxTdObjectListModel<QxTdUser> *model = static_cast<QxTdObjectListModel<QxTdUser> *>(sourceModel());
    QxTdUser *user = model->at(source_row);
    if (!user) {
        return false;
    }
    auto filtered = m_uids.contains(user->id());
    return filtered;
}

bool QxTdUsersSortFilterModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const
{
    QxTdObjectListModel<QxTdUser> *model = static_cast<QxTdObjectListModel<QxTdUser> *>(sourceModel());
    QxTdUser *left = model->at(source_left.row());
    QxTdUser *right = model->at(source_right.row());

    QString compareStringLeft = !left->firstName().isEmpty()
            ? left->firstName()
            : !left->lastName().isEmpty()
                    ? left->lastName()
                    : left->username();

    QString compareStringRight = !right->firstName().isEmpty()
            ? right->firstName()
            : !right->lastName().isEmpty()
                    ? right->lastName()
                    : right->username();
    auto result = QString::localeAwareCompare(compareStringLeft, compareStringRight) < 0;
    return result;
}
