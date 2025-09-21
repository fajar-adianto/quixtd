#ifndef QX_TD_SECRET_CHAT_H
#define QX_TD_SECRET_CHAT_H

#include <QObject>
#include <QPointer>
#include <QColor>
#include "qx_td_chat.h"
#include "qx_td_secret_chat_state.h"

class QxTdHashPixel : public QxTdObject
{
   Q_OBJECT
   Q_DISABLE_COPY(QxTdHashPixel)
   Q_PROPERTY(QColor hashPixelColor READ hashPixelColor NOTIFY hashPixelChanged)
   QML_ELEMENT
public:
   explicit QxTdHashPixel(QObject *parent = nullptr);
   QColor hashPixelColor() const;
   void setHashPixelColor(QColor hashPixelColor);
signals:
   void hashPixelChanged();

private:
   QColor m_hashPixelColor;
};

class QxTdHashRow : public QxTdObject
{
   Q_OBJECT
   Q_DISABLE_COPY(QxTdHashRow)
   Q_PROPERTY(QObject *hashRow READ hashRow NOTIFY hashRowChanged)
   QML_ELEMENT
public:
   explicit QxTdHashRow(QObject *parent = nullptr);
   QObject *hashRow() const;
   void setRow(QByteArray stringRow) const;
signals:
   void hashRowChanged();

private:
   QPointer<QxTdObjectListModel<QxTdHashPixel>> m_hashRow;
};


class QxTdSecretChat : public QxTdChat
{
    Q_OBJECT
    Q_PROPERTY(QString secretChatId READ qmlSecretChatId NOTIFY secretChatChanged)
    Q_PROPERTY(QString userId READ qmlUserId NOTIFY secretChatChanged)
    Q_PROPERTY(QxTdSecretChatState *state READ state NOTIFY stateChanged)
    Q_PROPERTY(bool isOutbound READ isOutbound NOTIFY secretChatChanged)
    Q_PROPERTY(qint32 ttl READ ttl NOTIFY secretChatChanged)
    Q_PROPERTY(QString keyHashString READ keyHashString NOTIFY secretChatChanged)
    Q_PROPERTY(QObject *keyHashMap READ keyHashMap NOTIFY secretChatChanged)
    Q_PROPERTY(qint32 layer READ layer NOTIFY secretChatChanged)
    Q_PROPERTY(bool isPending READ isPending NOTIFY stateChanged)
    Q_PROPERTY(bool isClosed READ isClosed NOTIFY stateChanged)
    QML_ELEMENT
public:
    explicit QxTdSecretChat(QObject *parent = nullptr);

    QString qmlSecretChatId() const;
    qint64 secretChatId() const;
    QString qmlUserId() const;
    qint64 userId() const;
    bool isOutbound() const;
    bool isWritable() const override;
    bool isPending() const;
    bool isClosed() const;
    qint32 ttl() const;
    QString keyHashString() const;
    QObject *keyHashMap() const;
    qint32 layer() const;

    QxTdSecretChatState *state() const;

    void getSecretChatData();

signals:
    void secretChatChanged();
    void stateChanged(QxTdSecretChatState *state);

private:
    virtual void onChatOpened() override;

private slots:
    void updateSecretChat(const QJsonObject &data);

private:
    QxTdInt64 m_secretChatId;
    QxTdInt64 m_userId;
    bool m_isOutbound;
    qint32 m_ttl;
    QByteArray m_keyHash;
    QPointer<QxTdObjectListModel<QxTdHashRow>> m_hashMap;
    qint32 m_layer;
    QPointer<QxTdSecretChatState> m_state;
};

#endif // QX_TD_SECRET_CHAT_H
