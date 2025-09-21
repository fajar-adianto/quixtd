#include "qx_td_chat_action_bar.h"
#include "utils/qx_td_translate_tools.h"

QxTdChatActionBar::QxTdChatActionBar(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdChatActionBarAddContact::QxTdChatActionBarAddContact(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_ADDCONTACT);
}

QxTdChatActionBarInviteMembers::QxTdChatActionBarInviteMembers(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_INVITEMEMBERS);
}

QxTdChatActionBarJoinRequest::QxTdChatActionBarJoinRequest(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_JOINREQUEST);
}

void QxTdChatActionBarJoinRequest::unmarshalJson(const QJsonObject &json)
{
    QxTdChatActionBar::unmarshalJson(json);
    m_title = json["title"].toString();
    m_isChannel = json["is_channel"].toBool();
    m_requestDate = json["request_date"].toInt();
}

QString QxTdChatActionBarJoinRequest::title() {
    return m_title;
}

bool QxTdChatActionBarJoinRequest::isChannel() {
    return m_isChannel;
}

qint32 QxTdChatActionBarJoinRequest::requestDate() {
    return m_requestDate;
}

QxTdChatActionBarReportAddBlock::QxTdChatActionBarReportAddBlock(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTADDBLOCK);
}

void QxTdChatActionBarReportAddBlock::unmarshalJson(const QJsonObject &json)
{
    QxTdChatActionBar::unmarshalJson(json);
    m_canUnarchive = json["can_unarchive"].toBool();
    m_distance = json["distance"].toInt();
}

bool QxTdChatActionBarReportAddBlock::canUnarchive() {
    return m_canUnarchive;
}

qint32 QxTdChatActionBarReportAddBlock::distance() {
    return m_distance;
}

QxTdChatActionBarReportSpam::QxTdChatActionBarReportSpam(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTSPAM);
}

bool QxTdChatActionBarReportSpam::canUnarchive() {
    return m_canUnarchive;
}

void QxTdChatActionBarReportSpam::unmarshalJson(const QJsonObject &json)
{
    QxTdChatActionBar::unmarshalJson(json);
    m_canUnarchive = json["can_unarchive"].toBool();
}

QxTdChatActionBarReportUnrelatedLocation::QxTdChatActionBarReportUnrelatedLocation(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_REPORTUNRELATEDLOCATION);
}

QxTdChatActionBarSharePhoneNumber::QxTdChatActionBarSharePhoneNumber(QObject *parent)
    : QxTdChatActionBar(parent)
{
    setType(CHAT_ACTIONBAR_SHAREPHONENUMBER);
}

QxTdChatActionBar *QxTdChatActionBarFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QxTdChatActionBar *chatActionBar = nullptr;
    if (type == "chatActionBarAddContact") {
        chatActionBar = new QxTdChatActionBarAddContact(parent);
    } else if (type == "chatActionBarInviteMembers") {
        chatActionBar = new QxTdChatActionBarInviteMembers(parent);
    } else if (type == "chatActionBarJoinRequest") {
        chatActionBar = new QxTdChatActionBarJoinRequest(parent);
    } else if (type == "chatActionBarReportAddBlock") {
        chatActionBar = new QxTdChatActionBarReportAddBlock(parent);
    } else if (type == "chatActionBarReportSpam") {
        chatActionBar = new QxTdChatActionBarReportSpam(parent);
    } else if (type == "chatActionBarReportUnrelatedLocation") {
        chatActionBar = new QxTdChatActionBarReportUnrelatedLocation(parent);
    } else if (type == "chatActionBarSharePhoneNumber") {
        chatActionBar = new QxTdChatActionBarSharePhoneNumber(parent);
    }
    if (chatActionBar) {
        chatActionBar->unmarshalJson(json);
    }
    return chatActionBar;
}
