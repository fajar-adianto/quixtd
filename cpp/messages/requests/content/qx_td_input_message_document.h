#ifndef QX_TD_INPUT_MESSAGE_DOCUMENT_H
#define QX_TD_INPUT_MESSAGE_DOCUMENT_H

#include "../qx_td_input_message_content_attachment_caption.h"

class QxTdInputMessageDocument : public QxTdInputMessageContentAttachmentCaption
{
    Q_OBJECT

public:
    explicit QxTdInputMessageDocument(QObject *parent = nullptr);
    QJsonObject marshalJson();
    void setAttachmentPath(const QString &url);
    void setCaption(const QString &text);
    void setCaptionEntities(const QJsonArray &entities);

private:
    Q_DISABLE_COPY(QxTdInputMessageDocument)
    QString m_document;
    QString m_caption;
    QJsonArray m_captionEntities;
};

#endif // QX_TD_INPUT_MESSAGE_DOCUMENT_H
