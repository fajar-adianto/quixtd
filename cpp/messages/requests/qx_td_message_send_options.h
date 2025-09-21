#ifndef QX_TD_MESSAGE_SEND_OPTIONS_H
#define QX_TD_MESSAGE_SEND_OPTIONS_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdMessageSendOptions class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_send_options.html
 */
class QxTdMessageSendOptions : public QxTdObject
{
    Q_OBJECT

public:
    explicit QxTdMessageSendOptions(QObject *parent = nullptr);

    void setDisableNotifications(const bool value);
    void setSendDate(const qint32 value);
    QJsonObject marshalJson();

signals:


private:
    Q_DISABLE_COPY(QxTdMessageSendOptions)

    bool m_disableNotifications;
    bool m_fromBackground;
    qint32 m_sendDate;
};





#endif //QX_TD_MESSAGE_SEND_OPTIONS_H
