#ifndef QX_TD_USER_STATUS_H
#define QX_TD_USER_STATUS_H

#include <QDateTime>
#include "common/qx_td_object.h"

/**
 * @brief The QxTdUserStatus class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_user_status.html
 */
class QxTdUserStatus : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString string READ toString NOTIFY statusStringChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatus)
public:
    explicit QxTdUserStatus(QObject *parent = nullptr);
    virtual QString toString() const = 0;

signals:
    void statusStringChanged(QString status);
};

/**
 * @brief The QxTdUserStatusEmpty class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_empty.html
 */
class QxTdUserStatusEmpty : public QxTdUserStatus
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatusEmpty)
public:
    explicit QxTdUserStatusEmpty(QObject *parent = nullptr);
    QString toString() const override;
};

/**
 * @brief The QxTdUserStateLastMonth class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_last_month.html
 */
class QxTdUserStateLastMonth : public QxTdUserStatus
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStateLastMonth)
public:
    explicit QxTdUserStateLastMonth(QObject *parent = nullptr);
    QString toString() const override;
};

/**
 * @brief The QxTdUserStatusLastWeek class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_last_week.html
 */
class QxTdUserStatusLastWeek : public QxTdUserStatus
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatusLastWeek)
public:
    explicit QxTdUserStatusLastWeek(QObject *parent = nullptr);
    QString toString() const override;
};

/**
 * @brief The QxTdUserStatusOffline class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_offline.html
 */
class QxTdUserStatusOffline : public QxTdUserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDateTime wasOnline READ wasOnline NOTIFY wasOnlineChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatusOffline)
public:
    explicit QxTdUserStatusOffline(QObject *parent = nullptr);
    QDateTime wasOnline() const;
    void unmarshalJson(const QJsonObject &json) override;
    QString toString() const override;
signals:
    void wasOnlineChanged(QDateTime wasOnline);

private:
    QDateTime m_wasOnline;
};

/**
 * @brief The QxTdUserStatusOnline class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_online.html
 */
class QxTdUserStatusOnline : public QxTdUserStatus
{
    Q_OBJECT
    Q_PROPERTY(QDateTime expires READ expires NOTIFY expiresChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatusOnline)
public:
    explicit QxTdUserStatusOnline(QObject *parent = nullptr);
    QDateTime expires() const;
    void unmarshalJson(const QJsonObject &json) override;
    QString toString() const override;
signals:
    void expiresChanged();

private:
    QDateTime m_expires;
};

/**
 * @brief The QxTdUserStatusRecently class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1user_status_recently.html
 */
class QxTdUserStatusRecently : public QxTdUserStatus
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserStatus and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserStatusRecently)
public:
    explicit QxTdUserStatusRecently(QObject *parent = nullptr);
    QString toString() const override;
};

#endif // QX_TD_USER_STATUS_H
