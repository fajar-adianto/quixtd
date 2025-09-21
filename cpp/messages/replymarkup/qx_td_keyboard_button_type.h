#ifndef QX_TD_KEYBOARD_BUTTON_TYPE_H
#define QX_TD_KEYBOARD_BUTTON_TYPE_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdKeyboardButtonType class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_keyboard_button_type.html
 */
class QxTdKeyboardButtonType : public QxTdObject
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonType(QObject *parent = nullptr);
};

/**
 * @brief The QxTdKeyboardButtonTypeRequestLocation class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_location.html
 */
class QxTdKeyboardButtonTypeRequestLocation : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonTypeRequestLocation(QObject *parent = nullptr);
};

/**
 * @brief The QxTdKeyboardButtonTypeRequestPhoneNumber class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_phone_number.html
 */
class QxTdKeyboardButtonTypeRequestPhoneNumber : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonTypeRequestPhoneNumber(QObject *parent = nullptr);
};

/**
 * @brief The QxTdKeyboardButtonTypeRequestPoll class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_request_poll.html
 */
class QxTdKeyboardButtonTypeRequestPoll : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonTypeRequestPoll(QObject *parent = nullptr);
};

/**
 * @brief The QxTdKeyboardButtonTypeText class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button_type_text.html
 */
class QxTdKeyboardButtonTypeText : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonTypeText(QObject *parent = nullptr);
};

class QxTdKeyboardButtonTypeWebApp: public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdKeyboardButtonTypeWebApp(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeBuy : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeBuy(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeCallback : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeCallback(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeCallbackGame : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeCallbackGame(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeCallbackWithPassword : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeCallbackWithPassword(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeLoginUrl : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeLoginUrl(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeSwitchinline : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeSwitchinline(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeUrl : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeUrl(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeUser : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeUser(QObject *parent = nullptr);
};

class QxTdInlineKeyboardButtonTypeWebApp : public QxTdKeyboardButtonType
{
    Q_OBJECT
public:
    explicit QxTdInlineKeyboardButtonTypeWebApp(QObject *parent = nullptr);
};


struct QxTdKeyboardButtonTypeFactory
{
    static QxTdKeyboardButtonType *create(const QJsonObject &data, QObject *parent);
};

#endif // QX_TD_KEYBOARD_BUTTON_TYPE_H
