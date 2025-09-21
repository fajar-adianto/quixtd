#ifndef QX_TD_IMPORT_CONTACTS_REQUEST_H
#define QX_TD_IMPORT_CONTACTS_REQUEST_H

#include "common/qx_td_request.h"
#include "user/qx_td_contact.h"

class QxTdContact; // Forward declaration.

/**
 * @brief The QxTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_contacts.html
 */
class QxTdImportContactsRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdImportContactsRequest(QObject *parent = nullptr);

    void setContacts(const QList<QxTdContact *> &contacts);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdImportContactsRequest)
    QJsonArray m_contacts;
};

#endif // QX_TD_IMPORT_CONTACTS_REQUEST_H
