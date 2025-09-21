#ifndef QX_TD_LOCAL_FILE_H
#define QX_TD_LOCAL_FILE_H

#include "common/qx_td_object.h"
#include "common/qx_td_int.h"

class QxTdLocalFile : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString path READ path NOTIFY pathChanged)
    Q_PROPERTY(bool canBeDownloaded READ canBeDownloaded NOTIFY canBeDownloadedChanged)
    Q_PROPERTY(bool canBeDeleted READ canBeDeleted NOTIFY canBeDeletedChanged)
    Q_PROPERTY(bool isDownloadingActive READ isDownloadingActive NOTIFY isDownloadingActiveChanged)
    Q_PROPERTY(bool isDownloadingCompleted READ isDownloadingCompleted NOTIFY isDownloadingCompletedChanged)
    Q_PROPERTY(QString downloadedPrefixSize READ qmlDownloadedPrefixSize NOTIFY downloadedPrefixSizeChanged)
    Q_PROPERTY(QString downloadedSize READ qmlDownloadedSize NOTIFY downloadedSizeChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdLocalFile cannot be created in QML.")public:
    explicit QxTdLocalFile(QObject *parent = nullptr);

    QString path() const;
    bool canBeDownloaded() const;
    bool canBeDeleted() const;
    bool isDownloadingActive() const;
    bool isDownloadingCompleted() const;

    QString qmlDownloadedPrefixSize() const;
    qint32 downloadedPrefixSize() const;

    QString qmlDownloadedSize() const;
    qint32 downloadedSize() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void pathChanged(QString path);
    void canBeDownloadedChanged(bool canBeDownloaded);
    void canBeDeletedChanged(bool canBeDeleted);
    void isDownloadingActiveChanged(bool isDownloadingActive);
    void isDownloadingCompletedChanged(bool isDownloadingCompleted);
    void downloadedPrefixSizeChanged();
    void downloadedSizeChanged();

private:
    QString m_path;
    bool m_canBeDownloaded;
    bool m_canBeDeleted;
    bool m_isDownloadingActive;
    bool m_isDownloadingCompleted;
    QxTdInt32 m_prefixSize;
    QxTdInt32 m_size;
};

#endif // QX_TD_LOCAL_FILE_H
