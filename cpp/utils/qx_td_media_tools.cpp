#include "qx_td_media_tools.h"
//#include <lomiri/thumbnailer/qt/lomiri-thumbnailer-qt.h>
#include <QTemporaryFile>
#include <QDebug>
#include <QStandardPaths>
#include <QMediaMetaData>
#include <QtConcurrent>
#include <QImageReader>
#include <QEventLoop>
#include <QFile>

QxTdThumbnailExtractor::QxTdThumbnailExtractor(QObject *parent)
    : QObject(parent)
{
    // Intentionally left empty.
}

/*
// THIS IS THE LOMIRI IMPLEMENTATIOIN OF <QxTdThumbnailExtractor::extractThumbnail>

std::tuple<QString, qint32, qint32> QxTdThumbnailExtractor::extractThumbnail(QString originalFile, qint32 maxSize)
{

    m_originalFile = originalFile;
    lomiri::thumbnailer::qt::Thumbnailer thumbnailer;

    auto thumbnailRequest = thumbnailer.getThumbnail(m_originalFile, QSize(maxSize, maxSize));
    thumbnailRequest->waitForFinished();
    QTemporaryFile thumbnailFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation).append("/thumbnail-XXXXXX.jpg"));
    int thumbnailWidth = 0, thumbnailHeight = 0;
    if (thumbnailRequest->isValid() && thumbnailFile.open()) {
        thumbnailWidth = thumbnailRequest->image().width();
        thumbnailHeight = thumbnailRequest->image().height();
        thumbnailRequest->image().save(&thumbnailFile, "JPG");
        thumbnailFile.close();
        thumbnailFile.setAutoRemove(false);
    }
    return std::make_tuple(thumbnailFile.fileName(), thumbnailWidth, thumbnailHeight);
}
*/

std::tuple<QString, qint32, qint32> QxTdThumbnailExtractor::extractThumbnail(QString originalFile, qint32 maxSize)
{
    QTemporaryFile thumbnailFile(QStandardPaths::writableLocation(QStandardPaths::TempLocation).append("/thumbnail-XXXXXX.jpg"));
    int thumbnailWidth = 0, thumbnailHeight = 0;

    if (!thumbnailFile.open()) {
        return std::make_tuple(QString(), 0, 0);
    }

    // Try as image first
    QImageReader reader(originalFile);
    reader.setAutoTransform(true);
    QImage img = reader.read();

    if (!img.isNull()) {
        QImage thumb = img.scaled(maxSize, maxSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        thumb.save(&thumbnailFile, "JPG");
        thumbnailWidth = thumb.width();
        thumbnailHeight = thumb.height();
        thumbnailFile.close();
        thumbnailFile.setAutoRemove(false);
        return std::make_tuple(thumbnailFile.fileName(), thumbnailWidth, thumbnailHeight);
    }

    // TODO: If it’s a video, use QMediaPlayer + QVideoSink approach here

    return std::make_tuple(QString(), 0, 0);
}

QxTdMediaSizeExtractor::QxTdMediaSizeExtractor(QObject *parent)
    : QObject(parent)
    , fakeMediaPlayer(new QMediaPlayer())
{
    connect(fakeMediaPlayer, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &QxTdMediaSizeExtractor::onMediaMetadataChanged);
}

std::tuple<qint32, qint32> QxTdMediaSizeExtractor::extractPictureSize(QString picturePath)
{
    QImageReader reader(picturePath);
    reader.setAutoTransform(true);
    QSize sizeOfImage = reader.size();
    int height = sizeOfImage.height();
    int width = sizeOfImage.width();
    return std::make_tuple(width, height);
}

bool QxTdMediaSizeExtractor::canBeSendCompressed(QString picturePath) {
    QImageReader reader(picturePath);
    reader.setAutoTransform(true);
    QSize sizeOfImage = reader.size();
    int height = sizeOfImage.height();
    int width = sizeOfImage.width();
    QFile file(picturePath);
    qDebug() << "path: " << picturePath << ", height: " << height << ", width: " << width << ", size: " << file.size();
    return height + width <= 10000 && width / height <= 20.0 && file.size() <= 10485760;
}

// TODO see include file
// std::tuple<qint32, qint32> QxTdThumbnailExtractor::extractVideoSize(QString videoPath)
// {
//     qint32 width, height;

//     fakeMediaPlayer = new QMediaPlayer();
//     fakeMediaPlayer->setMedia(QUrl::fromLocalFile(videoPath));
//     m_stopMediaPlayer = false;
//     QEventLoop tempLoop;
//     fakeMediaPlayer->play();
//     qWarning() << "Player playing";
//     while (!m_stopMediaPlayer)
//     {
//         tempLoop.processEvents();
//     }
//     fakeMediaPlayer->stop();
//     qWarning() << "Player stopped";
//     QSize videoSize = fakeMediaPlayer->metaData(QMediaMetaData::Resolution).toSize();
//     width = videoSize.width();
//     height = videoSize.height();
//     qWarning() << "Videosize result:" << width << height;
//     disconnect(fakeMediaPlayer, QOverload<>::of(&QMediaPlayer::metaDataChanged), this, &QxTdThumbnailExtractor::onMediaMetadataChanged);
//     return std::make_tuple(width, height);
// }

void QxTdMediaSizeExtractor::onMediaMetadataChanged()
{
    m_stopMediaPlayer = true;
}

