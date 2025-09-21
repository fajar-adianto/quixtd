#ifndef QX_TD_PHOTOS_H
#define QX_TD_PHOTOS_H

#include <QPointer>
#include "models/qx_td_object_list_model.h"
#include "qx_td_photo_size.h"

class QxTdPhotos : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(bool hasSitckers READ hasStickers NOTIFY photosChanged)
    Q_PROPERTY(QObject *sizes READ qmlSizes NOTIFY photosChanged)
    QML_ELEMENT
public:
    explicit QxTdPhotos(QObject *parent = nullptr);
    ~QxTdPhotos();

    void unmarshalJson(const QJsonObject &json) override;

    bool hasStickers() const;

    QObject *qmlSizes() const;
    QxTdObjectListModel<QxTdPhotoSize> *sizes() const;

signals:
    void photosChanged();

private:
    bool m_hasStickers;
    QPointer<QxTdObjectListModel<QxTdPhotoSize>> m_sizes;
};

#endif // QX_TD_PHOTOS_H
