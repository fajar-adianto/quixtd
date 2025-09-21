#include "qx_td_message_unread_label.h"

QxTdMessageUnreadLabel::QxTdMessageUnreadLabel(QObject *parent)
    : QxTdMessageContent(parent)
    , m_label("")
{
    setType(MESSAGE_UNREAD_LABEL);
}

QString QxTdMessageUnreadLabel::label()
{
    return m_label;
}

void QxTdMessageUnreadLabel::setLabel(const QString label)
{
    m_label = label;
}
