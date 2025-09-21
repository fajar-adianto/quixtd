#ifndef QX_TD_CHAT_STATE_H
#define QX_TD_CHAT_STATE_H

#include <QObject>
#include <QtQmlIntegration/qqmlintegration.h>

class QxTdChatState
{
    Q_GADGET
    QML_ELEMENT
    QML_UNCREATABLE("QxTdChatState cannot be created in QML.")
public:
    enum ChatState {
        Default,
        EditingMessage,
        ReplyingToMessage,
    };
    Q_ENUM(ChatState)
private:
    explicit QxTdChatState();
};

#endif // QX_TD_CHAT_STATE_H
