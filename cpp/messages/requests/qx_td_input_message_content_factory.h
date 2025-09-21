#ifndef QX_TD_INPUT_MESSAGE_CONTENT_FACTORY_H
#define QX_TD_INPUT_MESSAGE_CONTENT_FACTORY_H

#include <QObject>

class QxTdInputMessageContentAttachmentCaption; // Forward declaration.

enum InputMessageType {
    Photo,
    Video,
    Audio,
    Document,
};

struct QxTdInputMessageContentFactory
{
    static QxTdInputMessageContentAttachmentCaption *create(const InputMessageType type, QObject *parent = nullptr);
};

#endif // QX_TD_INPUT_MESSAGE_CONTENT_FACTORY_H
