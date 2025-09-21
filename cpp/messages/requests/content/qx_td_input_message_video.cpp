#include "qx_td_input_message_video.h"

#include <tuple>

QxTdInputMessageVideo::QxTdInputMessageVideo(QObject *parent)
    : QxTdInputMessageContentAttachmentCaption(parent)
    , m_video(QString())
    , m_width(0)
    , m_height(0)
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
    , m_mediaSizeExtractor(new QxTdMediaSizeExtractor(this))
    , m_inputThumbnail(nullptr)
{
}
void QxTdInputMessageVideo::setAttachmentPath(const QString &url)
{
    m_video = url;
    m_inputThumbnail.reset(new QxTdInputThumbnail(this));
    m_inputThumbnail->setOriginalFile(m_video);
    m_width = m_inputThumbnail->width();
    m_height = m_inputThumbnail->height();
    //Disabled for now, the hack in the 2 lines before works as well
    //Still leaving this code here for a while as TODO
    //auto mediaSize = m_mediaSizeExtractor->extractVideoSize(m_video);
    //m_width = std::get<0>(mediaSize);
    //m_height = std::get<1>(mediaSize);
}

void QxTdInputMessageVideo::setCaption(const QString &caption)
{
    m_caption = caption;
}

void QxTdInputMessageVideo::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}

QJsonObject QxTdInputMessageVideo::marshalJson()
{

    return QJsonObject{
        { "@type", "inputMessageVideo" },
        { "video", QJsonObject
            {
                { "@type", "inputFileGenerated" },
                { "original_path", m_video },
                { "conversion", "attachment" } 
            }
        },
        { "width", m_width},
        { "height", m_height},
        { "thumbnail", m_inputThumbnail->marshalJson()},
        { "caption", QJsonObject{
                { "@type", "formattedText" },
                { "text", m_caption },
                { "entities", m_captionEntities }
            }
        }
    };
}
