#include "qx_td_input_message_contact.h"

QxTdInputMessageContact::QxTdInputMessageContact(QObject *parent)
    : QxTdInputMessageContent(parent)
    , m_contact(new QxTdContact(this))
{
    // Intentionally left empty.
}

QxTdContact *QxTdInputMessageContact::contact() {
    return m_contact.get();
}

QJsonObject QxTdInputMessageContact::marshalJson()
{
    return QJsonObject{
        { "@type", "inputMessageContact" },
        { "contact", m_contact->marshalJson() }
    };
}
