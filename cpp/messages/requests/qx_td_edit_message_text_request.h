#ifndef QX_TD_EDIT_MESSAGE_TEXT_REQUEST_H
#define QX_TD_EDIT_MESSAGE_TEXT_REQUEST_H

#include "common/qx_td_request.h"

class QxTdEditMessageTextRequest : public QxTdRequest
{
    Q_OBJECT
    qint64 m_chatId;
    qint64 m_messageId;
    QString m_text;
    QJsonArray m_entities;

public:
    explicit QxTdEditMessageTextRequest(QObject *parent = nullptr);
    void setText(const QString &text);
    void setChatId(const qint64 &id);
    void setMessageId(const qint64 &id);
    void setEntities(const QJsonArray &entities);
    QJsonObject marshalJson();
    virtual QFuture<QxTdResponse> sendAsync();
};

#endif // QX_TD_EDIT_MESSAGE_TEXT_REQUEST_H
