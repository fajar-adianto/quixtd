#include "qx_td_message_link.h"

QxTdMessageLink::QxTdMessageLink(QObject *parent)
    : QxTdObject(parent)
{
    setType(MESSAGE_LINK);
}

QString QxTdMessageLink::link() const {
    return m_link;
}

bool QxTdMessageLink::isPublic() const {
    return m_is_public;
}


void QxTdMessageLink::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_link = json["link"].toString();
    m_is_public = json["is_public"].toBool();
    emit messageLinkChanged();
}
