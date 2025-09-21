#ifndef QX_TD_DOCUMENT_H
#define QX_TD_DOCUMENT_H

#include "qx_td_thumbnail.h"

class QxTdDocument : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName NOTIFY documentChanged)
    Q_PROPERTY(QString mimeType READ mimeType NOTIFY documentChanged)
    Q_PROPERTY(QxTdThumbnail *thumbnail READ thumbnail NOTIFY documentChanged)
    Q_PROPERTY(QxTdFile *document READ document NOTIFY documentChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdDocument cannot be created in QML.")
public:
    explicit QxTdDocument(QObject *parent = nullptr);

    QString fileName() const;

    QString mimeType() const;

    QxTdThumbnail *thumbnail() const;

    QxTdFile *document() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void documentChanged();

private:
    Q_DISABLE_COPY(QxTdDocument)
    QString m_fileName;
    QString m_mimeType;
    QScopedPointer<QxTdThumbnail> m_thumbnail;
    QScopedPointer<QxTdFile> m_document;
};

#endif // QX_TD_DOCUMENT_H
