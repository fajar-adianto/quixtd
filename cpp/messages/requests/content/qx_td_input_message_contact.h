#ifndef QX_TD_INPUT_MESSAGE_CONTACT_H
#define QX_TD_INPUT_MESSAGE_CONTACT_H

#include <QString>

#include "../qx_td_input_message_content.h"
#include "user/qx_td_contact.h"

class QxTdInputMessageContact : public QxTdInputMessageContent
{
    Q_OBJECT
    
public:
    explicit QxTdInputMessageContact(QObject *parent = nullptr);
    QJsonObject marshalJson();
    QxTdContact *contact();

private:
    QScopedPointer<QxTdContact> m_contact;
    Q_DISABLE_COPY(QxTdInputMessageContact)
};

#endif // QX_TD_INPUT_MESSAGE_CONTACT_H
