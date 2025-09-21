#ifndef QX_TD_LOCATION_H
#define QX_TD_LOCATION_H

#include "common/qx_td_object.h"

class QxTdLocation : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(double latitude READ latitude NOTIFY entityChanged)
    Q_PROPERTY(double longitude READ longitude NOTIFY entityChanged)
    QML_ELEMENT
public:
    explicit QxTdLocation(QObject *parent = nullptr);

    double latitude() const;
    void setLatitude(const double value);

    double longitude() const;
    void setLongitude(const double value);

    void unmarshalJson(const QJsonObject &json) override;
    QJsonObject marshalJson() override;

signals:
    void entityChanged();

private:
    Q_DISABLE_COPY(QxTdLocation)
    double m_latitude;
    double m_longitude;
};

#endif // QX_TD_LOCATION_H
