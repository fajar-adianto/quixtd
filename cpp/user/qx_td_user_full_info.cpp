#include "qx_td_user_full_info.h"

QxTdUserFullInfo::QxTdUserFullInfo(QObject *parent)
    : m_isBlocked(false)
    , m_canBeCalled(false)
    , m_hasPrivateCalls(false)
    , m_bio(QString())
    , m_shareText(QString())
    , m_groupInCommonCount(0)
{
    setType(USER_FULL_INFO);
}

void QxTdUserFullInfo::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_isBlocked = json["is_blocked"].toBool();
    m_canBeCalled = json["can_be_called"].toBool();
    m_hasPrivateCalls = json["has_private_calls"].toBool();
    m_bio = json["bio"].toString();
    m_shareText = json["share_text"].toString();
    m_groupInCommonCount = json["group_in_common_count"].toInt();

    emit userFullInfoChanged();
}

bool QxTdUserFullInfo::isBlocked() const
{
    return m_isBlocked;
}

bool QxTdUserFullInfo::canBeCalled() const
{
    return m_canBeCalled;
}

bool QxTdUserFullInfo::hasPrivateCalls() const
{
    return m_hasPrivateCalls;
}

QString QxTdUserFullInfo::bio() const
{
    return m_bio;
}

QString QxTdUserFullInfo::shareText() const
{
    return m_shareText;
}

qint32 QxTdUserFullInfo::groupInCommonCount() const
{
    return m_groupInCommonCount;
}
