#ifndef QX_TD_STICKER_H
#define QX_TD_STICKER_H

#include "qx_td_thumbnail.h"
#include "sticker/qx_td_sticker_format.h"
#include "sticker/qx_td_sticker_type.h"

class QxTdSticker : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString setId READ qmlSetId NOTIFY stickerChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY stickerChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY stickerChanged)
    Q_PROPERTY(QString emoji READ emoji NOTIFY stickerChanged)
    Q_PROPERTY(QxTdStickerType* stickerType READ qmlType NOTIFY stickerChanged)
    Q_PROPERTY(QxTdStickerFormat* stickerFormat READ qmlFormat NOTIFY stickerChanged)
    Q_PROPERTY(bool isMask READ isMask NOTIFY stickerChanged)
    // TODO: Q_PROPERTY(QxTdMaskPosition maskPosition READ maskPosition NOTIFY stickerChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY stickerChanged)
    Q_PROPERTY(QxTdFile *sticker READ sticker NOTIFY stickerChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdSticker cannot be created in QML.")
public:
    explicit QxTdSticker(QObject *parent = nullptr);

    QString qmlSetId() const;
    qint64 setId() const;

    qint32 width() const;

    qint32 height() const;

    QString emoji() const;

    QxTdStickerType *qmlType() const;
    QxTdStickerFormat *qmlFormat() const;

    bool isMask() const;

    QxTdFile *sticker() const;

    void unmarshalJson(const QJsonObject &json) override;

    QxTdThumbnail *thumbnail() const;

signals:
    void stickerChanged();

private:
    QxTdInt64 m_setId;
    qint32 m_width;
    qint32 m_height;
    QString m_emoji;
    QScopedPointer<QxTdStickerFormat> m_format;
    QScopedPointer<QxTdStickerType> m_type;
    bool m_isMask;
    QScopedPointer<QxTdThumbnail> m_thumbnail;
    QScopedPointer<QxTdFile> m_sticker;
};

#endif // QX_TD_STICKER_H
