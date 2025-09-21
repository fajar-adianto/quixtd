#include "qx_td_contact.h"

#include <QVariant>
#include <QDebug>
#include <QScopedPointer>

#include "qx_td_users.h"
#include "requests/qx_td_search_user_by_phone_number_request.h"

#include "asyncfuture.h"
using namespace AsyncFuture;

QxTdContact::QxTdContact(QObject *parent)
    : QxTdObject(parent)
    , m_user(nullptr)
    , m_firstName("")
    , m_lastName("")
    , m_phoneNumber("")
    , m_vcard("")
    , m_userId(0)
{
    setType(CONTACT);
}

QString QxTdContact::firstName() const
{
    return m_firstName;
}

void QxTdContact::setFirstName(QString value)
{
    m_firstName = value;
}

QString QxTdContact::lastName() const
{
  return m_lastName;
}

void QxTdContact::setLastName(QString value)
{
    m_lastName = value;
}

QString QxTdContact::phoneNumber() const
{
    return m_phoneNumber;
}

void QxTdContact::setPhoneNumber(QString value)
{
    m_phoneNumber = value;
}

QString QxTdContact::vcard() const
{
    return m_vcard;
}

void QxTdContact::setVcard(QString value)
{
    m_vcard = value;
}

qint64 QxTdContact::userId() const
{
    return m_userId;
}

void QxTdContact::setUserId(qint64 value)
{
    m_userId = value;
}

QxTdUser *QxTdContact::user() const {
    return m_user;
}

QString QxTdContact::initials() const
{
    if (m_firstName != "") {
        if (m_lastName != "") {
            return (m_firstName.trimmed().left(1) + m_lastName.trimmed().left(1)).toUpper();
        }
        return m_firstName.trimmed().left(2).toUpper();
    }
    if (m_lastName != "") {
        return m_lastName.trimmed().left(2).toUpper();
    }
    return "";
}

void QxTdContact::getUserFromModel(qint64 userId) {
    auto user = QxTdUsers::instance()->model()->getByUid(QString::number(userId));
    if (user) {
        m_userId = userId;
        m_user = user;
        emit userChanged();
    }
}

void QxTdContact::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_firstName = json["first_name"].toString();
    m_lastName = json["last_name"].toString();
    m_phoneNumber = json["phone_number"].toString();
    m_vcard = json["vcard"].toString();
    getUserFromModel(json["user_id"].toVariant().toLongLong());
    if (!m_user) {
        qWarning() << "QxTdContact: User was not found in users datamodel, trying to search on Telegram server...";
        QScopedPointer<QxTdSearchUserByPhoneNumberRequest> req(new QxTdSearchUserByPhoneNumberRequest());
        req->setPhoneNumber(m_phoneNumber);
        auto future = req->sendAsync();
        AsyncFuture::observe(future).subscribe([this](QxTdResponse resp) {
            if (resp.isError()) {
                auto errorMessage = resp.errorString();
                qWarning() << "Error:" << errorMessage;
                return;
            }
            auto id = resp.json()["id"].toVariant().toLongLong();
            QxTdUsers::instance()->handleUpdateUser(resp.json());
            getUserFromModel(id);
        });
    }
    emit dataChanged();
}

QJsonObject QxTdContact::marshalJson() {
    return QJsonObject{
        { "@type", "contact" },
        { "first_name", m_firstName },
        { "last_name", m_lastName },
        { "phone_number", m_phoneNumber },
        { "vcard", m_vcard },
        { "user_id", m_userId }
    };
}
