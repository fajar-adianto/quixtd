#include "utils/qx_td_translate_tools.h"
#include "qx_td_user_status.h"

QxTdUserStatus::QxTdUserStatus(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdUserStatusEmpty::QxTdUserStatusEmpty(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_EMPTY);
}

QString QxTdUserStatusEmpty::toString() const
{
    return "";
}

QxTdUserStateLastMonth::QxTdUserStateLastMonth(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_MONTH);
}

QString QxTdUserStateLastMonth::toString() const
{
    return qxTranslate("Last seen one month ago");
}

QxTdUserStatusLastWeek::QxTdUserStatusLastWeek(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_LAST_WEEK);
}

QString QxTdUserStatusLastWeek::toString() const
{
    return qxTranslate("Last seen one week ago");
}

QxTdUserStatusOffline::QxTdUserStatusOffline(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_OFFLINE);
}

QDateTime QxTdUserStatusOffline::wasOnline() const
{
    return m_wasOnline;
}

QString QxTdUserStatusOffline::toString() const
{
    return QString(qxTranslate("Last seen ")) + m_wasOnline.toString(qxTranslate("dd.MM.yy hh:mm"));
}

void QxTdUserStatusOffline::unmarshalJson(const QJsonObject &json)
{
    QxTdUserStatus::unmarshalJson(json);
    m_wasOnline.setSecsSinceEpoch(qint32(json["was_online"].toInt()));
    emit wasOnlineChanged(m_wasOnline);
}

QxTdUserStatusOnline::QxTdUserStatusOnline(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_ONLINE);
}

QDateTime QxTdUserStatusOnline::expires() const
{
    return m_expires;
}

QString QxTdUserStatusOnline::toString() const
{
    return qxTranslate("Online");
}

void QxTdUserStatusOnline::unmarshalJson(const QJsonObject &json)
{
    QxTdUserStatus::unmarshalJson(json);
    m_expires.setSecsSinceEpoch(qint32(json["expires"].toInt()));
    emit expiresChanged();
}

QxTdUserStatusRecently::QxTdUserStatusRecently(QObject *parent)
    : QxTdUserStatus(parent)
{
    setType(USER_STATUS_RECENTLY);
}

QString QxTdUserStatusRecently::toString() const
{
    return qxTranslate("Seen recently");
}
