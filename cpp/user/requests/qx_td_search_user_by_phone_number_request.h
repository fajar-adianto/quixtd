#ifndef QX_TD_SEARCH_USER_BY_PHONE_NUMBER_REQUEST_H
#define QX_TD_SEARCH_USER_BY_PHONE_NUMBER_REQUEST_H

#include "common/qx_td_request.h"

class QxTdSearchUserByPhoneNumberRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdSearchUserByPhoneNumberRequest(QObject *parent = nullptr);

    void setPhoneNumber(const QString &value);

    QJsonObject marshalJson() Q_DECL_FINAL;
    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdSearchUserByPhoneNumberRequest)
    QString m_phoneNumber;
};

#endif // QX_TD_SEARCH_USER_BY_PHONE_NUMBER_REQUEST_H
