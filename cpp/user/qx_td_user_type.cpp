#include "qx_td_user_type.h"

QxTdUserType::QxTdUserType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

void QxTdUserType::unmarshalJson(const QJsonObject &json) {
    QxTdObject::unmarshalJson(json);
}

QxTdUserTypeBot::QxTdUserTypeBot(QObject *parent)
    : QxTdUserType(parent)
    , m_canJoinGroups(false)
    , m_canReadAllGroupMessages(false)
    , m_isInline(false)
    , m_needLocation(false)
{
    setType(USER_TYPE_BOT);
}

bool QxTdUserTypeBot::canJoinGroups() const
{
    return m_canJoinGroups;
}

bool QxTdUserTypeBot::canReadAllGroupMessages() const
{
    return m_canReadAllGroupMessages;
}

bool QxTdUserTypeBot::isInline() const
{
    return m_isInline;
}

QString QxTdUserTypeBot::placeholder() const
{
    return m_inlineQueryPlaceholder;
}

bool QxTdUserTypeBot::needLocation() const
{
    return m_needLocation;
}

void QxTdUserTypeBot::unmarshalJson(const QJsonObject &json)
{
    QxTdUserType::unmarshalJson(json);
    m_canJoinGroups = json["can_join_groups"].toBool();
    m_canReadAllGroupMessages = json["can_read_all_group_messages"].toBool();
    m_isInline = json["is_inline"].toBool();
    m_inlineQueryPlaceholder = json["inline_query_placeholder"].toString();
    m_needLocation = json["need_location"].toBool();
    emit userTypeDataChanged();
}

QxTdUserTypeDeleted::QxTdUserTypeDeleted(QObject *parent)
    : QxTdUserType(parent)
{
    setType(USER_TYPE_DELETED);
}

QxTdUserTypeRegular::QxTdUserTypeRegular(QObject *parent)
    : QxTdUserType(parent)
{
    setType(USER_TYPE_REGULAR);
}

QxTdUserTypeUnknown::QxTdUserTypeUnknown(QObject *parent)
    : QxTdUserType(parent)
{
    setType(USER_TYPE_UNKNOWN);
}
