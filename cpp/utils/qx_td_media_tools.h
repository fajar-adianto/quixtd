#ifndef QX_TD_MEDIA_TOOLS_H
#define QX_TD_MEDIA_TOOLS_H

#include <tuple>

#include <QObject>
#include <QJsonArray>
#include <QString>
#include <QDebug>
#include <QMediaPlayer>
#include <QPointer>

#include <QtQmlIntegration/qqmlintegration.h>

class QxTdThumbnailExtractor : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdThumbnailExtractor)

public:
    explicit QxTdThumbnailExtractor(QObject *parent = nullptr);
    std::tuple<QString, qint32, qint32> extractThumbnail(QString originalFile, qint32 maxSize);

private:
    QString m_originalFile;
};

class QxTdMediaSizeExtractor : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_DISABLE_COPY(QxTdMediaSizeExtractor)

public:
    explicit QxTdMediaSizeExtractor(QObject *parent = nullptr);
    //TODO: This is to be implemented in a smarter way
    //std::tuple<qint32, qint32> extractVideoSize(QString videoPath);
    std::tuple<qint32, qint32> extractPictureSize(QString picturePath);
    Q_INVOKABLE bool canBeSendCompressed(QString picturePath);

private slots:
    void onMediaMetadataChanged();

private:
    bool m_stopMediaPlayer;
    QPointer<QMediaPlayer> fakeMediaPlayer;
};

#endif // QX_TD_MEDIA_TOOLS_H
