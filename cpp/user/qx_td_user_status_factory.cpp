#include "qx_td_user_status_factory.h"
#include "qx_td_user_status.h"

#include <QDebug>

QxTdUserStatus *QxTdUserStatusFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    //    qDebug() << "[USERSTATUSTYPE] " << type;
    QxTdUserStatus *obj = nullptr;
    if (type == "userStatusEmpty") {
        obj = new QxTdUserStatusEmpty(parent);
    } else if (type == "userStatusLastMonth") {
        obj = new QxTdUserStateLastMonth(parent);
    } else if (type == "userStatusLastWeek") {
        obj = new QxTdUserStatusLastWeek(parent);
    } else if (type == "userStatusOffline") {
        obj = new QxTdUserStatusOffline(parent);
    } else if (type == "userStatusOnline") {
        obj = new QxTdUserStatusOnline(parent);
    } else if (type == "userStatusRecently") {
        obj = new QxTdUserStatusRecently(parent);
    } else {
        qWarning() << "Unknown user status type: " << type;
    }

    if (obj) {
        obj->unmarshalJson(json);
    }
    return obj;
}
