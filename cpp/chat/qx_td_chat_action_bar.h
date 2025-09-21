#ifndef QX_TD_CHAT_ACTION_BAR_H
#define QX_TD_CHAT_ACTION_BAR_H

#include "common/qx_td_object.h"

class QxTdChatActionBar : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionBar)

public:
    explicit QxTdChatActionBar(QObject *parent = nullptr);

};

class QxTdChatActionBarAddContact : public QxTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionBarAddContact)

public:
    explicit QxTdChatActionBarAddContact(QObject *parent = nullptr);
};

class QxTdChatActionBarInviteMembers : public QxTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionBarInviteMembers)

public:
    explicit QxTdChatActionBarInviteMembers(QObject *parent = nullptr);
};

class QxTdChatActionBarJoinRequest : public QxTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title)
    Q_PROPERTY(bool isChannel READ isChannel)
    Q_PROPERTY(qint32 requestDate READ requestDate)
    QML_ELEMENT
    Q_DISABLE_COPY(QxTdChatActionBarJoinRequest)

public:
    explicit QxTdChatActionBarJoinRequest(QObject *parent = nullptr);

    QString title();
    bool isChannel();
    qint32 requestDate();

    void unmarshalJson(const QJsonObject &json) override;

private:
    QString m_title;
    bool m_isChannel;
    qint32 m_requestDate;
};

class QxTdChatActionBarReportAddBlock : public QxTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(bool canUnarchive READ canUnarchive)
    Q_PROPERTY(qint32 distance READ distance)
    QML_ELEMENT
    Q_DISABLE_COPY(QxTdChatActionBarReportAddBlock)

public:
    explicit QxTdChatActionBarReportAddBlock(QObject *parent = nullptr);

    bool canUnarchive();
    qint32 distance();

    void unmarshalJson(const QJsonObject &json) override;

private:
    bool m_canUnarchive;
    qint32 m_distance;
};

class QxTdChatActionBarReportSpam : public QxTdChatActionBar
{
    Q_OBJECT
    Q_PROPERTY(bool canUnarchive READ canUnarchive)
    QML_ELEMENT
    Q_DISABLE_COPY(QxTdChatActionBarReportSpam)

public:
    explicit QxTdChatActionBarReportSpam(QObject *parent = nullptr);

    bool canUnarchive();

    void unmarshalJson(const QJsonObject &json) override;

private:
    bool m_canUnarchive;
};

class QxTdChatActionBarReportUnrelatedLocation : public QxTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionBarReportUnrelatedLocation)

public:
    explicit QxTdChatActionBarReportUnrelatedLocation(QObject *parent = nullptr);
};

class QxTdChatActionBarSharePhoneNumber : public QxTdChatActionBar
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatActionBarSharePhoneNumber)

public:
    explicit QxTdChatActionBarSharePhoneNumber(QObject *parent = nullptr);
};

struct QxTdChatActionBarFactory
{
    static QxTdChatActionBar *create(const QJsonObject &json, QObject *parent = nullptr);
};
#endif // QX_TD_CHAT_ACTION_BAR_H
