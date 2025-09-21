#ifndef QX_TD_AUTH_ENCRYPTION_KEY_RESPONSE_H
#define QX_TD_AUTH_ENCRYPTION_KEY_RESPONSE_H

#include <QObject>
#include "common/qx_td_request.h"

/**
 * @brief The QxTdAuthEncryptionKeyResponse class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1set_database_encryption_key.html
 */
class QxTdAuthEncryptionKeyResponse : public QxTdOkRequest
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdAuthEncryptionKeyResponse)
public:
    explicit QxTdAuthEncryptionKeyResponse(QObject *parent = nullptr);

    /**
     * @brief setKey
     * @param key - New encryption key
     */
    void setKey(const QString &key);

    /**
     * @brief marshalJson
     * @return QJsonObject of the request suitable for sending to tdlib
     */
    QJsonObject marshalJson();

private:
    QString m_key;
};

#endif // QX_TD_AUTH_ENCRYPTION_KEY_RESPONSE_H
