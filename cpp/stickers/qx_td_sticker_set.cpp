#include "qx_td_sticker_set.h"
#include "client/qx_td_client.h"

QxTdStickerSet::QxTdStickerSet(QObject *parent)
    : QxTdObject(parent)
    , m_id(0)
    , m_title("")
    , m_name("")
    , m_thumbnail(new QxTdThumbnail())
    , m_format(new QxTdStickerFormat())
    , m_type(new QxTdStickerType())
    , m_hasThumbnail(false)
    , m_isAnimated(false)
    , m_detailsLoaded(false)
    , m_isInstalled(false)
    , m_isArchived(false)
    , m_isOfficial(false)
{
    m_stickers.reset(new QxTdObjectListModel<QxTdSticker>(this, "", "id"));
    connect(QxTdClient::instance(), &QxTdClient::stickerSet, this, &QxTdStickerSet::handleDetails);
}

QString QxTdStickerSet::title() const
{
    return m_title;
}

QString QxTdStickerSet::name() const
{
    return m_name;
}

QxTdThumbnail *QxTdStickerSet::thumbnail() const
{
    return m_thumbnail.get();
}

bool QxTdStickerSet::hasThumbnail() const
{
    return m_hasThumbnail;
}

bool QxTdStickerSet::isAnimated() const
{
    return m_isAnimated;
}

QObject *QxTdStickerSet::qmlModel() const
{
    return m_stickers.get();
}

void QxTdStickerSet::loadDetails() const
{
    QxTdClient::instance()->send(QJsonObject{
            { "@type", "getStickerSet" },
            { "set_id", m_id.toJsonValue() },
    });
}

void QxTdStickerSet::handleDetails(const QJsonObject &json)
{
    if (m_detailsLoaded) {
        return;
    }
    const QJsonValue value = json["id"];
    QxTdInt64 tdId;
    tdId = value;
    if (tdId.value() == m_id.value()) {
        this->unmarshalJson(json);
        m_detailsLoaded = true;
    }
}

void QxTdStickerSet::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_id = json["id"];
    m_title = json["title"].toString();
    m_name = json["name"].toString();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
        m_hasThumbnail = true;
    } else {
        m_hasThumbnail = false;
    }
    m_format.reset(QxTdStickerFormatFactory::create(json["format"].toObject(), this));
    m_type.reset(QxTdStickerTypeFactory::create(json["type"].toObject(), this));
    m_isAnimated = json["is_animated"].toBool();
    m_isInstalled = json["is_installed"].toBool();
    m_isArchived = json["is_archived"].toBool();
    m_isOfficial = json["is_official"].toBool();

    if (json.contains("covers") && !m_hasThumbnail) {
        auto coversArray = json["covers"].toArray();
        if (!coversArray.isEmpty()) {
            auto coverSticker = coversArray[0].toObject();
            m_thumbnail->unmarshalJson(coverSticker["thumbnail"].toObject());
        }
    }
    if (json.contains("stickers")) {
        auto stickersArray = json["stickers"].toArray();
        for (auto stickerJSON : stickersArray) {
            QxTdSticker *sticker = new QxTdSticker(this);
            sticker->unmarshalJson(stickerJSON.toObject());
            m_stickers->append(sticker);
        }
    }
    emit stickerSetChanged();
}
