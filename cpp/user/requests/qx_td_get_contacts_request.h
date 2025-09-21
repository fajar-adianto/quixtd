#ifndef QX_TD_GET_CONTACTS_REQUEST_H
#define QX_TD_GET_CONTACTS_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetUserRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_contacts.html
 */
class QxTdGetContactsRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetContactsRequest(QObject *parent = nullptr);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

};

#endif // QX_TD_GET_CONTACTS_REQUEST_H
