#include "qx_td_input_message_photo.h"

#include <tuple>

QxTdInputMessagePhoto::QxTdInputMessagePhoto(QObject *parent)
    : QxTdInputMessageContentAttachmentCaption(parent)
    , m_photo(QString())
    , m_width(0)
    , m_height(0)
    , m_caption(QString())
    , m_captionEntities(QJsonArray())
    , m_mediaSizeExtractor(new QxTdMediaSizeExtractor(this))
    , m_inputThumbnail(nullptr)
{
    // Intentionally left empty.
}

void QxTdInputMessagePhoto::setAttachmentPath(const QString &url)
{   
    m_photo = url;
    m_inputThumbnail.reset(new QxTdInputThumbnail(this));
    m_inputThumbnail->setOriginalFile(m_photo);
    auto mediaSize = m_mediaSizeExtractor->extractPictureSize(m_photo);
    m_width = std::get<0>(mediaSize);
    m_height = std::get<1>(mediaSize);
}

void QxTdInputMessagePhoto::setCaption(const QString &caption)
{
    m_caption = caption;
}

void QxTdInputMessagePhoto::setCaptionEntities(const QJsonArray &entities)
{
    m_captionEntities = entities;
}

QJsonObject QxTdInputMessagePhoto::marshalJson()
{
    
    return QJsonObject{
        { "@type", "inputMessagePhoto" },
        { "photo", QJsonObject{
                { "@type", "inputFileGenerated" },
                { "original_path", m_photo },
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
