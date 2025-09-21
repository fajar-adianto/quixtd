#include "qx_td_import_contacts_request.h"
#include "client/qx_td_client.h"

QxTdImportContactsRequest::QxTdImportContactsRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_contacts(QJsonArray())
{
    // Intentionally left empty
}

void QxTdImportContactsRequest::setContacts(const QList<QxTdContact *> &contacts)
{
    foreach (auto contact, contacts) {
        m_contacts.append(contact->marshalJson());
    }
}

QJsonObject QxTdImportContactsRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "importContacts" },
        { "contacts", m_contacts }
    };
}

QFuture<QxTdResponse> QxTdImportContactsRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::importedContacts);
}
