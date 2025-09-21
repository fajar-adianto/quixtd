#include "qx_td_proxy_type.h"

QxTdProxyType::QxTdProxyType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QString QxTdProxyType::username() const {
    return m_username;
}

void QxTdProxyType::setUsername(QString value) {
    m_username = value;
}

QString QxTdProxyType::password() const {
    return m_password;
}

void QxTdProxyType::setPassword(QString value) {
    m_password = value;
}

QString QxTdProxyType::secret() const
{
    return m_secret;
}

void QxTdProxyType::setSecret(QString value) {
    m_secret = value;
}

bool QxTdProxyType::httpOnly() const
{
    return m_httpOnly;
}

void QxTdProxyType::setHttpOnly(bool value) {
    m_httpOnly = value;
}

int QxTdProxyType::qmlType() const
{
    switch(type()) {
        case PROXY_TYPE_HTTP:
            return 0;
        case PROXY_TYPE_MTPROTO:
            return 1;
        case PROXY_TYPE_SOCKS5:
            return 2;
        default:
            return -1;
    }
}

QString QxTdProxyType::typeString() const
{
    switch(type()) {
        case PROXY_TYPE_HTTP:
            return "HTTP";
        case PROXY_TYPE_MTPROTO:
            return "MTProto";
        case PROXY_TYPE_SOCKS5:
            return "SOCKS5";
        default:
            return "";
    }
}

QxTdProxyType *QxTdProxyType::create(const QJsonObject &json, QObject *parent) {
    const QString type = json["@type"].toString();
    QxTdProxyType *proxyType = nullptr;
    if (type == "proxyTypeHttp") {
        proxyType = new QxTdProxyTypeHttp(parent);
    } else if (type == " proxyTypeMtproto") {
        proxyType = new QxTdProxyTypeMtproto(parent);
    } else if (type == "proxyTypeSocks5") {
        proxyType = new QxTdProxyTypeSocks5(parent);
    }
    if (proxyType != nullptr) {
        proxyType->unmarshalJson(json);
    }
    return proxyType;
}

QJsonObject QxTdProxyType::marshalJson()
{
    auto result = QJsonObject{
        { "username", m_username },
        { "password", m_password },
        { "secret", m_secret },
        { "http_only", m_httpOnly }
    };
    switch(type()) {
        case QxTdObject::Type::PROXY_TYPE_HTTP:
            result["@type"] = "proxyTypeHttp";
            break;
        case QxTdObject::Type::PROXY_TYPE_MTPROTO:
            result["@type"] = "proxyTypeMtproto";
            break;
        case QxTdObject::Type::PROXY_TYPE_SOCKS5:
            result["@type"] = "proxyTypeSocks5";
            break;
        default:
            break;
    }
    return result;
}

void QxTdProxyType::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_username = json["username"].toString();
    m_password = json["password"].toString();
    m_secret = json["secret"].toString();
    m_httpOnly = json["http_only"].toBool();
    emit dataChanged();
}

QxTdProxyTypeHttp::QxTdProxyTypeHttp(QObject *parent)
    : QxTdProxyType(parent)
{
    setType(PROXY_TYPE_HTTP);
}

QxTdProxyTypeMtproto::QxTdProxyTypeMtproto(QObject *parent)
    : QxTdProxyType(parent)
{
    setType(PROXY_TYPE_MTPROTO);
}

QxTdProxyTypeSocks5::QxTdProxyTypeSocks5(QObject *parent)
    : QxTdProxyType(parent)
{
    setType(PROXY_TYPE_SOCKS5);
}
