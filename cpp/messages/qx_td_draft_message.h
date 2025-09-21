#ifndef QX_TD_DRAFT_MESSAGE_H
#define QX_TD_DRAFT_MESSAGE_H

#include <QScopedPointer>
#include "requests/content/qx_td_input_message_text.h"
#include "common/qx_td_int.h"

/**
 * @brief The QxTdDraftMessage class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1draft_message.html
 */
class QxTdDraftMessage : public QxTdObject
{
    Q_OBJECT
    Q_DISABLE_COPY(QxTdDraftMessage)
    Q_PROPERTY(QString replyToMessageId READ qmlReplyToMessageId NOTIFY replyToMessageIdChanged)
    Q_PROPERTY(QxTdInputMessageText *inputMessageText READ inputMessageText NOTIFY inputMessageTextChanged)
    QML_ELEMENT
public:
    explicit QxTdDraftMessage(QObject *parent = nullptr);

    QString qmlReplyToMessageId() const;
    qint64 replyToMessageId() const;
    QxTdInputMessageText *inputMessageText() const;
    void unmarshalJson(const QJsonObject &json) override;
    void setReplyToMessageId(const qint64 &replyToMessageId);
    void setInputMessageText(QxTdInputMessageText *inputMessageText);
    QJsonObject marshalJson() override;

signals:
    void replyToMessageIdChanged();
    void inputMessageTextChanged();

private:
    QxTdInt64 m_replyToMessageId;
    QScopedPointer<QxTdInputMessageText> m_inputMessageText;
};

#endif // QX_TD_DRAFT_MESSAGE_H
