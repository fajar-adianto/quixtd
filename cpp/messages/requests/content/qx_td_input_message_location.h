#ifndef QX_TD_INPUT_MESSAGE_LOCATION_H
#define QX_TD_INPUT_MESSAGE_LOCATION_H

#include <QPointer>
#include <QString>

#include "../qx_td_input_message_content.h"
#include "../../content/qx_td_location.h"

class QxTdInputMessageLocation : public QxTdInputMessageContent
{
    Q_OBJECT
public:
    explicit QxTdInputMessageLocation(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setLocation(const double latitude, const double longitude);
    void setLivePeriod(const qint32 live_period);

private:
    std::unique_ptr<QxTdLocation> m_location;
    qint32 m_live_period;
    Q_DISABLE_COPY(QxTdInputMessageLocation)
};

#endif // QX_TD_INPUT_MESSAGE_LOCATION_H
