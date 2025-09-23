#include "common/qx_td_object.h"
#include "qx_td_keyboard_button.h"

QxTdKeyboardButton::QxTdKeyboardButton(QObject *parent)
    : QxTdObject(parent)
    , m_type(nullptr)
{
    // Intentionally left empty.
}

QString QxTdKeyboardButton::text() const
{
    return m_text;
}

void QxTdKeyboardButton::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_text = json["text"].toString();
    m_type.reset(QxTdKeyboardButtonTypeFactory::create(json["type"].toObject(), this));
}

QxTdKeyboardButtonType *QxTdKeyboardButton::type() const
{
    return m_type.get();
}

QxTdKeyboardRow::QxTdKeyboardRow(QObject *parent)
    : QxTdObject(parent)
{
    m_row.reset(new QxTdObjectListModel<QxTdKeyboardButton>(this));
}

QObject *QxTdKeyboardRow::row() const
{
    return m_row.get();
}

void QxTdKeyboardRow::unmarshalJson(const QJsonValue &json)
{
    const QJsonArray row = json.toArray();
    for (const QJsonValue &v : row) {
        QxTdKeyboardButton *button = new QxTdKeyboardButton;
        button->unmarshalJson(v.toObject());
        m_row->append(button);
    }
}
