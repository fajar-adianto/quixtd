#include "qx_td_sticker_type.h"

#include <QDebug>

QxTdStickerType::QxTdStickerType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty
}

QxTdStickerTypeRegular::QxTdStickerTypeRegular(QObject *parent)
    : QxTdStickerType(parent)
{
    setType(STICKER_TYPE_REGULAR);
}

QxTdStickerTypeMask::QxTdStickerTypeMask(QObject *parent)
    : QxTdStickerType(parent)
{
    setType(STICKER_TYPE_MASK);
}


QxTdStickerTypeCustomEmoji::QxTdStickerTypeCustomEmoji(QObject *parent)
    : QxTdStickerType(parent)
{
    setType(STICKER_TYPE_CUSTOM_EMOJI);
}

QxTdStickerType *QxTdStickerTypeFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    QxTdStickerType *result;

    if (type == "stickerTypeRegular") {
        result = new QxTdStickerTypeRegular(parent);
    } else if (type == "stickerTypeMask") {
        result = new QxTdStickerTypeMask(parent);
    } else if (type == "stickerTypeCustomEmoji") {
        result = new QxTdStickerTypeCustomEmoji(parent);
    } else {
        qWarning() << "Received unknown sticker type" << type << json;
        return new QxTdStickerType(parent);
    }
    result->unmarshalJson(json);
    return result;
}
