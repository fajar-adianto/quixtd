#ifndef QTDTOGGLEMESSAGESENDERISBLOCKED_H
#define QTDTOGGLEMESSAGESENDERISBLOCKED_H

#include <QObject>
#include <QScopedPointer>

#include "common/qtdrequest.h"
#include "../qtdmessagesender.h"

class QTdToggleMessageSenderIsBlockedRequest : public QTdOkRequest
{
    Q_OBJECT

public:
    explicit QTdToggleMessageSenderIsBlockedRequest(QObject *parent = nullptr);
    void setSenderId(QTdMessageSender *senderId);
    void setIsBlocked(const bool &isBlocked);
    QJsonObject marshalJson();

private:
    Q_DISABLE_COPY(QTdToggleMessageSenderIsBlockedRequest)
    QTdMessageSender *m_senderId;
    bool m_isBlocked;
};

#endif // QTDTOGGLEMESSAGESENDERISBLOCKED_H
