#ifndef QX_TD_CLOSE_REQUEST_H
#define QX_TD_CLOSE_REQUEST_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdCloseRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1close.html
 */
class QxTdCloseRequest : public QxTdOkRequest
{
    Q_OBJECT

public:
    explicit QxTdCloseRequest(QObject *parent = nullptr);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

};

#endif // QX_TD_CLOSE_REQUEST_H
