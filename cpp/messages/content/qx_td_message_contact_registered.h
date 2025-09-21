#ifndef QX_TD_MESSAGE_CONTACT_REGISTERED_H
#define QX_TD_MESSAGE_CONTACT_REGISTERED_H

#include "messages/qx_td_message_content.h"

class QxTdMessageContactRegistered : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageContactRegistered)
public:
    explicit QxTdMessageContactRegistered(QObject *parent = nullptr);

};

#endif // QX_TD_MESSAGE_CONTACT_REGISTERED_H
