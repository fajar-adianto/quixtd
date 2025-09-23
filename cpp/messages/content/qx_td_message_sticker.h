#ifndef QX_TD_MESSAGE_STICKER_H
#define QX_TD_MESSAGE_STICKER_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_sticker.h"

class QxTdMessageSticker : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdSticker *sticker READ sticker NOTIFY dataChanged)
    Q_PROPERTY(bool isPremium READ isPremium NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageSticker cannot be created in QML.")
public:
    explicit QxTdMessageSticker(QObject *parent = nullptr);

    QxTdSticker *sticker() const;

    bool isPremium() const;
    
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageSticker)
    std::unique_ptr<QxTdSticker> m_sticker;
    bool m_is_premium;
};

#endif // QX_TD_MESSAGE_STICKER_H
