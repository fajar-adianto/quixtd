#include "qx_td_reply_markup.h"

#include <QJsonValue>

QxTdReplyMarkup::QxTdReplyMarkup(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdReplyMarkupForceReply::QxTdReplyMarkupForceReply(QObject *parent)
    : QxTdReplyMarkup(parent)
    , m_isPersonal(false)
{
    setType(REPLY_MARKUP_FORCE_REPLY);
}

bool QxTdReplyMarkupForceReply::isPersonal() const
{
    return m_isPersonal;
}

void QxTdReplyMarkupForceReply::unmarshalJson(const QJsonObject &json)
{
    QxTdReplyMarkup::unmarshalJson(json);
    m_isPersonal = json["is_personal"].toBool();
    emit isPersonalChanged();
}

QxTdReplyMarkupInlineKeyboard::QxTdReplyMarkupInlineKeyboard(QObject *parent)
    : QxTdReplyMarkup(parent)
    , m_rows(nullptr)
{
    setType(REPLY_MARKUP_INLINE_KEYBOARD);
    m_rows = new QxTdObjectListModel<QxTdKeyboardRow>(this);
}

QObject *QxTdReplyMarkupInlineKeyboard::rows()
{
    return m_rows;
}

void QxTdReplyMarkupInlineKeyboard::unmarshalJson(const QJsonObject &json)
{
    QxTdReplyMarkup::unmarshalJson(json);
    const QJsonArray rows = json["rows"].toArray();
    for (const QJsonValue &item : rows) {
        QxTdKeyboardRow *keyboardRow = new QxTdKeyboardRow;
        keyboardRow->unmarshalJson(item);
        m_rows->append(keyboardRow);
    }
    emit rowsChanged();
}

QxTdReplyMarkupRemoveKeyboard::QxTdReplyMarkupRemoveKeyboard(QObject *parent)
    : QxTdReplyMarkup(parent)
    , m_isPersonal(false)
{
    setType(REPLY_MARKUP_REMOVE_KEYBOARD);
}

bool QxTdReplyMarkupRemoveKeyboard::isPersonal() const
{
    return m_isPersonal;
}

void QxTdReplyMarkupRemoveKeyboard::unmarshalJson(const QJsonObject &json)
{
    QxTdReplyMarkup::unmarshalJson(json);
    m_isPersonal = json["is_personal"].toBool();
    emit isPersonalChanged();
}

QxTdReplyMarkupShowKeyboard::QxTdReplyMarkupShowKeyboard(QObject *parent)
    : QxTdReplyMarkup(parent)
    , m_rows(nullptr)
    , m_resizeKeyboard(false)
    , m_oneTime(false)
    , m_isPersonal(false)
{
    setType(REPLY_MARKUP_SHOW_KEYBOARD);
    m_rows = new QxTdObjectListModel<QxTdKeyboardRow>(this);
}
QObject *QxTdReplyMarkupShowKeyboard::rows() const
{
    return m_rows;
}

bool QxTdReplyMarkupShowKeyboard::resizeKeyboard() const
{
    return m_resizeKeyboard;
}

bool QxTdReplyMarkupShowKeyboard::oneTime() const
{
    return m_oneTime;
}

bool QxTdReplyMarkupShowKeyboard::isPersonal() const
{
    return m_isPersonal;
}

void QxTdReplyMarkupShowKeyboard::unmarshalJson(const QJsonObject &json)
{
    QxTdReplyMarkup::unmarshalJson(json);
    const QJsonArray rows = json["rows"].toArray();
    for (const auto &item : rows) {
        QxTdKeyboardRow *keyboardRow = new QxTdKeyboardRow;
        keyboardRow->unmarshalJson(item);
        m_rows->append(keyboardRow);
    }
    m_resizeKeyboard = json["resize_keyboard"].toBool();
    m_oneTime = json["one_time"].toBool();
    m_isPersonal = json["is_personal"].toBool();
    emit markupChanged();
}

QxTdReplyMarkup *QxTdReplyMarkupFactory::create(const QJsonObject &data, QObject *parent)
{
    const QString type = data["@type"].toString();

    QxTdReplyMarkup *result = nullptr;
    if (type == "replyMarkupForceReply") {
        result = new QxTdReplyMarkupForceReply(parent);
    } else if (type == "replyMarkupInlineKeyboard") {
        result = new QxTdReplyMarkupInlineKeyboard(parent);
    } else if (type == "replyMarkupRemoveKeyboard") {
        result = new QxTdReplyMarkupRemoveKeyboard(parent);
    } else if (type == "replyMarkupShowKeyboard") {
        result = new QxTdReplyMarkupShowKeyboard(parent);
    } else {
        qWarning() << "Unknown reply markup type: " << type;
    }

    if (result) {
        result->unmarshalJson(data);
    }

    return result;
}
