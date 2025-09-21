#ifndef QX_TD_INPUT_MESSAGE_STICKER_H
#define QX_TD_INPUT_MESSAGE_STICKER_H

#include "../qx_td_input_message_content.h"

class QxTdSticker; // Forward declaration.

class QxTdInputMessageSticker : public QxTdInputMessageContent
{
    Q_OBJECT

public:
    explicit QxTdInputMessageSticker(QObject *parent = nullptr);

    void setSticker(QxTdSticker *sticker);

    QJsonObject marshalJson();

private:
    QxTdSticker *m_sticker;
    Q_DISABLE_COPY(QxTdInputMessageSticker)
};

#endif // QX_TD_INPUT_MESSAGE_STICKER_H
