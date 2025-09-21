#include "qx_td_sticker_format.h"

#include <QDebug>

QxTdStickerFormat::QxTdStickerFormat(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdStickerFormatWebp::QxTdStickerFormatWebp(QObject *parent)
    : QxTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_WEBP);
}

QxTdStickerFormatTgs::QxTdStickerFormatTgs(QObject *parent)
    : QxTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_TGS);
}


QxTdStickerFormatWebm::QxTdStickerFormatWebm(QObject *parent)
    : QxTdStickerFormat(parent)
{
    setType(STICKER_FORMAT_WEBM);
}

QxTdStickerFormat *QxTdStickerFormatFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();

    QxTdStickerFormat *result;

    if (type == "stickerFormatWebp") {
        result = new QxTdStickerFormatWebp(parent);
    } else if (type == "stickerFormatTgs") {
        result = new QxTdStickerFormatTgs(parent);
    } else if (type == "stickerFormatWebm") {
        result = new QxTdStickerFormatWebm(parent);
    } else {
        qWarning() << "Received unknown sticker type" << type << json;
        return new QxTdStickerFormat(parent);
    }
    result->unmarshalJson(json);
    return result;
}
