#ifndef QX_TD_MESSAGE_SCHEDULING_STATE_H
#define QX_TD_MESSAGE_SCHEDULING_STATE_H

#include "common/qx_td_object.h"

class QxTdMessageSchedulingState : public QxTdObject
{
    Q_OBJECT
public:
    explicit QxTdMessageSchedulingState(QObject *parent = nullptr);
};

class QxTdMessageSchedulingStateSendAtDate : public QxTdMessageSchedulingState
{
    Q_OBJECT
public:
    explicit QxTdMessageSchedulingStateSendAtDate(QObject *parent = nullptr);
};

class QxTdMessageSchedulingStateSendWhenOnline : public QxTdMessageSchedulingState
{
    Q_OBJECT
public:
    explicit QxTdMessageSchedulingStateSendWhenOnline(QObject *parent = nullptr);
};
#endif // QX_TD_MESSAGE_SCHEDULING_STATE_H
