#ifndef QX_TD_CONTACT_H
#define QX_TD_CONTACT_H

#include <QPointer>
#include "common/qx_td_object.h"
#include "qx_td_user.h"

class QxTdContact: public QxTdObject {
    Q_OBJECT
    Q_PROPERTY(QString phoneNumber READ phoneNumber WRITE setPhoneNumber NOTIFY dataChanged)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY dataChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY dataChanged)
    Q_PROPERTY(QString initials READ initials NOTIFY dataChanged)
    Q_PROPERTY(QString vcard READ vcard WRITE setVcard NOTIFY dataChanged)
    Q_PROPERTY(qint64 userId READ userId WRITE setUserId NOTIFY dataChanged)
    Q_PROPERTY(QxTdUser *user READ user NOTIFY userChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdContact cannot be created in QML.")
public:
    explicit QxTdContact(QObject *parent = nullptr);

    QString phoneNumber() const;
    QString firstName() const;
    QString lastName() const;
    QString vcard() const;
    qint64 userId() const;
    QxTdUser *user() const;
    QString initials() const;

    void setPhoneNumber(QString value);
    void setFirstName(QString value);
    void setLastName(QString value);
    void setVcard(QString value);
    void setUserId(qint64 value);

    void unmarshalJson(const QJsonObject &json) override;
    QJsonObject marshalJson() override;

signals:
    void dataChanged();
    void userChanged();

private:
    Q_DISABLE_COPY(QxTdContact)
    void getUserFromModel(qint64 id);
    QPointer<QxTdUser> m_user;
    QString m_phoneNumber;
    QString m_firstName;
    QString m_lastName;
    QString m_vcard;
    qint64 m_userId;
};

#endif // QX_TD_CONTACT_H
