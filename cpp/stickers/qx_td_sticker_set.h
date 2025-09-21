#ifndef QX_TD_STICKER_SET_H
#define QX_TD_STICKER_SET_H

#include <QObject>
#include <QScopedPointer>
#include "models/qx_td_object_list_model.h"
#include "common/qx_td_object.h"
#include "files/qx_td_thumbnail.h"
#include "files/qx_td_sticker.h"

class QxTdStickerSet : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY stickerSetChanged)
    Q_PROPERTY(QString title READ title NOTIFY stickerSetChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY stickerSetChanged)
    Q_PROPERTY(bool hasThumbnail READ hasThumbnail NOTIFY stickerSetChanged)
    Q_PROPERTY(bool isAnimated READ isAnimated NOTIFY stickerSetChanged)
    Q_PROPERTY(QObject *stickers READ qmlModel NOTIFY stickerSetChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdStickerSet cannot be created in QML.")
public:
    explicit QxTdStickerSet(QObject *parent = nullptr);

    QString title() const;
    QString name() const;
    QxTdThumbnail *thumbnail() const;
    bool hasThumbnail() const;
    bool isAnimated() const;

    QObject *qmlModel() const;

    Q_INVOKABLE void loadDetails() const;

    void handleDetails(const QJsonObject &json);

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void stickerSetChanged();

private:
    QScopedPointer<QxTdObjectListModel<QxTdSticker>> m_stickers;
    QxTdInt64 m_id;
    QString m_title;
    QString m_name;
    QScopedPointer<QxTdThumbnail> m_thumbnail;
    QScopedPointer<QxTdStickerFormat> m_format;
    QScopedPointer<QxTdStickerType> m_type;
    bool m_hasThumbnail;
    bool m_isAnimated;
    bool m_detailsLoaded;
    bool m_isInstalled;
    bool m_isArchived;
    bool m_isOfficial;
};

#endif // QX_TD_STICKER_SET_H
