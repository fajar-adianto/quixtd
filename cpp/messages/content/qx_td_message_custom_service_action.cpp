#include "qx_td_message_custom_service_action.h"
#include "utils/qx_td_await.h"

QxTdMessageCustomServiceAction::QxTdMessageCustomServiceAction(QObject *parent)
    : QxTdMessageContent(parent)
{
    setType(MESSAGE_CUSTOM_SERVICE_ACTION);
}

QString QxTdMessageCustomServiceAction::text() const
{
    return m_text;
}

void QxTdMessageCustomServiceAction::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    
    QxTdMessageContent::unmarshalJson(json);
    m_text = json["text"].toString();
    m_typeText = m_text;
    emit contentChanged();
}
