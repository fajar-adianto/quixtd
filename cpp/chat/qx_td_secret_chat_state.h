#ifndef QX_TD_SECRET_CHAT_STATE_H
#define QX_TD_SECRET_CHAT_STATE_H

#include <QObject>
#include "common/qx_td_object.h"

class QxTdSecretChatState : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSecretChatState)
public:
    explicit QxTdSecretChatState(QObject *parent = nullptr);
};

class QxTdSecretChatStateClosed : public QxTdSecretChatState
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSecretChatStateClosed)
public:
    explicit QxTdSecretChatStateClosed(QObject *parent = nullptr);
};

class QxTdSecretChatStatePending : public QxTdSecretChatState
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSecretChatStatePending)
public:
    explicit QxTdSecretChatStatePending(QObject *parent = nullptr);
};

class QxTdSecretChatStateReady : public QxTdSecretChatState
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdSecretChatStateReady)
public:
    explicit QxTdSecretChatStateReady(QObject *parent = nullptr);
};

#endif // QX_TD_SECRET_CHAT_STATE_H
