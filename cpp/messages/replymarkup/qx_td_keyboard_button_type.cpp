#include "qx_td_keyboard_button_type.h"

#include <QDebug>
#include "common/qx_td_object.h"

QxTdKeyboardButtonType::QxTdKeyboardButtonType(QObject *parent)
    : QxTdObject(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonTypeRequestLocation::QxTdKeyboardButtonTypeRequestLocation(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonTypeRequestPhoneNumber::QxTdKeyboardButtonTypeRequestPhoneNumber(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonTypeRequestPoll::QxTdKeyboardButtonTypeRequestPoll(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonTypeText::QxTdKeyboardButtonTypeText(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonTypeWebApp::QxTdKeyboardButtonTypeWebApp(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeBuy::QxTdInlineKeyboardButtonTypeBuy(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeCallback::QxTdInlineKeyboardButtonTypeCallback(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeCallbackGame::QxTdInlineKeyboardButtonTypeCallbackGame(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeCallbackWithPassword::QxTdInlineKeyboardButtonTypeCallbackWithPassword(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeLoginUrl::QxTdInlineKeyboardButtonTypeLoginUrl(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeSwitchinline::QxTdInlineKeyboardButtonTypeSwitchinline(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeUrl::QxTdInlineKeyboardButtonTypeUrl(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeUser::QxTdInlineKeyboardButtonTypeUser(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdInlineKeyboardButtonTypeWebApp::QxTdInlineKeyboardButtonTypeWebApp(QObject *parent)
    : QxTdKeyboardButtonType(parent)
{
    // Intentionally left empty.
}

QxTdKeyboardButtonType *QxTdKeyboardButtonTypeFactory::create(const QJsonObject &data, QObject *parent)
{
    const QString type = data["@type"].toString();
    QxTdKeyboardButtonType *result = nullptr;

    if (type == "keyboardButtonTypeRequestLocation") {
        result = new QxTdKeyboardButtonTypeRequestLocation(parent);
    } else if (type == "keyboardButtonTypeRequestPhoneNumber") {
        result = new QxTdKeyboardButtonTypeRequestPhoneNumber(parent);
    } else if (type == "keyboardButtonTypeRequestPoll") {
        result = new QxTdKeyboardButtonTypeRequestPoll(parent);
    } else if (type == "keyboardButtonTypeText") {
        result = new QxTdKeyboardButtonTypeText(parent);
    } else if (type == "keyboardButtonTypeWebApp") {
        result = new QxTdKeyboardButtonTypeWebApp(parent);
    } else if (type == "inlineKeyboardButtonTypeBuy") {
        result = new QxTdInlineKeyboardButtonTypeBuy(parent);
    } else if (type == "inlineKeyboardButtonTypeCallback") {
        result = new QxTdInlineKeyboardButtonTypeCallback(parent);
    } else if (type == "inlineKeyboardButtonTypeCallbackGame") {
        result = new QxTdInlineKeyboardButtonTypeCallbackGame(parent);
    } else if (type == "inlineKeyboardButtonTypeCallbackWithPassword") {
        result = new QxTdInlineKeyboardButtonTypeCallbackWithPassword(parent);
    } else if (type == "inlineKeyboardButtonTypeLoginUrl") {
        result = new QxTdInlineKeyboardButtonTypeLoginUrl(parent);
    } else if (type == "inlineKeyboardButtonTypeSwitchinline") {
        result = new QxTdInlineKeyboardButtonTypeSwitchinline(parent);
    } else if (type == "inlineKeyboardButtonTypeUrl") {
        result = new QxTdInlineKeyboardButtonTypeUrl(parent);
    } else if (type == "inlineKeyboardButtonTypeUser") {
        result = new QxTdInlineKeyboardButtonTypeUser(parent);
    } else if (type == "inlineKeyboardButtonTypeWebApp") {
        result = new QxTdInlineKeyboardButtonTypeWebApp(parent);
    } else {
        qWarning() << "Unknown keyboard button type:" << type;
    }

    if (result) {
        result->unmarshalJson(data);
    }

    return result;
}
