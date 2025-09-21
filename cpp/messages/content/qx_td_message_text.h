#ifndef QX_TD_MESSAGE_TEXT_H
#define QX_TD_MESSAGE_TEXT_H

#include "messages/qx_td_message_content.h"
#include "qx_td_formatted_text.h"
#include "qx_td_web_page.h"

class QxTdMessageText : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdFormattedText *text READ text NOTIFY dataChanged)
    Q_PROPERTY(QxTdWebPage *webPage READ webPage NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageText cannot be created in QML.")
public:
    explicit QxTdMessageText(QObject *parent = nullptr);

    QxTdFormattedText *text() const;
    QxTdWebPage *webPage() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageText)
    QScopedPointer<QxTdFormattedText> m_text;
    QScopedPointer<QxTdWebPage> m_webPage;
    bool m_hasWebPage;
};

#endif // QX_TD_MESSAGE_TEXT_H
