#ifndef QX_TD_REPLY_MARKUP_H
#define QX_TD_REPLY_MARKUP_H

#include <QPointer>
#include "qx_td_keyboard_button.h"

/**
 * @brief The QxTdReplyMarkup class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_reply_markup.html
 */
class QxTdReplyMarkup : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdReplyMarkup)
public:
    explicit QxTdReplyMarkup(QObject *parent = nullptr);

};

/**
 * @brief The QxTdReplyMarkupForceReply class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_force_reply.html
 */
class QxTdReplyMarkupForceReply : public QxTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY isPersonalChanged)
    QML_ELEMENT
public:
    explicit QxTdReplyMarkupForceReply(QObject *parent = nullptr);
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void isPersonalChanged();

private:
    bool m_isPersonal;
};

/**
 * @brief The QxTdReplyMarkupInlineKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_inline_keyboard.html
 */
class QxTdReplyMarkupInlineKeyboard : public QxTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(QObject *rows READ rows NOTIFY rowsChanged)
    QML_ELEMENT
public:
    explicit QxTdReplyMarkupInlineKeyboard(QObject *parent = nullptr);
    QObject *rows();

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void rowsChanged();

private:
    QPointer<QxTdObjectListModel<QxTdKeyboardRow>> m_rows;
};

/**
 * @brief The QxTdReplyMarkupRemoveKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_remove_keyboard.html
 */
class QxTdReplyMarkupRemoveKeyboard : public QxTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY isPersonalChanged)
    QML_ELEMENT
public:
    explicit QxTdReplyMarkupRemoveKeyboard(QObject *parent = nullptr);
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void isPersonalChanged();

private:
    bool m_isPersonal;
};

/**
 * @brief The QxTdReplyMarkupShowKeyboard class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1reply_markup_show_keyboard.html
 */
class QxTdReplyMarkupShowKeyboard : public QxTdReplyMarkup
{
    Q_OBJECT
    Q_PROPERTY(QObject *rows READ rows NOTIFY markupChanged)
    Q_PROPERTY(bool resizeKeyboard READ resizeKeyboard NOTIFY markupChanged)
    Q_PROPERTY(bool oneTime READ oneTime NOTIFY markupChanged)
    Q_PROPERTY(bool isPersonal READ isPersonal NOTIFY markupChanged)
    QML_ELEMENT
public:
    explicit QxTdReplyMarkupShowKeyboard(QObject *parent = nullptr);

    QObject *rows() const;
    bool resizeKeyboard() const;
    bool oneTime() const;
    bool isPersonal() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void markupChanged();

private:
    QPointer<QxTdObjectListModel<QxTdKeyboardRow>> m_rows;
    bool m_resizeKeyboard;
    bool m_oneTime;
    bool m_isPersonal;
};

struct QxTdReplyMarkupFactory
{
    static QxTdReplyMarkup *create(const QJsonObject &data, QObject *parent);
};
#endif // QX_TD_REPLY_MARKUP_H
