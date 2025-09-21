#include "qx_td_user.h"
#include "qx_td_user_status_factory.h"
#include "client/qx_td_client.h"
#include "common/qx_td_helpers.h"
#include "requests/qx_td_get_user_full_info_request.h"
#include "utils/qx_td_translate_tools.h"
#include "utils/qx_td_await.h"

QxTdUser::QxTdUser(QObject *parent)
    : QxAbstractInt64Id(parent)
    , m_fullInfo(new QxTdUserFullInfo)
    , m_status(nullptr)
    , m_profilePhoto(new QxTdProfilePhoto)
    , m_isVerified(false)
    , m_userType(nullptr)
    , m_userNames(nullptr)
    , m_emojiStatus(new QxTdEmojiStatus)
{
    setType(USER);
    m_my_id = QxTdClient::instance()->getOption("my_id").toLongLong();
}

void QxTdUser::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    setFirstName(json["first_name"].toString());
    setLastName(json["last_name"].toString());
    m_userNames.reset(new QxTdUsernames(this));
    m_userNames->unmarshalJson(json["usernames"].toObject());
    setPhoneNumber(json["phone_number"].toString());
    setStatus(QxTdUserStatusFactory::create(json["status"].toObject(), this));
    m_isVerified = json["is_verified"].toBool();
    emit isVerifiedChanged(m_isVerified);
    m_restrictionReason = json["restriction_reason"].toString();
    emit restrictionReasonChanged(m_restrictionReason);
    m_languageCode = json["language_code"].toString();
    emit languageCodeChanged(m_languageCode);

    const QJsonObject typeObj = json["type"].toObject();
    const QString type = typeObj["@type"].toString();
    if (type == "userTypeRegular") {
        setType(USER_TYPE_REGULAR);
        m_userType.reset(new QxTdUserTypeRegular(this));
    } else if (type == "userTypeBot") {
        m_userType.reset(new QxTdUserTypeBot(this));
    } else if (type == "userTypeDeleted") {
        m_userType.reset(new QxTdUserTypeDeleted(this));
        setFirstName("");
        setLastName("");
        emit isDeletedChanged();
    } else if (type == "userTypeUnknown") {
        m_userType.reset(new QxTdUserTypeUnknown(this));
    } else {
        m_userType.reset();
    }
    if (m_userType) {
        m_userType->unmarshalJson(typeObj);
    }

    m_profilePhoto->unmarshalJson(json["profile_photo"].toObject());
    emit profilePhotoChanged(m_profilePhoto.data());
    const bool hasProfilePhoto = m_profilePhoto->small()->id() > 0;
    const bool needsDownload = m_profilePhoto->small()->local()->path().isEmpty();
    if (hasProfilePhoto && needsDownload) {
        m_profilePhoto->small()->downloadFile();
    }

    m_emojiStatus.reset(new QxTdEmojiStatus(this));
    m_emojiStatus->unmarshalJson(json["emoji_status"].toObject());
    m_isContact = json["is_contact"].toBool();
    m_isMutualContact = json["is_mutual_contact"].toBool();
    m_isPremium = json["is_premium"].toBool();
    m_isSupport = json["is_support"].toBool();
    m_isScam = json["is_scam"].toBool();
    m_isFake = json["is_fake"].toBool();
    m_haveAccess = json["have_access"].toBool();

    QxAbstractInt64Id::unmarshalJson(json);

    emit dataChanged();
}

QxTdUserType *QxTdUser::userType() const
{
    return m_userType.data();
}

QString QxTdUser::restrictionReason() const
{
    return m_restrictionReason;
}

QString QxTdUser::languageCode() const
{
    return m_languageCode;
}

bool QxTdUser::isVerified() const
{
    return m_isVerified;
}

bool QxTdUser::isMyself()
{
    if (m_my_id == 0) {
        m_my_id = QxTdClient::instance()->getOption("my_id").toLongLong();
    }
    return id() == m_my_id;
}

bool QxTdUser::isOnline() const
{
    return m_status->typeString() == "userStatusOnline";
}

bool QxTdUser::isDeleted() const
{
    return qobject_cast<QxTdUserTypeDeleted*>(m_userType.data());
}

bool QxTdUser::isBot() const
{
    return qobject_cast<QxTdUserTypeBot*>(m_userType.data());
}

QxTdProfilePhoto *QxTdUser::profilePhoto() const
{
    return m_profilePhoto.data();
}

QxTdUserFullInfo *QxTdUser::fullInfo()
{
    return m_fullInfo.data();
}

QxTdUserStatus *QxTdUser::status() const
{
    return m_status.data();
}

void QxTdUser::setFirstName(QString firstName)
{
    if (m_firstName == firstName)
        return;

    m_firstName = firstName;
    emit nameChanged(m_firstName);
}

void QxTdUser::setLastName(QString lastName)
{
    if (m_lastName == lastName)
        return;

    m_lastName = lastName;
    emit nameChanged(m_lastName);
}

void QxTdUser::setPhoneNumber(QString phoneNumber)
{
    if (m_phoneNumber == phoneNumber)
        return;

    m_phoneNumber = phoneNumber;
    emit phoneNumberChanged(m_phoneNumber);
}

void QxTdUser::setFullInfo(QxTdUserFullInfo *fullInfo)
{
    m_fullInfo.reset(fullInfo);
    emit fullInfoChanged(m_fullInfo.data());
}

void QxTdUser::setStatus(QxTdUserStatus *status)
{
    QString oldStatusString = "";

    if (m_status) {
        oldStatusString = m_status->toString();
    }

    m_status.reset(status);
    emit statusChanged(m_status.data());

    if (m_status->toString() != oldStatusString) {
        emit m_status->statusStringChanged(m_status->toString());
    }
}

QString QxTdUser::firstName() const
{
    return m_firstName;
}

QString QxTdUser::lastName() const
{
    return m_lastName;
}

QString QxTdUser::username() const
{
    return m_userNames->editableUsername();
}

QString QxTdUser::fullName() const
{
    if (isDeleted()) {
        return qxTranslate("Deleted User");
    }
    if (m_firstName != "") {
        auto fullName = m_firstName;
        if (m_lastName != "")
            fullName = fullName + " " + m_lastName;
        return fullName;
    } else {
        return m_userNames->editableUsername();
    }
}

QString QxTdUser::phoneNumber() const
{
    return m_phoneNumber;
}

QString QxTdUser::initials() const
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
    if (m_userNames->editableUsername() != "") {
        return m_userNames->editableUsername().trimmed().left(2).toUpper();
    }
    return "";
}

QString QxTdUser::smallPhotoPath() const {
    if (isDeleted()) {
        return "image://theme/account";
    }
    return m_profilePhoto->smallPhotoPath();
}

QString QxTdUser::statusString() const {
    if (isBot()) {
        return qxTranslate("Bot");
    }
    return m_status->toString();
}

QString QxTdUser::avatarColor(qint64 userId)
{
    return QxTdHelpers::avatarColor(userId);
}

QxTdEmojiStatus* QxTdUser::emojiStatus() const {
    return m_emojiStatus.data();
}

bool QxTdUser::isContact() const {
    return m_isContact;
}

bool QxTdUser::isMutualContact() const {
    return m_isMutualContact;
}

bool QxTdUser::isPremium() const {
    return m_isPremium;
}

bool QxTdUser::isSupport() const {
    return m_isSupport;
}

bool QxTdUser::isScam() const {
    return m_isScam;
}

bool QxTdUser::isFake() const {
    return m_isFake;
}

bool QxTdUser::haveAccess() const {
    return m_haveAccess;
}
