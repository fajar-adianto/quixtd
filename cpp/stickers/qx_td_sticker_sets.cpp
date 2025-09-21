#include "qx_td_sticker_sets.h"
#include "client/qx_td_client.h"
#include <QJsonObject>
#include <QJsonArray>

QxTdStickerSets::QxTdStickerSets(QObject *parent)
    : QxTdObject(parent)
{
    m_stickerSets = new QxTdObjectListModel<QxTdStickerSet>(this, "", "id");
    connect(QxTdClient::instance(), &QxTdClient::stickerSets, this, &QxTdStickerSets::handleStickerSets);
}

QObject *QxTdStickerSets::qmlModel() const
{
    return m_stickerSets;
}

void QxTdStickerSets::loadStickerSets()
{
    QxTdClient::instance()->send(QJsonObject{
            { "@type", "getInstalledStickerSets" },
            { "is_masks", false },
    });
}

void QxTdStickerSets::handleStickerSets(const QJsonObject &json)
{
    m_stickerSets->clear();
    auto array = json["sets"].toArray();
    for (auto value : array) {
        auto newSet = new QxTdStickerSet(this);
        newSet->unmarshalJson(value.toObject());
        m_stickerSets->append(newSet);
    }
}
