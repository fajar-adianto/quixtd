#include "qx_td_response.h"

QxTdResponse::QxTdResponse(QObject *parent)
{
    // Intentionally left empty.
}

bool QxTdResponse::isError() const
{
    if (m_json.contains("@type")) {
        return m_json.value("@type").toString() == "error";
    }
    return false;
}

QString QxTdResponse::errorString() const
{
    return isError() ? m_json.value("message").toString() : QString();
}

int QxTdResponse::errorCode() const
{
    return isError() ? m_json.value("code").toInt() : 0;
}

bool QxTdResponse::isOk() const
{
    if (m_json.contains("@type")) {
        return m_json.value("@type").toString() == "ok";
    }
    return false;
}

QJsonObject QxTdResponse::json() const
{
    return m_json;
}

void QxTdResponse::setJson(const QJsonObject &json)
{
    m_json = json;
}
