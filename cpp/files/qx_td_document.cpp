#include "qx_td_document.h"

QxTdDocument::QxTdDocument(QObject *parent)
    : QxTdObject(parent)
    , m_thumbnail(new QxTdThumbnail)
    , m_document(new QxTdFile)
{
    setType(DOCUMENT);
}

QString QxTdDocument::fileName() const
{
    return m_fileName;
}

QString QxTdDocument::mimeType() const
{
    return m_mimeType;
}

QxTdThumbnail *QxTdDocument::thumbnail() const
{
    return m_thumbnail.data();
}

QxTdFile *QxTdDocument::document() const
{
    return m_document.data();
}

void QxTdDocument::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    m_fileName = json["file_name"].toString();
    m_mimeType = json["mime_type"].toString();
    if (json.contains("thumbnail")) {
        m_thumbnail->unmarshalJson(json["thumbnail"].toObject());
    }
    m_document->unmarshalJson(json["document"].toObject());
    emit documentChanged();
}
