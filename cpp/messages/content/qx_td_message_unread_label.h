#ifndef QX_TD_MESSAGE_UNREAD_LABEL_H
#define QX_TD_MESSAGE_UNREAD_LABEL_H

#include "messages/qx_td_message_content.h"

class QxTdMessageUnreadLabel : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QString label READ label NOTIFY labelChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageUnreadLabel(QObject *parent = nullptr);

    void setLabel(const QString label);
    QString label();

signals:
    void labelChanged();

private:
    QString m_label;
};

#endif // QX_TD_MESSAGE_UNREAD_LABEL_H
