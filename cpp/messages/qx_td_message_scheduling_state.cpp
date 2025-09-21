#include "qx_td_message_scheduling_state.h"

QxTdMessageSchedulingState::QxTdMessageSchedulingState(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdMessageSchedulingStateSendAtDate::QxTdMessageSchedulingStateSendAtDate(QObject *parent)
    : QxTdMessageSchedulingState(parent)
{
    setType(MESSAGE_SCHEDULING_STATE_AT_DATE);
}

QxTdMessageSchedulingStateSendWhenOnline::QxTdMessageSchedulingStateSendWhenOnline(QObject *parent)
    : QxTdMessageSchedulingState(parent)
{
    setType(MESSAGE_SCHEDULING_STATE_WHEN_ONLINE);
}
