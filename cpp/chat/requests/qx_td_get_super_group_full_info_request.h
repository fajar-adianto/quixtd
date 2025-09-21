#ifndef QX_TD_GET_SUPER_GROUP_FULL_INFO_REQUEST_H
#define QX_TD_GET_SUPER_GROUP_FULL_INFO_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetSuperGroupFullInfoRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_supergroup_full_info.html
 */
class QxTdGetSuperGroupFullInfoRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_id;

public:
    explicit QxTdGetSuperGroupFullInfoRequest(QObject *parent = nullptr);

    void setSupergroupId(const qint64 &id);
    QJsonObject marshalJson();
    QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_GET_SUPER_GROUP_FULL_INFO_REQUEST_H
