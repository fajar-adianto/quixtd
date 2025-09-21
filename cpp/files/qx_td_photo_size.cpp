#include "qx_td_photo_size.h"
#include <QDebug>

QxTdPhotoSize::QxTdPhotoSize(QObject *parent)
    : QxTdObject(parent)
    , m_photo(new QxTdFile)
    , m_width(0)
    , m_height(0)
{
    setType(PHOTO_SIZE);
}

QString QxTdPhotoSize::type() const
{
    return m_type;
}

QxTdFile *QxTdPhotoSize::photo() const
{
    return m_photo.data();
}

qint32 QxTdPhotoSize::width() const
{
    return m_width;
}

qint32 QxTdPhotoSize::height() const
{
    return m_height;
}

void QxTdPhotoSize::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_type = json["type"].toString();
    m_photo->unmarshalJson(json["photo"].toObject());
    if (m_photo->local()->path().isEmpty()) {
        m_photo->downloadFile();
    }
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    emit photoSizeChanged();
}
