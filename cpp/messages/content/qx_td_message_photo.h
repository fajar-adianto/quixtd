#ifndef QX_TD_MESSAGE_PHOTO_H
#define QX_TD_MESSAGE_PHOTO_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_photos.h"
#include "qx_td_formatted_text.h"

class QxTdMessagePhoto : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdPhotos *photo READ photo NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessagePhoto cannot be created in QML.")
public:
    explicit QxTdMessagePhoto(QObject *parent = nullptr);

    QxTdPhotos *photo() const;
    QxTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessagePhoto)
    std::unique_ptr<QxTdPhotos> m_photo;
    std::unique_ptr<QxTdFormattedText> m_caption;
};

#endif // QX_TD_MESSAGE_PHOTO_H
