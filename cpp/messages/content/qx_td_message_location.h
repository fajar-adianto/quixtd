#ifndef QX_TD_MESSAGE_LOCATION_H
#define QX_TD_MESSAGE_LOCATION_H

#include "messages/qx_td_message_content.h"
#include "qx_td_location.h"

class QxTdMessageLocation : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdLocation *location READ location NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageLocation cannot be created in QML.")
public:
    explicit QxTdMessageLocation(QObject *parent = nullptr);

    QxTdLocation *location() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageLocation)
    std::unique_ptr<QxTdLocation> m_location;
};

#endif // QX_TD_MESSAGE_LOCATION_H
