#ifndef QX_TD_INPUT_MESSAGE_PHOTO_H
#define QX_TD_INPUT_MESSAGE_PHOTO_H

#include <QScopedPointer>

#include "../qx_td_input_message_content_attachment_caption.h"
#include "qx_td_input_thumbnail.h"

class QxTdInputMessagePhoto : public QxTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QxTdInputMessagePhoto(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QxTdInputMessagePhoto)
    QString m_photo;
    qint32 m_width, m_height;
    QString m_caption;
    QJsonArray m_captionEntities;
    QScopedPointer<QxTdMediaSizeExtractor> m_mediaSizeExtractor;
    QScopedPointer<QxTdInputThumbnail> m_inputThumbnail;
};

#endif // QX_TD_INPUT_MESSAGE_PHOTO_H
