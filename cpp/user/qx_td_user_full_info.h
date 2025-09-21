#ifndef QX_TD_USER_FULL_INFO_H
#define QX_TD_USER_FULL_INFO_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdUserFullInfo class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_full_info.html
 */
class QxTdUserFullInfo : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(bool isBlocked READ isBlocked NOTIFY userFullInfoChanged)
    Q_PROPERTY(bool canBeCalled READ canBeCalled NOTIFY userFullInfoChanged)
    Q_PROPERTY(bool hasPrivateCalls READ hasPrivateCalls NOTIFY userFullInfoChanged)
    Q_PROPERTY(QString bio READ bio NOTIFY userFullInfoChanged)
    Q_PROPERTY(QString shareText READ shareText NOTIFY userFullInfoChanged)
    Q_PROPERTY(qint32 groupInCommonCount READ groupInCommonCount NOTIFY userFullInfoChanged)
    QML_ELEMENT
    //TODO Implement botInfo
    //Q_PROPERTY(QxTdBotInfo *botInfo...)

public:
    explicit QxTdUserFullInfo(QObject *parent = nullptr);

    bool isBlocked() const;
    bool canBeCalled() const;
    bool hasPrivateCalls() const;
    QString bio() const;
    QString shareText() const;
    qint32 groupInCommonCount() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void userFullInfoChanged();

private:
    Q_DISABLE_COPY(QxTdUserFullInfo)
    bool m_isBlocked;
    bool m_canBeCalled;
    bool m_hasPrivateCalls;
    QString m_bio;
    QString m_shareText;
    qint32 m_groupInCommonCount;
};

#endif // QX_TD_USER_FULL_INFO_H
