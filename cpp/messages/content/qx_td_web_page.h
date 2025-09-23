#ifndef QX_TD_WEB_PAGE_H
#define QX_TD_WEB_PAGE_H

#include "files/qx_td_photos.h"
#include "files/qx_td_animation.h"
#include "files/qx_td_audio.h"
#include "files/qx_td_video.h"
#include "files/qx_td_document.h"
#include "files/qx_td_sticker.h"
#include "files/qx_td_voice_note.h"

class QxTdWebPage : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString url READ url NOTIFY webPageChanged)
    Q_PROPERTY(QString displayUrl READ displayUrl NOTIFY webPageChanged)
    Q_PROPERTY(QString type READ type NOTIFY webPageChanged)
    Q_PROPERTY(QString siteName READ siteName NOTIFY webPageChanged)
    Q_PROPERTY(QString title READ title NOTIFY webPageChanged)
    Q_PROPERTY(QString description READ description NOTIFY webPageChanged)
    Q_PROPERTY(QxTdPhotos *photo READ photo NOTIFY webPageChanged)
    Q_PROPERTY(bool containsPhoto READ containsPhoto NOTIFY webPageChanged)
    Q_PROPERTY(QString embedUrl READ embedUrl NOTIFY webPageChanged)
    Q_PROPERTY(QString embedType READ embedType NOTIFY webPageChanged)
    Q_PROPERTY(qint32 embedWidth READ embedWidth NOTIFY webPageChanged)
    Q_PROPERTY(qint32 embedheight READ embedHeight NOTIFY webPageChanged)
    Q_PROPERTY(qint32 duration READ duration NOTIFY webPageChanged)
    Q_PROPERTY(QString author READ author NOTIFY webPageChanged)
    Q_PROPERTY(QxTdAnimation *animation READ animation NOTIFY webPageChanged)
    Q_PROPERTY(QxTdAudio *audio READ audio NOTIFY webPageChanged)
    Q_PROPERTY(QxTdVideo *video READ video NOTIFY webPageChanged)
    Q_PROPERTY(QxTdVoiceNote *voiceNote READ voiceNote NOTIFY webPageChanged)
    Q_PROPERTY(QxTdDocument *document READ document NOTIFY webPageChanged)
    Q_PROPERTY(QxTdSticker *sticker READ sticker NOTIFY webPageChanged)
    /**
      TODO: QxTdVideo, QxTdVideoNote QxTdVoiceNote
     */
    Q_PROPERTY(bool hasInstantView READ hasInstantView NOTIFY webPageChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdWebPage cannot be created in QML.")
public:
    explicit QxTdWebPage(QObject *parent = nullptr);

    QString url() const;

    QString displayUrl() const;

    QString type() const;

    QString siteName() const;

    QString title() const;

    QString description() const;

    QxTdPhotos *photo() const;
    bool containsPhoto() const;

    QString embedUrl() const;

    QString embedType() const;

    qint32 embedWidth() const;

    qint32 embedHeight() const;

    qint32 duration() const;

    QString author() const;

    QxTdAnimation *animation() const;

    QxTdAudio *audio() const;

    QxTdVideo *video() const;

    QxTdVoiceNote *voiceNote() const;

    QxTdDocument *document() const;

    QxTdSticker *sticker() const;

    bool hasInstantView() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void webPageChanged();

private:
    QString m_url;
    QString m_displayUrl;
    QString m_type;
    QString m_siteName;
    QString m_title;
    //TODO 1.7.9 change to formattedText
    QString m_description;
    std::unique_ptr<QxTdPhotos> m_photo;
    bool m_containsPhoto;
    QString m_embedUrl;
    QString m_embedType;
    qint32 m_embedWidth;
    qint32 m_embedheight;
    qint32 m_duration;
    QString m_author;
    std::unique_ptr<QxTdAnimation> m_animation;
    std::unique_ptr<QxTdAudio> m_audio;
    std::unique_ptr<QxTdDocument> m_document;
    std::unique_ptr<QxTdSticker> m_sticker;
    std::unique_ptr<QxTdVideo> m_video;
    std::unique_ptr<QxTdVoiceNote> m_voiceNote;
    bool m_hasInstantView;
};

#endif // QX_TD_WEB_PAGE_H
