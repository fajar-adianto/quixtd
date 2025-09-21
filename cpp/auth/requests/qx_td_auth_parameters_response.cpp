#include "qx_td_auth_parameters_response.h"
#include "auth/qx_td_auth_params.h"

QxTdAuthParametersResponse::QxTdAuthParametersResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthParametersResponse::setParameters(QxTdAuthParams *params)
{
    m_params = params->marshalJson();
}

QJsonObject QxTdAuthParametersResponse::marshalJson()
{
    auto result = m_params;
    result.insert("@type", "setTdlibParameters");
    return result;
}
