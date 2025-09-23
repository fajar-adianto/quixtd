#ifndef QX_TD_MESSAGE_VIDEO_H
#define QX_TD_MESSAGE_VIDEO_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_video.h"
#include "qx_td_formatted_text.h"

class QxTdMessageVideo : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdVideo *video READ video NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageVideo cannot be created in QML.")
public:
    explicit QxTdMessageVideo(QObject *parent = nullptr);

    QxTdVideo *video() const;
    QxTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageVideo)
    std::unique_ptr<QxTdVideo> m_video;
    std::unique_ptr<QxTdFormattedText> m_caption;
};

#endif // QX_TD_MESSAGE_VIDEO_H
