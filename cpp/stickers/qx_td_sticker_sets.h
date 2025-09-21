#ifndef QX_TD_STICKER_SETS_H
#define QX_TD_STICKER_SETS_H

#include <QObject>
#include <QPointer>
#include "common/qx_td_object.h"
#include "models/qx_td_object_list_model.h"
#include "qx_td_sticker_set.h"

class QxTdStickerSets : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QObject *stickerSets READ qmlModel)
    QML_ELEMENT
public:
    explicit QxTdStickerSets(QObject *parent = nullptr);

    QObject *qmlModel() const;

    Q_INVOKABLE void loadStickerSets();

    void handleStickerSets(const QJsonObject &json);

signals:

private:
    QPointer<QxTdObjectListModel<QxTdStickerSet>> m_stickerSets;
};

#endif // QX_TD_STICKER_SETS_H
