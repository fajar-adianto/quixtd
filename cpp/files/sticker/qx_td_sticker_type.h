#ifndef QX_TD_STICKER_TYPE_H
#define QX_TD_STICKER_TYPE_H

#include <QPointer>
#include "common/qx_td_object.h"

class QxTdStickerType : public QxTdObject
{
    Q_OBJECT

public:
    explicit QxTdStickerType(QObject *parent = nullptr);

    // virtual void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdStickerType)
};

class QxTdStickerTypeRegular : public QxTdStickerType
{
    Q_OBJECT

public:
    explicit QxTdStickerTypeRegular(QObject *parent = nullptr);

};

class QxTdStickerTypeMask : public QxTdStickerType
{
    Q_OBJECT

public:
    explicit QxTdStickerTypeMask(QObject *parent = nullptr);

};

class QxTdStickerTypeCustomEmoji : public QxTdStickerType
{
    Q_OBJECT

public:
    explicit QxTdStickerTypeCustomEmoji(QObject *parent = nullptr);

};

struct QxTdStickerTypeFactory
{
    static QxTdStickerType *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_STICKER_TYPE_H
