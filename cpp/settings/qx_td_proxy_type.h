#ifndef QX_TD_PROXY_TYPE_H
#define QX_TD_PROXY_TYPE_H

#include <QObject>
#include <common/qx_td_object.h>

class QxTdProxyType: public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY dataChanged)
    Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY dataChanged)
    Q_PROPERTY(QString secret READ secret WRITE setSecret NOTIFY dataChanged)
    Q_PROPERTY(int type READ qmlType NOTIFY dataChanged)
    Q_PROPERTY(QString typeString READ typeString NOTIFY dataChanged)
    Q_PROPERTY(bool httpOnly READ httpOnly WRITE setHttpOnly NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdProxyType cannot be created in QML.")
public:

    explicit QxTdProxyType(QObject *parent = nullptr);
    static QxTdProxyType *create(const QJsonObject &json, QObject *parent);
    QJsonObject marshalJson() override;
    void unmarshalJson(const QJsonObject &json) override;

    int qmlType() const;
    QString typeString() const;
    QString username() const;
    void setUsername(QString value);
    QString password() const;
    void setPassword(QString value);
    QString secret() const;
    void setSecret(QString value);
    bool httpOnly() const;
    void setHttpOnly(bool value);

signals:
    void dataChanged();

protected:
    QString m_username;
    QString m_password;
    QString m_secret;
    bool m_httpOnly;
};

class QxTdProxyTypeHttp: public QxTdProxyType
{
    Q_OBJECT
public:
    explicit QxTdProxyTypeHttp(QObject *parent = nullptr);

};

class QxTdProxyTypeMtproto: public QxTdProxyType
{
    Q_OBJECT
public:
    explicit QxTdProxyTypeMtproto(QObject *parent = nullptr);
};

class QxTdProxyTypeSocks5: public QxTdProxyType
{
    Q_OBJECT
public:
    explicit QxTdProxyTypeSocks5(QObject *parent = nullptr);
};

#endif // QX_TD_PROXY_TYPE_H
