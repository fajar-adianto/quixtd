#ifndef QX_TD_INPUT_MESSAGE_CONTENT_H
#define QX_TD_INPUT_MESSAGE_CONTENT_H

#include "common/qx_td_object.h"

class QxTdInputMessageContent : public QxTdObject
{
    Q_OBJECT
    // Q_DISABLE_COPY(QxTdInputMessageContent)
public:
    explicit QxTdInputMessageContent(QObject *parent = nullptr);
    virtual QJsonObject marshalJson() = 0;
};
#endif // QX_TD_INPUT_MESSAGE_CONTENT_H
