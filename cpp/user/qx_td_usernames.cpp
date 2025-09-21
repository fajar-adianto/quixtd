#include "qx_td_usernames.h"

#include <QJsonObject>
#include <QJsonArray>

QxTdUsernames::QxTdUsernames(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdUsernames::QxTdUsernames(QObject *parent, QList<QString> activeUsernames_, QList<QString> disabledUsernames_, QString editableUsername_)
    : QxTdObject(parent)
    , m_activeUsernames(activeUsernames_)
    , m_disabledUsernames(disabledUsernames_)
    , m_editableUsername(editableUsername_)
{
    // Intentionally left empty.
}

QList<QString> QxTdUsernames::activeUsernames() const {
    return m_activeUsernames;
}

void QxTdUsernames::setActiveUsernames(QList<QString> value) {
    if (m_activeUsernames != value) {
        m_activeUsernames = value;
        emit dataChanged();
    }
}

QList<QString> QxTdUsernames::disabledUsernames() const {
    return m_disabledUsernames;
}

void QxTdUsernames::setDisabledUsernames(QList<QString> value) {
    if (m_disabledUsernames != value) {
        m_disabledUsernames = value;
        emit dataChanged();
    }
}

QString QxTdUsernames::editableUsername() const {
    return m_editableUsername;
}

void QxTdUsernames::setEditableUsername(QString value) {
    if (m_editableUsername != value) {
        m_editableUsername = value;
        emit dataChanged();
    }
}

void QxTdUsernames::unmarshalJson(const QJsonObject &json) {
    QJsonObject jsonObj;
    QJsonArray jsonArray;

    QxTdObject::unmarshalJson(json);
    jsonArray = json["active_usernames"].toArray();
    for (const QJsonValue &jsonValue : jsonArray) {
        m_activeUsernames << jsonValue.toString();
    }
    jsonArray = json["disabled_usernames"].toArray();
    for (const QJsonValue &jsonValue : jsonArray) {
        m_disabledUsernames << jsonValue.toString();
    }
    m_editableUsername = json["editable_username"].toString();

    emit dataChanged();
}
