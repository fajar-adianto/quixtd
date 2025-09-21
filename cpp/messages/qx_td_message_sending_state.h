#ifndef QX_TD_MESSAGE_SENDING_STATE_H
#define QX_TD_MESSAGE_SENDING_STATE_H

#include "common/qx_td_object.h"

class QxTdMessageSendingState : public QxTdObject
{
    Q_OBJECT
public:
    explicit QxTdMessageSendingState(QObject *parent = nullptr);
};

class QxTdMessageSendingStateFailed : public QxTdMessageSendingState
{
    Q_OBJECT
public:
    explicit QxTdMessageSendingStateFailed(QObject *parent = nullptr);
};

class QxTdMessageSendingStatePending : public QxTdMessageSendingState
{
    Q_OBJECT
public:
    explicit QxTdMessageSendingStatePending(QObject *parent = nullptr);
};
#endif // QX_TD_MESSAGE_SENDING_STATE_H
