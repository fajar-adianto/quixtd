#include "qx_td_auth_resend_code_request.h"

QxTdAuthResendCodeRequest::QxTdAuthResendCodeRequest(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

QJsonObject QxTdAuthResendCodeRequest::marshalJson()
{
    return QJsonObject {
        { "@type", "resendPhoneNumberConfirmationCode" }
    };
}
