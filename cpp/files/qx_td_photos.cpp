#include "qx_td_photos.h"
#include <QJsonArray>
#include <QDebug>

QxTdPhotos::QxTdPhotos(QObject *parent)
    : QxAbstractInt64Id(parent)
    , m_hasStickers(false)
    , m_sizes(nullptr)
{
    m_sizes = new QxTdObjectListModel<QxTdPhotoSize>(this, "", "type");
}

QxTdPhotos::~QxTdPhotos()
{
    m_sizes->clear();
}

void QxTdPhotos::unmarshalJson(const QJsonObject &json)
{
    QxAbstractInt64Id::unmarshalJson(json);
    m_hasStickers = json["has_stickers"].toBool();
    const QJsonArray sizes = json["sizes"].toArray();
    for (const QJsonValue &size : sizes) {
        auto *s = new QxTdPhotoSize();
        s->unmarshalJson(size.toObject());
        m_sizes->append(s);
    }
    emit photosChanged();
}

bool QxTdPhotos::hasStickers() const
{
    return m_hasStickers;
}

QObject *QxTdPhotos::qmlSizes() const
{
    return m_sizes;
}

QxTdObjectListModel<QxTdPhotoSize> *QxTdPhotos::sizes() const
{
    return m_sizes;
}
