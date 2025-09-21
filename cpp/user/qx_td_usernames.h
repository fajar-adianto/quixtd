#ifndef QX_TD_USERNAMES_H
#define QX_TD_USERNAMES_H

#include <QList>
#include "common/qx_td_object.h"

class QxTdUsernames : public QxTdObject {
    Q_OBJECT
    Q_PROPERTY(QList<QString> activeUsernames READ activeUsernames WRITE setActiveUsernames NOTIFY dataChanged)
    Q_PROPERTY(QList<QString> disabledUsernames READ disabledUsernames WRITE setDisabledUsernames NOTIFY dataChanged)
    Q_PROPERTY(QString editableUsername READ editableUsername WRITE setEditableUsername NOTIFY dataChanged)

public:
    explicit QxTdUsernames(QObject *parent = nullptr);
    explicit QxTdUsernames(QObject *parent, QList<QString> activeUsernames_, QList<QString> disabledUsernames_, QString editableUsername_);

    QList<QString> activeUsernames() const;
    void setActiveUsernames(QList<QString> value);
    QList<QString> disabledUsernames() const;
    void setDisabledUsernames(QList<QString> value);
    QString editableUsername() const;
    void setEditableUsername(QString value);

    void unmarshalJson(const QJsonObject &json) override;

private:
    Q_DISABLE_COPY(QxTdUsernames)
    QList<QString> m_activeUsernames;
    QList<QString> m_disabledUsernames;
    QString m_editableUsername;

signals:
    void dataChanged();

};

#endif // QX_TD_USERNAMES_H
