#ifndef QX_TD_GET_SUPER_GROUP_REQUEST_H
#define QX_TD_GET_SUPER_GROUP_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetSuperGroupRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_supergroup.html
 */
class QxTdGetSuperGroupRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_sgId;

public:
    explicit QxTdGetSuperGroupRequest(QObject *parent = nullptr);
    void setSuperGroupId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_GET_SUPER_GROUP_REQUEST_H
