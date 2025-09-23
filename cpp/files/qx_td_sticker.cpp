#include "qx_td_sticker.h"

QxTdSticker::QxTdSticker(QObject *parent)
    : QxTdObject(parent)
    , m_setId(0)
    , m_width(0)
    , m_height(0)
    , m_isMask(false)
    , m_format(new QxTdStickerFormat)
    , m_type(new QxTdStickerType)
    , m_thumbnail(new QxTdThumbnail)
    , m_sticker(new QxTdFile)
{
    setType(STICKER);
}

QString QxTdSticker::qmlSetId() const
{
    return m_setId.toQmlValue();
}

qint64 QxTdSticker::setId() const
{
    return m_setId.value();
}

qint32 QxTdSticker::width() const
{
    return m_width;
}

qint32 QxTdSticker::height() const
{
    return m_height;
}

QString QxTdSticker::emoji() const
{
    return m_emoji;
}

QxTdFile *QxTdSticker::sticker() const
{
    return m_sticker.get();
}

void QxTdSticker::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_setId = json["set_id"];
    m_width = qint32(json["width"].toInt());
    m_height = qint32(json["height"].toInt());
    m_emoji = json["emoji"].toString();
    m_format.reset(QxTdStickerFormatFactory::create(json["format"].toObject(), this));
    m_type.reset(QxTdStickerTypeFactory::create(json["type"].toObject(), this));
    m_isMask = json["is_mask"].toBool();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_sticker->unmarshalJson(json["sticker"].toObject());
    emit stickerChanged();
}

QxTdThumbnail *QxTdSticker::thumbnail() const
{
    return m_thumbnail.get();
}

bool QxTdSticker::isMask() const
{
    return m_isMask;
}

QxTdStickerType *QxTdSticker::qmlType() const
{
    return m_type.get();
}

QxTdStickerFormat *QxTdSticker::qmlFormat() const
{
    return m_format.get();
}
