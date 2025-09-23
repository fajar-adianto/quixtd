#ifndef QX_TD_ANIMATION_H
#define QX_TD_ANIMATION_H

#include "qx_td_thumbnail.h"
#include "qx_td_mini_thumbnail.h"

/**
 * @brief The QxTdAnimation class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1animation.html
 */
class QxTdAnimation : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 duration READ duration NOTIFY animationChanged)
    Q_PROPERTY(qint32 width READ width NOTIFY animationChanged)
    Q_PROPERTY(qint32 height READ height NOTIFY animationChanged)
    Q_PROPERTY(QString fileName READ fileName NOTIFY animationChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY animationChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY animationChanged)
    Q_PROPERTY(QxTdMiniThumbnail *miniThumbnail READ miniThumbnail NOTIFY animationChanged)
    Q_PROPERTY(QxTdFile *animation READ animation NOTIFY animationChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdAnimation cannot be created in QML.")
public:
    explicit QxTdAnimation(QObject *parent = nullptr);

    qint32 duration() const;

    qint32 width() const;

    qint32 height() const;

    QString fileName() const;

    QString mimeType() const;

    QxTdThumbnail *thumbnail() const;

    QxTdMiniThumbnail *miniThumbnail() const;

    QxTdFile *animation() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void animationChanged();

private:
    qint32 m_duration;
    qint32 m_width;
    qint32 m_height;
    QString m_fileName;
    QString m_mimeType;
    std::unique_ptr<QxTdThumbnail> m_thumbnail;
    std::unique_ptr<QxTdMiniThumbnail> m_minithumbnail;
    std::unique_ptr<QxTdFile> m_animation;
};

#endif // QX_TD_ANIMATION_H
