#ifndef QX_TD_KEYBOARD_BUTTON_H
#define QX_TD_KEYBOARD_BUTTON_H

#include <QScopedPointer>
#include <QJsonArray>

#include "qx_td_keyboard_button_type.h"
#include "models/qx_td_object_list_model.h"

/**
 * @brief The QxTdKeyboardButton class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1keyboard_button.html
 */
class QxTdKeyboardButton : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdKeyboardButton)
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(QxTdKeyboardButtonType *type READ type NOTIFY typeChanged)
    QML_ELEMENT
public:
    explicit QxTdKeyboardButton(QObject *parent = nullptr);

    QString text() const;
    QxTdKeyboardButtonType *type() const;
    void unmarshalJson(const QJsonObject &json) override;

signals:
    void textChanged();
    void typeChanged();

private:
    QString m_text;
    QScopedPointer<QxTdKeyboardButtonType> m_type;
};

/**
 * @brief The QxTdKeyboardRow class
 *
 * not present in telegram docs, to abstact easier the array of array of (pointers to) QxTdKeyboardButton
 */
class QxTdKeyboardRow : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdKeyboardRow)
    Q_PROPERTY(QObject *row READ row NOTIFY rowChanged)
    QML_ELEMENT
public:
    explicit QxTdKeyboardRow(QObject *parent = nullptr);
    QObject *row() const;
    void unmarshalJson(const QJsonValue &json);

signals:
    void rowChanged();

private:
    QScopedPointer<QxTdObjectListModel<QxTdKeyboardButton>> m_row;
};

#endif // QX_TD_KEYBOARD_BUTTON_H
