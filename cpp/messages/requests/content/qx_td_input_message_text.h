#ifndef QX_TD_INPUT_MESSAGE_TEXT_H
#define QX_TD_INPUT_MESSAGE_TEXT_H

#include <QString>
#include "../qx_td_input_message_content.h"

class QxTdInputMessageText : public QxTdInputMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY inputMessageTextChanged)
    Q_PROPERTY(bool clearDraft READ clearDraft NOTIFY inputMessageTextChanged)
    Q_PROPERTY(bool disableWebPagePreview READ disableWebPagePreview NOTIFY inputMessageTextChanged)
    // Q_DISABLE_COPY(QxTdInputMessageText)
    // QxTdFormattedText m_text; <- TODO: that's the way to go
    QString m_text;
    QJsonArray m_entities;
    bool m_disable_web_page_preview;
    bool m_clear_draft;

public:
    explicit QxTdInputMessageText(QObject *parent = nullptr);
    QJsonObject marshalJson() override;
    void setText(const QString &text);
    void setClearDraft(const bool clear_draft);
    void setEntities(const QJsonArray &entities);
    void unmarshalJson(const QJsonObject &json) override;
    QString text() const;
    bool clearDraft() const;
    bool disableWebPagePreview() const;

private:
    Q_DISABLE_COPY(QxTdInputMessageText)

signals:
    void inputMessageTextChanged();
};

#endif // QX_TD_INPUT_MESSAGE_TEXT_H
