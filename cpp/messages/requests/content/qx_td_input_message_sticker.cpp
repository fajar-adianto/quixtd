#include "qx_td_input_message_sticker.h"
#include "files/qx_td_sticker.h"

QxTdInputMessageSticker::QxTdInputMessageSticker(QObject *parent)
    : QxTdInputMessageContent(parent)
    , m_sticker(nullptr)
{
    // Intentionally left empty.
}

void QxTdInputMessageSticker::setSticker(QxTdSticker *sticker)
{
    m_sticker = sticker;
}

QJsonObject QxTdInputMessageSticker::marshalJson()
{
    if (!m_sticker) {
        qDebug() << "Tried to marshal QxTdInputMessageSticker with invalid sticker pointer";
        return QJsonObject();
    }
    return QJsonObject{
        { "@type", "inputMessageSticker" },
        { "sticker", QJsonObject{ { "@type", "inputFileRemote" }, { "id", m_sticker->sticker()->remote()->id() } } },
    };
}
