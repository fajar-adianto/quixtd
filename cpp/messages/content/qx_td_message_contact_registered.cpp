#include "qx_td_message_contact_registered.h"
#include "utils/qx_td_await.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageContactRegistered::QxTdMessageContactRegistered(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CONTACT_REGISTERED);
    m_typeText = qxTranslate("has joined Telegram!");
}
