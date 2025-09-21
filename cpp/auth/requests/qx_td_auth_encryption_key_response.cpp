#include "qx_td_auth_encryption_key_response.h"

QxTdAuthEncryptionKeyResponse::QxTdAuthEncryptionKeyResponse(QObject *parent)
    : QxTdOkRequest(parent)
{
    // Intentionally left empty.
}

void QxTdAuthEncryptionKeyResponse::setKey(const QString &key)
{
    m_key = key;
}

QJsonObject QxTdAuthEncryptionKeyResponse::marshalJson()
{
    return QJsonObject{
        { "@type", "setDatabaseEncryptionKey" },
        { "new_encryption_key", m_key },
    };
}
