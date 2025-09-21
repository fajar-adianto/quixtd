#ifndef QX_TD_CHAT_TYPE_H
#define QX_TD_CHAT_TYPE_H

#include "common/qx_td_object.h"
#include "common/qx_td_int.h"
#include "user/qx_td_user.h"

/**
 * @brief The QxTdChatType class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_chat_type.html
 */
class QxTdChatType : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatType and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdChatType)
public:
    explicit QxTdChatType(QObject *parent = nullptr);

};

/**
 * @brief The QxTdChatTypeBasicGroup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_basic_group.html
 */
class QxTdChatTypeBasicGroup : public QxTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString basicGroupId READ qmlBasicGroupId NOTIFY groupIdChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatType and its derived classes cannot be created in QML.")
public:
    explicit QxTdChatTypeBasicGroup(QObject *parent = nullptr);

    QString qmlBasicGroupId() const;
    qint64 basicGroupId() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void groupIdChanged();

private:
    Q_DISABLE_COPY(QxTdChatTypeBasicGroup)
    QxTdInt64 m_groupId;
};

/**
 * @brief The QxTdChatTypePrivate class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_private.html
 */
class QxTdChatTypePrivate : public QxTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString userId READ qmlUserId NOTIFY userIdChanged)
    Q_PROPERTY(QxTdUser *user READ user NOTIFY userChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatType and its derived classes cannot be created in QML.")
public:
    explicit QxTdChatTypePrivate(QObject *parent = nullptr);

    QString qmlUserId() const;
    qint64 userId() const;
    QxTdUser *user() const;

    virtual void unmarshalJson(const QJsonObject &json) override;
    
signals:
    void userIdChanged();
    void userChanged();

private:
    Q_DISABLE_COPY(QxTdChatTypePrivate)
    QxTdInt64 m_userId;
    QxTdUser *m_user;
    bool m_waitingForUser;

    void updateUser(const qint64 &userId);
};

/**
 * @brief The QxTdChatTypeSecret class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_secret.html
 */
class QxTdChatTypeSecret : public QxTdChatTypePrivate
{
    Q_OBJECT
    Q_PROPERTY(QString secretChatId READ qmlSecretChatId NOTIFY secretChatIdChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatType and its derived classes cannot be created in QML.")
public:
    explicit QxTdChatTypeSecret(QObject *parent = nullptr);

    QString qmlSecretChatId() const;
    qint64 secretChatId() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void secretChatIdChanged();

private:
    Q_DISABLE_COPY(QxTdChatTypeSecret)
    QxTdInt64 m_chatId;
};

/**
 * @brief The QxTdChatTypeSuperGroup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1chat_type_supergroup.html
 */
class QxTdChatTypeSuperGroup : public QxTdChatType
{
    Q_OBJECT
    Q_PROPERTY(QString superGroupId READ qmlSuperGroupId NOTIFY superGroupIdChanged)
    Q_PROPERTY(bool isChannel READ isChannel NOTIFY isChannelChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatType and its derived classes cannot be created in QML.")
public:
    explicit QxTdChatTypeSuperGroup(QObject *parent = nullptr);

    QString qmlSuperGroupId() const;
    qint64 superGroupId() const;
    bool isChannel() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void superGroupIdChanged();
    void isChannelChanged();

private:
    Q_DISABLE_COPY(QxTdChatTypeSuperGroup)
    QxTdInt64 m_groupId;
    bool m_isChannel;
};

#endif // QX_TD_CHAT_TYPE_H
