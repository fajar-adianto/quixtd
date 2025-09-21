#ifndef QX_TD_USER_H
#define QX_TD_USER_H

#include "common/qx_abstract_int64_id.h"
#include "qx_td_user_full_info.h"
#include "qx_td_user_status.h"
#include "qx_td_profile_photo.h"
#include "qx_td_user_type.h"
#include "qx_td_usernames.h"
#include "qx_td_emoji_status.h"

/**
 * @brief The QxTdUser class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user.html
 */
class QxTdUser : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY nameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY nameChanged)
    Q_PROPERTY(QString username READ username NOTIFY nameChanged)
    Q_PROPERTY(QString fullName READ fullName NOTIFY nameChanged)
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY phoneNumberChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY initialsChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY smallPhotoPathChanged)
    Q_PROPERTY(QxTdUserFullInfo *fullInfo READ fullInfo WRITE setFullInfo NOTIFY fullInfoChanged)
    Q_PROPERTY(QxTdUserStatus *status READ status WRITE setStatus NOTIFY statusChanged)
    Q_PROPERTY(QxTdProfilePhoto *profilePhoto READ profilePhoto NOTIFY profilePhotoChanged)
    Q_PROPERTY(bool isVerified READ isVerified NOTIFY isVerifiedChanged)
    Q_PROPERTY(bool isMyself READ isMyself NOTIFY isMyselfChanged)
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY statusChanged)
    Q_PROPERTY(bool isDeleted READ isDeleted NOTIFY isDeletedChanged)
    Q_PROPERTY(bool isBot READ isBot NOTIFY isBotChanged)
    Q_PROPERTY(QString restrictionReason READ restrictionReason NOTIFY restrictionReasonChanged)
    Q_PROPERTY(QString statusString READ statusString NOTIFY statusChanged)
    Q_PROPERTY(QxTdUserType *userType READ userType NOTIFY userTypeChanged)
    Q_PROPERTY(QString languageCode READ languageCode NOTIFY languageCodeChanged)
    Q_PROPERTY(QxTdEmojiStatus* emojiStatus READ emojiStatus NOTIFY dataChanged)
    Q_PROPERTY(bool isContact READ isContact NOTIFY dataChanged)
    Q_PROPERTY(bool isMutualContact READ isMutualContact NOTIFY dataChanged)
    Q_PROPERTY(bool isPremium READ isPremium NOTIFY dataChanged)
    Q_PROPERTY(bool isSupport READ isSupport NOTIFY dataChanged)
    Q_PROPERTY(bool isScam READ isScam NOTIFY dataChanged)
    Q_PROPERTY(bool isFake READ isFake NOTIFY dataChanged)
    Q_PROPERTY(bool haveAccess READ haveAccess NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUser cannot be created in QML.")
public:
    explicit QxTdUser(QObject *parent = nullptr);

    QString firstName() const;
    QString lastName() const;
    QString username() const;
    QString fullName() const;
    QString phoneNumber() const;
    QString initials() const;
    QString smallPhotoPath() const;
    Q_INVOKABLE QString avatarColor(qint64 userId);
    QxTdUserFullInfo *fullInfo();
    QxTdUserStatus *status() const;
    QxTdProfilePhoto *profilePhoto() const;
    bool isVerified() const;
    bool isMyself();
    bool isOnline() const;
    bool isDeleted() const;
    bool isBot() const;
    QString restrictionReason() const;
    QString statusString() const;
    QString languageCode() const;
    QxTdUserType *userType() const;
    QxTdEmojiStatus* emojiStatus() const;
    bool isContact() const;
    bool isMutualContact() const;
    bool isPremium() const;
    bool isSupport() const;
    bool isScam() const;
    bool isFake() const;
    bool haveAccess() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void nameChanged(QString name);
    void phoneNumberChanged(QString phoneNumber);
    void initialsChanged(QString initials);
    void smallPhotoPathChanged();
    void fullInfoChanged(QxTdUserFullInfo *fullInfo);
    void statusChanged(QxTdUserStatus *status);
    void profilePhotoChanged(QxTdProfilePhoto *profilePhoto);
    void isVerifiedChanged(bool isVerified);
    void isMyselfChanged(bool isMyself);
    void isDeletedChanged();
    void isBotChanged();
    void restrictionReasonChanged(QString restrictionReason);
    void languageCodeChanged(QString languageCode);
    void dataChanged();
    void userTypeChanged(QxTdUserType *userType);

public slots:
    void setFirstName(QString firstName);
    void setLastName(QString lastName);
    void setPhoneNumber(QString phoneNumber);
    void setFullInfo(QxTdUserFullInfo *fullInfo);
    void setStatus(QxTdUserStatus *status);

private:
    Q_DISABLE_COPY(QxTdUser)
    QString m_firstName;
    QString m_lastName;
    QScopedPointer<QxTdUsernames> m_userNames;
    QString m_phoneNumber;
    qint64 m_my_id;
    QScopedPointer<QxTdUserFullInfo> m_fullInfo;
    QScopedPointer<QxTdUserStatus> m_status;
    QScopedPointer<QxTdProfilePhoto> m_profilePhoto;
    bool m_isVerified;
    QString m_restrictionReason;
    QString m_languageCode;
    QScopedPointer<QxTdUserType> m_userType;
    QScopedPointer<QxTdEmojiStatus> m_emojiStatus;
    bool m_isContact;
    bool m_isMutualContact;
    bool m_isPremium;
    bool m_isSupport;
    bool m_isScam;
    bool m_isFake;
    bool m_haveAccess;

};

#endif // QX_TD_USER_H
