#include "qx_td_download_file_request.h"
#include "client/qx_td_client.h"

QxTdDownloadFileRequest::QxTdDownloadFileRequest(QObject *parent)
    : QxTdRequest(parent)
    , m_priority(Low)
    , m_fileId(0)
{
    // Intentionally left empty.
}

void QxTdDownloadFileRequest::setPriority(const QxTdDownloadFileRequest::Priority &priority)
{
    m_priority = priority;
}

void QxTdDownloadFileRequest::setFileId(const qint64 &fileId)
{
    m_fileId = fileId;
}

QJsonObject QxTdDownloadFileRequest::marshalJson()
{
    return QJsonObject{
        { "@type", "downloadFile" },
        { "file_id", m_fileId },
        { "priority", (qint32)m_priority },
    };
}

QFuture<QxTdResponse> QxTdDownloadFileRequest::sendAsync()
{
    return QxTdClient::instance()->sendAsync(this, &QxTdClient::file);
}
