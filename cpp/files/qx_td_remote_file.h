#ifndef QX_TD_REMOTE_FILE_H
#define QX_TD_REMOTE_FILE_H

#include "common/qx_td_object.h"
#include "common/qx_td_int.h"

class QxTdRemoteFile : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id NOTIFY idChanged)
    Q_PROPERTY(bool isUploadingActive READ isUploadingActive NOTIFY isUploadingActiveChanged)
    Q_PROPERTY(bool isUploadingCompleted READ isUploadingCompleted NOTIFY isUploadingCompletedChanged)
    Q_PROPERTY(QString uploadedSize READ qmlUploadedSize NOTIFY uploadedSizeChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdRemoteFile cannot be created in QML.")
public:
    explicit QxTdRemoteFile(QObject *parent = nullptr);

    QString id() const;
    bool isUploadingActive() const;
    bool isUploadingCompleted() const;
    QString qmlUploadedSize() const;
    qint32 uploadedSize() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void idChanged(QString id);
    void isUploadingActiveChanged(bool isUploadingActive);
    void isUploadingCompletedChanged(bool isUploadingCompleted);
    void uploadedSizeChanged(QString uploadedSize);

private:
    QString m_id;
    bool m_isUploadingActive;
    bool m_isUploadingCompleted;
    QxTdInt32 m_uploadedSize;
};

#endif // QX_TD_REMOTE_FILE_H
