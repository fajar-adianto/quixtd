#include "qx_td_file.h"

#include "client/qx_td_client.h"
#include "files/qx_td_download_file_request.h"

QxTdFile::QxTdFile(QObject *parent)
    : QxAbstractInt64Id(parent)
    , m_size(0)
    , m_expectedSize(0)
    , m_local(new QxTdLocalFile)
    , m_remote(new QxTdRemoteFile)
{
    setType(FILE);
    connect(QxTdClient::instance(), &QxTdClient::updateFile, this, &QxTdFile::handleUpdateFile);
}

qint32 QxTdFile::size() const
{
    return m_size.value();
}

QString QxTdFile::qmlSize() const
{
    return m_size.toQmlValue();
}

qint32 QxTdFile::expectedSize() const
{
    return m_expectedSize.value();
}

QString QxTdFile::qmlExpectedSize() const
{
    return m_expectedSize.toQmlValue();
}

QxTdLocalFile *QxTdFile::local() const
{
    return m_local.get();
}

QxTdRemoteFile *QxTdFile::remote() const
{
    return m_remote.get();
}

void QxTdFile::unmarshalJson(const QJsonObject &json)
{
    QxAbstractInt64Id::unmarshalJson(json);
    m_local->unmarshalJson(json["local"].toObject());
    m_remote->unmarshalJson(json["remote"].toObject());
    m_size = json["size"];
    m_expectedSize = json["expected_size"];
    emit fileChanged();
}

void QxTdFile::downloadFile()
{
    if (!m_local->canBeDownloaded()) {
        return;
    }
    std::unique_ptr<QxTdDownloadFileRequest> req(new QxTdDownloadFileRequest);
    req->setFileId(this->id());
    req->setPriority(QxTdDownloadFileRequest::Priority::Medium);
    QxTdClient::instance()->send(req.get());
}

void QxTdFile::handleUpdateFile(const QJsonObject &json)
{
    if (json["id"].toVariant().toLongLong() != this->id()) {
        return;
    }
    this->unmarshalJson(json);
}
