#include "qx_td_message_contact.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageContact::QxTdMessageContact(QObject *parent)
    : QxTdMessageContent(parent)
    , m_contact(new QxTdContact)
{
    setType(MESSAGE_CONTACT);
}

QxTdContact *QxTdMessageContact::contact() const
{
    return m_contact.data();
}

void QxTdMessageContact::unmarshalJson(const QJsonObject &json) {
    QxTdMessageContent::unmarshalJson(json);
    m_contact->unmarshalJson(json["contact"].toObject());
    m_typeText = qxTranslate("Contact");
}

