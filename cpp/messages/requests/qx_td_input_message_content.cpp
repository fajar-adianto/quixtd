#include "qx_td_input_message_content.h"

QxTdInputMessageContent::QxTdInputMessageContent(QObject *parent)
    : QxTdObject(parent)
{
    setType(INPUT_MESSAGE);
}
