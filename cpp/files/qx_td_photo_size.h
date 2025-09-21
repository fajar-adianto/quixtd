#ifndef QX_TD_PHOTO_SIZE_H
#define QX_TD_PHOTO_SIZE_H

#include "qx_td_file.h"

class QxTdPhotoSize : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString type READ type NOTIFY photoSizeChanged)
    Q_PROPERTY(QxTdFile *photo READ photo NOTIFY photoSizeChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY photoSizeChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY photoSizeChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdPhotoSize cannot be created in QML.")
public:
    explicit QxTdPhotoSize(QObject *parent = nullptr);

    QString type() const;

    QxTdFile *photo() const;

    qint32 width() const;

    qint32 height() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void photoSizeChanged();

private:
    QString m_type;
    QScopedPointer<QxTdFile> m_photo;
    qint32 m_width;
    qint32 m_height;
};

#endif // QX_TD_PHOTO_SIZE_H
