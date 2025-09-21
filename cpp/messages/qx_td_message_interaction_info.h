#ifndef QX_TD_MESSAGE_INTERACTION_INFO_H
#define QX_TD_MESSAGE_INTERACTION_INFO_H

#include "common/qx_td_object.h"
#include "common/qx_td_int.h"

/**
 * @brief The QxTdMessageInteractionInfo
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_interaction_info.html
 */
class QxTdMessageInteractionInfo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString viewCount READ qmlViewCount NOTIFY interactionInfoChanged)
    Q_PROPERTY(QString forwardCount READ qmlForwardCount NOTIFY interactionInfoChanged)
    QML_ELEMENT
    // TODO: add QxTdMessageReplyInfo
public:
    explicit QxTdMessageInteractionInfo(QObject *parent = nullptr);

    qint32 viewCount() const;
    QString qmlViewCount() const;
    qint32 forwardCount() const;
    QString qmlForwardCount() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void interactionInfoChanged();

private:
    Q_DISABLE_COPY(QxTdMessageInteractionInfo)

    QxTdInt32 m_viewCount;
    QxTdInt32 m_forwardCount;
};

#endif // QX_TD_MESSAGE_INTERACTION_INFO_H
