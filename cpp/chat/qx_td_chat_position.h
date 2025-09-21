#ifndef QX_TD_CHAT_POSITION_H
#define QX_TD_CHAT_POSITION_H

#include <QPointer>
#include "qx_td_chat_list.h"
#include "common/qx_abstract_int64_id.h"

class QxTdChatPosition : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdChatPosition)

    Q_PROPERTY(QObject *list READ list NOTIFY listChanged)
    Q_PROPERTY(QString order READ qmlOrder NOTIFY orderChanged)
    Q_PROPERTY(bool isPinned READ isPinned NOTIFY isPinnedChanged)
    // Q_PROPERTY(QString source READ source NOTIFY sourceChanged)
    QML_ELEMENT
public:
    explicit QxTdChatPosition(QObject *parent = nullptr);
    void unmarshalJson(const QJsonObject &json) override;

    QxTdChatList *list() const;
    QString qmlOrder() const;
    qint64 order() const;
    bool isPinned() const;
    // QxTdChatSource *source() const;

signals:
    void listChanged();
    void orderChanged();
    void isPinnedChanged();
    void sourceChanged();

private:
    QScopedPointer<QxTdChatList> m_list;
    QxTdInt64 m_order;
    bool m_isPinned;
    // QPointer<QxTdChatSource> m_source
};

#endif // QX_TD_CHAT_POSITION_H
