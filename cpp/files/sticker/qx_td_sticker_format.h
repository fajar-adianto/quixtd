#ifndef QX_TD_STICKER_FORMAT_H
#define QX_TD_STICKER_FORMAT_H

#include <QPointer>
#include "common/qx_td_object.h"

class QxTdStickerFormat : public QxTdObject
{
    Q_OBJECT

public:
    explicit QxTdStickerFormat(QObject *parent = nullptr);

    //virtual void unmarshalJson(const QJsonObject &json);

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdStickerFormat)
};

class QxTdStickerFormatWebp : public QxTdStickerFormat
{
    Q_OBJECT

public:
    explicit QxTdStickerFormatWebp(QObject *parent = nullptr);

};

class QxTdStickerFormatTgs : public QxTdStickerFormat
{
    Q_OBJECT

public:
    explicit QxTdStickerFormatTgs(QObject *parent = nullptr);

};

class QxTdStickerFormatWebm : public QxTdStickerFormat
{
    Q_OBJECT

public:
    explicit QxTdStickerFormatWebm(QObject *parent = nullptr);

};

struct QxTdStickerFormatFactory
{
    static QxTdStickerFormat *create(const QJsonObject &json, QObject *parent = nullptr);
};

#endif // QX_TD_STICKER_FORMAT_H
