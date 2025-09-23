#ifndef QX_TD_INPUT_THUMBNAIL_H
#define QX_TD_INPUT_THUMBNAIL_H

#include <QString>

#include "common/qx_td_object.h"
#include "utils/qx_td_media_tools.h"

/**
 * @brief The QxTdInputThumbnail class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1input_thumbnail.html
 */
class QxTdInputThumbnail : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdInputThumbnail)

public:
    explicit QxTdInputThumbnail(QObject *parent = nullptr);

    void setOriginalFile(QString filePath);
    qint32 width();
    qint32 height();
    QJsonObject marshalJson();

private:
    QString m_originalFile, m_thumbnailFile;
    qint32 m_width, m_height;
    std::unique_ptr<QxTdThumbnailExtractor> m_thumbnailExtractor;
};

#endif // QX_TD_INPUT_THUMBNAIL_H
