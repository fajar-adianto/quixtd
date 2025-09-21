#include "qx_td_remote_file.h"

QxTdRemoteFile::QxTdRemoteFile(QObject *parent)
    : QxTdObject(parent)
    , m_isUploadingActive(false)
    , m_isUploadingCompleted(false)
    , m_uploadedSize(0)
{
    setType(REMOTE_FILE);
}

QString QxTdRemoteFile::id() const
{
    return m_id;
}

bool QxTdRemoteFile::isUploadingActive() const
{
    return m_isUploadingActive;
}

bool QxTdRemoteFile::isUploadingCompleted() const
{
    return m_isUploadingCompleted;
}

QString QxTdRemoteFile::qmlUploadedSize() const
{
    return m_uploadedSize.toQmlValue();
}

qint32 QxTdRemoteFile::uploadedSize() const
{
    return m_uploadedSize.value();
}

void QxTdRemoteFile::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_id = json["id"].toString();
    emit idChanged(m_id);
    m_isUploadingActive = json["is_uploading_active"].toBool();
    emit isUploadingActiveChanged(m_isUploadingActive);
    m_isUploadingCompleted = json["is_uploading_completed"].toBool();
    emit isUploadingCompletedChanged(m_isUploadingCompleted);
    m_uploadedSize = json["uploaded_size"];
    emit uploadedSizeChanged(m_uploadedSize.toQmlValue());
}
