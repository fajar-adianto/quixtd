#ifndef QX_TD_MESSAGE_CUSTOM_SERVICE_ACTION_H
#define QX_TD_MESSAGE_CUSTOM_SERVICE_ACTION_H

#include "messages/qx_td_message_content.h"

class QxTdMessageCustomServiceAction : public QxTdMessageContent
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdMessageCustomServiceAction)
    Q_PROPERTY(QString text READ text NOTIFY contentChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageCustomServiceAction(QObject *parent = nullptr);

    QString text() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void contentChanged();

private:
    QString m_text;
};

#endif // QX_TD_MESSAGE_CUSTOM_SERVICE_ACTION_H
