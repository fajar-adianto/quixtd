#include "qx_td_message_content.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageContent::QxTdMessageContent(QObject *parent)
    : QxTdObject(parent),
    m_infoText(""),
    m_typeText(""),
    m_isSecret(false),
    m_infoImageUrl(QUrl())
{
}

QString QxTdMessageContent::infoText() const
{
    return m_infoText;
}

QString QxTdMessageContent::typeText() const
{
    return m_typeText;
}

QUrl QxTdMessageContent::infoImageUrl() const
{
    return m_infoImageUrl;
}

bool QxTdMessageContent::isSecret() const
{
    return m_isSecret;
}

void QxTdMessageContent::setInfoText(const QString &infoText)
{
    m_infoText = infoText;
}

void QxTdMessageContent::setTypeText(const QString &typeText)
{
    m_typeText = typeText;
}

QxTdMessageAction::QxTdMessageAction(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_ACTION);
}

QxTdMessageHidden::QxTdMessageHidden(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_HIDDEN);
}
