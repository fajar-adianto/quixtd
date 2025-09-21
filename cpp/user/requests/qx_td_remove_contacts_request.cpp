#include "qx_td_remove_contacts_request.h"

QxTdRemoveContactsRequest::QxTdRemoveContactsRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty
}

void QxTdRemoveContactsRequest::setUserIds(const QList<qint64> &userIds)
{
    m_userIds = userIds;
}

QJsonObject QxTdRemoveContactsRequest::marshalJson()
{
    QJsonArray json_userids;
    for (auto &m_userId : m_userIds)
        json_userids.append(m_userId);
    return QJsonObject{
        { "@type", "removeContacts" },
        { "user_ids", json_userids }
    };
}
