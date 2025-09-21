#ifndef QX_TD_MESSAGE_CHAT_CHANGE_TITLE_H
#define QX_TD_MESSAGE_CHAT_CHANGE_TITLE_H

#include "messages/qx_td_message_content.h"

class QxTdMessageChatChangeTitle : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageChatChangeTitle)
    Q_PROPERTY(QString title READ title NOTIFY contentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageChatChangeTitle cannot be created in QML.")
public:
    explicit QxTdMessageChatChangeTitle(QObject *parent = nullptr);

    QString title() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_title;
};

#endif // QX_TD_MESSAGE_CHAT_CHANGE_TITLE_H
