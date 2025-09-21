#ifndef QX_TD_MESSAGE_CHAT_CHANGE_PHOTO_H
#define QX_TD_MESSAGE_CHAT_CHANGE_PHOTO_H

#include "files/qx_td_photos.h"
#include "messages/qx_td_message_content.h"

/**
 * @brief The QxTdMessageChatChangePhoto class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_chat_change_photo.html
 */
class QxTdMessageChatChangePhoto : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdPhotos *photo READ photo NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatChangePhoto cannot be created in QML.")
public:
    explicit QxTdMessageChatChangePhoto(QObject *parent = nullptr);

    QxTdPhotos *photo() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QScopedPointer<QxTdPhotos> m_photo;
};

#endif // QX_TD_MESSAGE_CHAT_CHANGE_PHOTO_H
