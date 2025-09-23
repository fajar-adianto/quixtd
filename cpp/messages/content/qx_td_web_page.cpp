#include "qx_td_web_page.h"

QxTdWebPage::QxTdWebPage(QObject *parent)
    : QxTdObject(parent)
    , m_photo(new QxTdPhotos)
    , m_containsPhoto(false)
    , m_embedWidth(0)
    , m_embedheight(0)
    , m_duration(0)
    , m_animation(new QxTdAnimation)
    , m_audio(new QxTdAudio)
    , m_video(new QxTdVideo)
    , m_voiceNote(new QxTdVoiceNote)
    , m_document(new QxTdDocument)
    , m_sticker(new QxTdSticker)
    , m_hasInstantView(false)
{
    setType(WEB_PAGE);
}

QString QxTdWebPage::url() const
{
    return m_url;
}

QString QxTdWebPage::displayUrl() const
{
    return m_displayUrl;
}

QString QxTdWebPage::type() const
{
    return m_type;
}

QString QxTdWebPage::siteName() const
{
    return m_siteName;
}

QString QxTdWebPage::title() const
{
    return m_title;
}

QString QxTdWebPage::description() const
{
    return m_description;
}

QxTdPhotos *QxTdWebPage::photo() const
{
    return m_photo.get();
}
bool QxTdWebPage::containsPhoto() const
{
    return m_containsPhoto;
}

QString QxTdWebPage::embedUrl() const
{
    return m_embedUrl;
}

QString QxTdWebPage::embedType() const
{
    return m_embedType;
}

qint32 QxTdWebPage::embedWidth() const
{
    return m_embedWidth;
}

qint32 QxTdWebPage::embedHeight() const
{
    return m_embedheight;
}

qint32 QxTdWebPage::duration() const
{
    return m_duration;
}

QString QxTdWebPage::author() const
{
    return m_author;
}

QxTdAnimation *QxTdWebPage::animation() const
{
    return m_animation.get();
}

QxTdAudio *QxTdWebPage::audio() const
{
    return m_audio.get();
}
QxTdVideo *QxTdWebPage::video() const
{
    return m_video.get();
}

QxTdVoiceNote *QxTdWebPage::voiceNote() const
{
    return m_voiceNote.get();
}

QxTdDocument *QxTdWebPage::document() const
{
    return m_document.get();
}

QxTdSticker *QxTdWebPage::sticker() const
{
    return m_sticker.get();
}

bool QxTdWebPage::hasInstantView() const
{
    return m_hasInstantView;
}

void QxTdWebPage::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
        m_url = json["url"].toString();
    m_displayUrl = json["display_url"].toString();
    m_type = json["type"].toString();
    m_siteName = json["site_name"].toString();
    m_title = json["title"].toString();
    auto temp_description = json["description"].toObject();
    if (!temp_description.isEmpty()) {
        m_description = temp_description["text"].toString();
    }
    if (json.contains("photo")) {
        m_containsPhoto = true;
        m_photo->unmarshalJson(json["photo"].toObject());
    }
    m_embedUrl = json["embed_url"].toString();
    m_embedType = json["embed_type"].toString();
    m_embedWidth = qint32(json["embed_width"].toInt());
    m_embedheight = qint32(json["embed_height"].toInt());
    m_duration = qint32(json["duration"].toInt());
    m_author = json["author"].toString();

    if (json.contains("animation")) {
        m_animation->unmarshalJson(json["animation"].toObject());
    }

    if (json.contains("audio")) {
        m_audio->unmarshalJson(json["audio"].toObject());
    }

    if (json.contains("video")) {
        m_video->unmarshalJson(json["video"].toObject());
    }

    if (json.contains("voice_note")) {
        m_voiceNote->unmarshalJson(json["voiceNote"].toObject());
    }

    if (json.contains("document")) {
        m_document->unmarshalJson(json["document"].toObject());
    }

    if (json.contains("sticker")) {
        m_sticker->unmarshalJson(json["sticker"].toObject());
    }

    m_hasInstantView = json["has_instant_preview"].toBool();
    emit webPageChanged();
}
