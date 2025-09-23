#ifndef QX_TD_MESSAGE_FORWARD_INFO_H
#define QX_TD_MESSAGE_FORWARD_INFO_H

#include <QDateTime>

#include "qx_td_message_forward_origin.h"

/**
 * @brief The QxTdMessageForwardInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_forward_info.html
 */
class QxTdMessageForwardInfo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QxTdMessageForwardOrigin *origin READ origin NOTIFY forwardInfoChanged)
    Q_PROPERTY(QDateTime date READ qmlDate NOTIFY forwardInfoChanged)
    Q_PROPERTY(QString fromChatId READ qmlFromChatId NOTIFY forwardInfoChanged)
    Q_PROPERTY(QString fromMessageId READ qmlFromMessageId NOTIFY forwardInfoChanged)
    // These aren't original properties of the tdlib message class but we can
    // can make life easier for use in QML.
    Q_PROPERTY(QString displayedName READ displayedName NOTIFY forwardInfoChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageForwardInfo(QObject *parent = nullptr);

    QxTdMessageForwardOrigin *origin() const;
    QDateTime qmlDate() const;
    qint32 date() const;
    QString qmlFromChatId() const;
    qint64 fromChatId() const;
    QString qmlFromMessageId() const;
    qint64 fromMessageId() const;
    QString displayedName() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void forwardInfoChanged();

private:
    std::unique_ptr<QxTdMessageForwardOrigin> m_origin;
    qint32 m_date;
    QxTdInt64 m_fromChatId;
    QxTdInt64 m_fromMessageId;
    QString m_displayedName;
};

#endif // QX_TD_MESSAGE_FORWARD_INFO_H
