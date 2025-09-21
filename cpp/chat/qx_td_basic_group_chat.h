#ifndef QX_TD_BASIC_GROUP_CHAT_H
#define QX_TD_BASIC_GROUP_CHAT_H

#include <QMap>
#include <QPointer>
#include "qx_td_chat.h"
#include "qx_td_chat_member_status.h"
#include "qx_td_chat_member.h"

class QxTdBasicGroupChat : public QxTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString groupId READ qmlGroupId NOTIFY groupChanged)
    Q_PROPERTY(QString memberCount READ qmlMemberCount NOTIFY groupChanged)
    Q_PROPERTY(QxTdChatMemberStatus *status READ status NOTIFY groupChanged)
    Q_PROPERTY(bool isActive READ isActive NOTIFY groupChanged)
    Q_PROPERTY(QString upgradedToSuperGroupId READ qmlUpgradedToSuperGroupId NOTIFY groupChanged)

    // BasicGroupFullInfo properties
    Q_PROPERTY(QString creatorUserId READ qmlCreatorUserId NOTIFY groupInfoChanged)
    Q_PROPERTY(QObject *members READ qmlMembers NOTIFY groupInfoChanged)
    Q_PROPERTY(QString inviteLink READ inviteLink NOTIFY groupInfoChanged)
    QML_ELEMENT
public:
    explicit QxTdBasicGroupChat(QObject *parent = nullptr);

    QString qmlGroupId() const;
    qint64 groupId() const;
    QString qmlMemberCount() const;
    qint32 memberCount() const;
    QxTdChatMemberStatus *status() const;
    bool isActive() const;
    QString qmlUpgradedToSuperGroupId() const;
    qint64 upgradedToSuperGroupId() const;
    QString qmlCreatorUserId() const;
    qint64 creatorUserId() const;
    QObject *qmlMembers() const;
    QxTdObjectListModel<QxTdChatMember> *members() const;
    QString inviteLink() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void groupChanged();
    void groupInfoChanged();

protected:
    virtual void onChatDeserialized() override;

private slots:
    void requestGroupData();
    void updateGroupData(const QJsonObject &json);
    void updateGroupInfo(const QJsonObject &json);

private:
    Q_DISABLE_COPY(QxTdBasicGroupChat)
    QxTdInt64 m_groupId;
    QxTdInt32 m_memberCount;
    QScopedPointer<QxTdChatMemberStatus> m_status;
    bool m_isActive;
    QxTdInt64 m_upgradedSGID;
    QxTdInt64 m_creatorId;
    QPointer<QxTdObjectListModel<QxTdChatMember>> m_members;
    QString m_inviteLink;
};

#endif // QX_TD_BASIC_GROUP_CHAT_H
