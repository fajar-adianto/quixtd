#include "qx_td_local_file.h"

QxTdLocalFile::QxTdLocalFile(QObject *parent)
    : QxTdObject(parent)
    , m_canBeDownloaded(false)
    , m_canBeDeleted(false)
    , m_isDownloadingActive(false)
    , m_isDownloadingCompleted(false)
    , m_prefixSize(0)
    , m_size(0)
{
    setType(LOCAL_FILE);
}

QString QxTdLocalFile::path() const
{
    return m_path;
}

bool QxTdLocalFile::canBeDownloaded() const
{
    return m_canBeDownloaded;
}

bool QxTdLocalFile::canBeDeleted() const
{
    return m_canBeDeleted;
}

bool QxTdLocalFile::isDownloadingActive() const
{
    return m_isDownloadingActive;
}

bool QxTdLocalFile::isDownloadingCompleted() const
{
    return m_isDownloadingCompleted;
}

QString QxTdLocalFile::qmlDownloadedPrefixSize() const
{
    return m_prefixSize.toQmlValue();
}

qint32 QxTdLocalFile::downloadedPrefixSize() const
{
    return m_prefixSize.value();
}

QString QxTdLocalFile::qmlDownloadedSize() const
{
    return m_size.toQmlValue();
}

qint32 QxTdLocalFile::downloadedSize() const
{
    return m_size.value();
}

void QxTdLocalFile::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_path = json["path"].toString();
    emit pathChanged(m_path);
    m_canBeDownloaded = json["can_be_downloaded"].toBool();
    emit canBeDownloadedChanged(m_canBeDownloaded);
    m_canBeDeleted = json["can_be_deleted"].toBool();
    emit canBeDeletedChanged(m_canBeDeleted);
    m_isDownloadingActive = json["is_downloading_active"].toBool();
    emit isDownloadingActiveChanged(m_isDownloadingActive);
    m_isDownloadingCompleted = json["is_downloading_completed"].toBool();
    emit isDownloadingCompletedChanged(m_isDownloadingCompleted);
    m_prefixSize = json["downloaded_prefix_size"];
    emit downloadedPrefixSizeChanged();
    m_size = json["downloaded_size"];
    emit downloadedSizeChanged();
}
