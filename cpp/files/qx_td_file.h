#ifndef QX_TD_FILE_H
#define QX_TD_FILE_H

#include "common/qx_abstract_int64_id.h"
#include "qx_td_local_file.h"
#include "qx_td_remote_file.h"

class QxTdFile : public QxAbstractInt64Id
{
    Q_OBJECT
    Q_PROPERTY(QString size READ qmlSize NOTIFY fileChanged)
    Q_PROPERTY(QString expectedSize READ qmlExpectedSize NOTIFY fileChanged)
    Q_PROPERTY(QxTdLocalFile *local READ local NOTIFY fileChanged)
    Q_PROPERTY(QxTdRemoteFile *remote READ remote NOTIFY fileChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdFile cannot be created in QML.")
public:
    explicit QxTdFile(QObject *parent = nullptr);

    qint32 size() const;
    QString qmlSize() const;

    qint32 expectedSize() const;
    QString qmlExpectedSize() const;

    QxTdLocalFile *local() const;

    QxTdRemoteFile *remote() const;

    void unmarshalJson(const QJsonObject &json) override;

    Q_INVOKABLE void downloadFile();

signals:
    void fileChanged();

private slots:
    void handleUpdateFile(const QJsonObject &json);

private:
    QxTdInt53 m_size;
    QxTdInt53 m_expectedSize;
    std::unique_ptr<QxTdLocalFile> m_local;
    std::unique_ptr<QxTdRemoteFile> m_remote;
};

#endif // QX_TD_FILE_H
