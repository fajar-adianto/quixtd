#include "qx_td_message_sending_state.h"

QxTdMessageSendingState::QxTdMessageSendingState(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdMessageSendingStateFailed::QxTdMessageSendingStateFailed(QObject *parent)
    : QxTdMessageSendingState(parent)
{
    setType(MESSAGE_SENDING_STATE_FAILED);
}

QxTdMessageSendingStatePending::QxTdMessageSendingStatePending(QObject *parent)
    : QxTdMessageSendingState(parent)
{
    setType(MESSAGE_SENDING_STATE_PENDING);
}
