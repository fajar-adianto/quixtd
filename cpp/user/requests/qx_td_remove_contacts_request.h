#ifndef QX_TD_REMOVE_CONTACTS_REQUEST_H
#define QX_TD_REMOVE_CONTACTS_REQUEST_H

#include "common/qx_td_request.h"

class QxTdRemoveContactsRequest : public QxTdOkRequest
{
    Q_OBJECT
public:
    explicit QxTdRemoveContactsRequest(QObject *parent = nullptr);

    void setUserIds(const QList<qint64> &userIds);
    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QxTdRemoveContactsRequest)
    QList<qint64> m_userIds;
};

#endif // QX_TD_REMOVE_CONTACTS_REQUEST_H
