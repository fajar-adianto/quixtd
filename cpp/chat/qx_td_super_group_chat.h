#ifndef QX_TD_SUPER_GROUP_CHAT_H
#define QX_TD_SUPER_GROUP_CHAT_H

#include <QObject>

#include "qx_td_chat.h"
#include "qx_td_chat_member_status.h"
#include "user/qx_td_usernames.h"

class QxTdSuperGroupChat : public QxTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY superGroupChanged)
    Q_PROPERTY(QString userName READ userName NOTIFY superGroupChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY superGroupChanged)
    Q_PROPERTY(QxTdChatMemberStatus *status READ status NOTIFY superGroupChanged)
    Q_PROPERTY(bool signMessages READ signMessages NOTIFY superGroupChanged)
    Q_PROPERTY(bool isChannel READ isChannel NOTIFY superGroupChanged)
    Q_PROPERTY(bool isVerified READ isVerified NOTIFY superGroupChanged)
    Q_PROPERTY(QString restrictionReason READ restrictionReason NOTIFY superGroupChanged)

    // SuperGroupFullInfo properties
    Q_PROPERTY(QString description READ description NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString adminCount READ qmlAdminCount NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString restrictedCount READ qmlRestrictedCount NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString bannedCount READ qmlBannedCount NOTIFY superGroupInfoChanged)
    Q_PROPERTY(bool isAllHistoryAvailable READ isHistoryAvailable NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString stickerSetId READ qmlStickerSetId NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString pinnedMessageId READ qmlPinnedMessageId NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString upgradedFromBasicGroupId READ qmlUpgradedFromBasicGroupId NOTIFY superGroupInfoChanged)
    Q_PROPERTY(QString upgradedFromMaxMessageId READ qmlUpgradedFromMaxMessageId NOTIFY superGroupInfoChanged)
    QML_ELEMENT
public:
    explicit QxTdSuperGroupChat(QObject *parent = nullptr);

    QString qmlSuperGroupId() const;
    qint64 superGroupId() const;
    QString userName() const;
    QDateTime qmlDate() const;
    qint32 date() const;
    QxTdChatMemberStatus *status() const;
    QString qmlMemberCount() const;
    qint32 memberCount() const;
    bool signMessages() const;
    bool isChannel() const;
    bool isVerified() const;
    bool isWritable() const override;
    QString restrictionReason() const;
    QString description() const;
    QString qmlAdminCount() const;
    qint32 adminCount() const;
    QString qmlRestrictedCount() const;
    qint32 restrictedCount() const;
    QString qmlBannedCount() const;
    qint32 bannedCount() const;
    bool isHistoryAvailable() const;
    QString qmlStickerSetId() const;
    qint64 stickerSetId() const;
    QString inviteLink() const;
    QString qmlPinnedMessageId() const;
    qint64 pinnedMessageId() const;
    QString qmlUpgradedFromBasicGroupId() const;
    qint64 upgradedFromBasicGroupId() const;
    QString qmlUpgradedFromMaxMessageId() const;
    qint64 upgradedFromMaxMessageId() const;

signals:
    void superGroupChanged();
    void superGroupInfoChanged();

protected:
    virtual void onChatDeserialized() override;

private slots:
    void getSuperGroupData();
    void updateSuperGroup(const QJsonObject &json);
    void getSuperGroupFullInfo();
    void updateSuperGroupFullInfo(const QJsonObject &json);
    void superGroupFullInfo(const QJsonObject &info);

private:
    void parseSuperGroupId();
    Q_DISABLE_COPY(QxTdSuperGroupChat)
    QxTdInt64 m_sgId;
    std::unique_ptr<QxTdUsernames> m_userNames;
    qint32 m_date;
    std::unique_ptr<QxTdChatMemberStatus> m_status;
    QxTdInt32 m_memberCount;
    bool m_signMessages;
    bool m_isChannel;
    bool m_isVerified;
    QString m_restrictionReason;
    QString m_description;
    QxTdInt32 m_adminCount;
    QxTdInt32 m_restrictedCount;
    QxTdInt32 m_bannedCount;
    bool m_canGetMembers;
    bool m_canSetUsername;
    bool m_canSetStickerSet;
    bool m_historyAvailable;
    QxTdInt64 m_stickerSet;
    QString m_inviteLink;
    QxTdInt64 m_pinnedMessageId;
    QxTdInt32 m_upgradeGroupId;
    QxTdInt64 m_upgradeMaxMsgId;
};

#endif // QX_TD_SUPER_GROUP_CHAT_H
