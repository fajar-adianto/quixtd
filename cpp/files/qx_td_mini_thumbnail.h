#ifndef QX_TD_MINI_THUMBNAIL_H
#define QX_TD_MINI_THUMBNAIL_H

#include "common/qx_td_object.h"

class QxTdMiniThumbnail : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString data READ data NOTIFY miniThumbnailChanged)
    Q_PROPERTY(QString dataURL READ dataURL NOTIFY miniThumbnailChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY miniThumbnailChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY miniThumbnailChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMiniThumbnail cannot be created in QML.")
public:
    explicit QxTdMiniThumbnail(QObject *parent = nullptr);

    QString data() const;
    QString dataURL() const;
    qint32 width() const;
    qint32 height() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void miniThumbnailChanged();

private:
    Q_DISABLE_COPY(QxTdMiniThumbnail)
    QString m_data;
    qint32 m_width;
    qint32 m_height;
};

#endif // QX_TD_MINI_THUMBNAIL_H
