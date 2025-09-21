#ifndef QX_TD_MESSAGE_CONTACT_H
#define QX_TD_MESSAGE_CONTACT_H

#include <QScopedPointer>
#include "messages/qx_td_message_content.h"
#include "user/qx_td_contact.h"

class QxTdMessageContact : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdContact *contact READ contact NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageContact cannot be created in QML.")

public:
    explicit QxTdMessageContact(QObject *parent = nullptr);

    QxTdContact *contact() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();
    
private:
    Q_DISABLE_COPY(QxTdMessageContact)
    QScopedPointer<QxTdContact> m_contact;
};

#endif // QX_TD_MESSAGE_CONTACT_H

