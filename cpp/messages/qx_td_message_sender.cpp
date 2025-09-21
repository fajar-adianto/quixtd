#include "qx_td_message_sender.h"

#include "common/qx_td_helpers.h"

#include "qx_td_message_sender_user.h"
#include "qx_td_message_sender_chat.h"

QxTdMessageSender::QxTdMessageSender(QObject *parent)
    : QxAbstractInt64Id(parent)
{
    // Intentionally left empty.
}

QString QxTdMessageSender::avatarColor() const
{
    return QxTdHelpers::avatarColor(id());
}

QxTdMessageSenderUnimplemented::QxTdMessageSenderUnimplemented(QObject *parent)
    : QxTdMessageSender(parent)
{
    // Intentionally left empty.
}

QString QxTdMessageSenderUnimplemented::displayName() const
{
    return QString("unimplemented");
}

QString QxTdMessageSenderUnimplemented::fullName() const
{
    return QString("unimplemented");
}

QxTdPhoto *QxTdMessageSenderUnimplemented::photo() const
{
    return nullptr;
}

QString QxTdMessageSenderUnimplemented::initials() const
{
    return "";
}

QJsonObject QxTdMessageSenderUnimplemented::marshalJson() const
{
    return QJsonObject();
}

QxTdMessageSender *QxTdMessageSenderFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QxTdMessageSender *result = nullptr;

    if (type == "messageSenderUser") {
        result = new QxTdMessageSenderUser(parent);
    } else if (type == "messageSenderChat") {
        result = new QxTdMessageSenderChat(parent);
    } else {
        result = new QxTdMessageSenderUnimplemented(parent);
    }
    result->unmarshalJson(json);
    return result; 
}
