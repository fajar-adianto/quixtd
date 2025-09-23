#ifndef QX_TD_MESSAGE_DOCUMENT_H
#define QX_TD_MESSAGE_DOCUMENT_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_document.h"
#include "qx_td_formatted_text.h"

class QxTdMessageDocument : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdDocument *document READ document NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageDocument cannot be created in QML.")
public:
    explicit QxTdMessageDocument(QObject *parent = nullptr);

    QxTdDocument *document() const;
    QxTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageDocument)
    std::unique_ptr<QxTdDocument> m_document;
    std::unique_ptr<QxTdFormattedText> m_caption;
};

#endif // QX_TD_MESSAGE_DOCUMENT_H
