#include "qx_td_secret_chat_state.h"

QxTdSecretChatState::QxTdSecretChatState(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdSecretChatStateClosed::QxTdSecretChatStateClosed(QObject *parent)
    : QxTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_CLOSED);
}

QxTdSecretChatStatePending::QxTdSecretChatStatePending(QObject *parent)
    : QxTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_PENDING);
}

QxTdSecretChatStateReady::QxTdSecretChatStateReady(QObject *parent)
    : QxTdSecretChatState(parent)
{
    setType(SECRET_CHAT_STATE_READY);
}
