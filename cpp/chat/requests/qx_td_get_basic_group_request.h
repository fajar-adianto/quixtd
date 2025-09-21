#ifndef QX_TD_GET_BASIC_GROUP_REQUEST_H
#define QX_TD_GET_BASIC_GROUP_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdGetBasicGroupRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1get_basic_group.html
 */
class QxTdGetBasicGroupRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdGetBasicGroupRequest(QObject *parent = nullptr);

    void setGroupId(const qint64 groupId);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdGetBasicGroupRequest)
    qint64 m_groupId;
};

#endif // QX_TD_GET_BASIC_GROUP_REQUEST_H
