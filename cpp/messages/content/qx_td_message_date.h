#ifndef QX_TD_MESSAGE_DATE_H
#define QX_TD_MESSAGE_DATE_H

#include "messages/qx_td_message_content.h"

class QxTdMessageDate : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QDateTime date READ date NOTIFY dataChanged)
    Q_PROPERTY(QString dateString READ dateString NOTIFY dataChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageDate(QObject *parent = nullptr);

    QDateTime date() const;
    QString dateString() const;

    void setDate(const qint32 &date);

signals:
    void dataChanged();

private:
    qint32 m_date;
};

#endif // QX_TD_MESSAGE_DATE_H
