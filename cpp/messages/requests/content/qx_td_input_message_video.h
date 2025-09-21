#ifndef QX_TD_INPUT_MESSAGE_VIDEO_H
#define QX_TD_INPUT_MESSAGE_VIDEO_H

#include <QScopedPointer>

#include "../qx_td_input_message_content_attachment_caption.h"
#include "qx_td_input_thumbnail.h"

class QxTdInputMessageVideo : public QxTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QxTdInputMessageVideo(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QxTdInputMessageVideo)
    QString m_video;
    qint32 m_width, m_height;
    QString m_caption;
    QJsonArray m_captionEntities;
    QScopedPointer<QxTdMediaSizeExtractor> m_mediaSizeExtractor;
    QScopedPointer<QxTdInputThumbnail> m_inputThumbnail;
};

#endif // QX_TD_INPUT_MESSAGE_VIDEO_H
