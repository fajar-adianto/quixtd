#ifndef QX_TD_USER_TYPE_H
#define QX_TD_USER_TYPE_H

#include "common/qx_td_object.h"

class QxTdUserType : public QxTdObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserType and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserType)
public:
    explicit QxTdUserType(QObject *parent = nullptr);

    virtual void unmarshalJson(const QJsonObject &json) override;
};

class QxTdUserTypeBot : public QxTdUserType
{
    Q_OBJECT
    Q_PROPERTY(bool canJoinGroups READ canJoinGroups NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool canReadAllGroupMessages READ canReadAllGroupMessages NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool isInline READ isInline NOTIFY userTypeDataChanged)
    Q_PROPERTY(QString inlineQueryPlaceholder READ placeholder NOTIFY userTypeDataChanged)
    Q_PROPERTY(bool needLocation READ needLocation NOTIFY userTypeDataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserType and its derived classes cannot be created in QML.")
public:
    explicit QxTdUserTypeBot(QObject *parent = nullptr);
    bool canJoinGroups() const;
    bool canReadAllGroupMessages() const;
    bool isInline() const;
    QString placeholder() const;
    bool needLocation() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void userTypeDataChanged();

private:
    Q_DISABLE_COPY(QxTdUserTypeBot)
    bool m_canJoinGroups;
    bool m_canReadAllGroupMessages;
    bool m_isInline;
    QString m_inlineQueryPlaceholder;
    bool m_needLocation;
};

class QxTdUserTypeDeleted : public QxTdUserType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserType and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserTypeDeleted)
public:
    explicit QxTdUserTypeDeleted(QObject *parent = nullptr);
};

class QxTdUserTypeRegular : public QxTdUserType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserType and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserTypeRegular)
public:
    explicit QxTdUserTypeRegular(QObject *parent = nullptr);
};

class QxTdUserTypeUnknown : public QxTdUserType
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdUserType and its derived classes cannot be created in QML.")
    Q_DISABLE_COPY(QxTdUserTypeUnknown)
public:
    explicit QxTdUserTypeUnknown(QObject *parent = nullptr);
};
#endif // QX_TD_USER_TYPE_H
