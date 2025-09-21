#ifndef QX_TD_DOWNLOAD_FILE_REQUEST_H
#define QX_TD_DOWNLOAD_FILE_REQUEST_H

#include "common/qx_td_request.h"

/**
 * @brief The QxTdDownloadFileRequest class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1download_file.html
 */
class QxTdDownloadFileRequest : public QxTdRequest
{
    Q_OBJECT
public:
    explicit QxTdDownloadFileRequest(QObject *parent = nullptr);

    enum Priority {
        Low = 1,
        Medium = 16,
        High = 32
    };
    Q_ENUM(Priority)

    void setPriority(const Priority &priority);
    void setFileId(const qint64 &fileId);

    QJsonObject marshalJson();

    QFuture<QxTdResponse> sendAsync();

private:
    Q_DISABLE_COPY(QxTdDownloadFileRequest)
    Priority m_priority;
    qint64 m_fileId;
};

#endif // QX_TD_DOWNLOAD_FILE_REQUEST_H
