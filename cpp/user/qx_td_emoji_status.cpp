#include "qx_td_emoji_status.h"

#include <QJsonObject>
#include <QJsonArray>

QxTdEmojiStatus::QxTdEmojiStatus(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdEmojiStatus::QxTdEmojiStatus(QObject *parent, qint64 customEmojiId_)
    :         m_customEmojiId(customEmojiId_) {
}

qint64 QxTdEmojiStatus::customEmojiId() const {
    return m_customEmojiId;
}

void QxTdEmojiStatus::setCustomEmojiId(qint64 value) {
    if (m_customEmojiId != value) {
        m_customEmojiId = value;
        emit dataChanged();
    }
}

QJsonObject QxTdEmojiStatus::marshalJson() {
    return QJsonObject{
        { "@type", QxTdObject::typeString() },
        { "custom_emoji_id", m_customEmojiId }
    };
}

void QxTdEmojiStatus::unmarshalJson(const QJsonObject &json) {
    QJsonObject jsonObj;
    QJsonArray jsonArray;

    QxTdObject::unmarshalJson(json);
    m_customEmojiId = json["custom_emoji_id"].toVariant().toLongLong();

    emit dataChanged();
}
