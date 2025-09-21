#include "qx_td_input_thumbnail.h"

#include <tuple>

QxTdInputThumbnail::QxTdInputThumbnail(QObject *parent)
    : QxTdObject(parent)
    , m_width(0)
    , m_height(0)
    , m_thumbnailExtractor(new QxTdThumbnailExtractor(this))
{
}

void QxTdInputThumbnail::setOriginalFile(QString originalFile)
{
    auto result = m_thumbnailExtractor->extractThumbnail(originalFile, 320);
    m_thumbnailFile = std::get<0>(result);
    m_width = std::get<1>(result);
    m_height = std::get<2>(result);
}

qint32 QxTdInputThumbnail::width()
{
    return m_width;
}

qint32 QxTdInputThumbnail::height()
{
    return m_height;
}

QJsonObject QxTdInputThumbnail::marshalJson()
{
    return QJsonObject {
        { "@type", "inputThumbnail" },
        { "thumbnail", QJsonObject {
                { "@type", "inputFileLocal" },
                { "path", m_thumbnailFile }
            }
        },
        { "width", m_width },
        { "height", m_height }
    };
}

