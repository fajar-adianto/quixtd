#include "qx_td_block_user_request.h"
#include "user/qx_td_user.h"

QxTdBlockUserRequest::QxTdBlockUserRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdBlockUserRequest::setUser(QxTdUser *user)
{
    m_userId = user->id();
}

void QxTdBlockUserRequest::setUserId(const qint64 &id)
{
    m_userId = id;
}

void QxTdBlockUserRequest::setUserId(const QString &id)
{
    m_userId = id.toLongLong();
}

QJsonObject QxTdBlockUserRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "blockUser" },
        { "user_id", m_userId },
    };
}
