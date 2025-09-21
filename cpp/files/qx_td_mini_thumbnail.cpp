#include "qx_td_mini_thumbnail.h"

QxTdMiniThumbnail::QxTdMiniThumbnail(QObject *parent)
    : QxTdObject(parent)
    , m_data("")
    , m_width(0)
    , m_height(0)
{
    setType(MINITHUMBNAIL);
}

QString QxTdMiniThumbnail::data() const
{
    return m_data;
}

QString QxTdMiniThumbnail::dataURL() const
{
    return QString("data:image/jpeg;base64,%1").arg(m_data);
}

qint32 QxTdMiniThumbnail::width() const
{
    return m_width;
}

qint32 QxTdMiniThumbnail::height() const
{
    return m_height;
}

void QxTdMiniThumbnail::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_data = json["data"].toString();
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    emit miniThumbnailChanged();
}
