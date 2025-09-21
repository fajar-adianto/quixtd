#include "qx_td_photo.h"

QxTdPhoto::QxTdPhoto(QObject *parent)
    : QxTdObject(parent)
    , m_small(new QxTdFile)
    , m_big(new QxTdFile)
{
    // Intentionally left empty.
}

QxTdFile *QxTdPhoto::small() const
{
    return m_small.data();
}

QxTdFile *QxTdPhoto::big() const
{
    return m_big.data();
}

QString QxTdPhoto::smallPhotoPath() {
    if (m_small && !m_small->local()->path().isEmpty()) {
        return "image://photo/" + m_small->local()->path();
    }
    return "";
}

void QxTdPhoto::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    if (!json.isEmpty()) {
        m_small->unmarshalJson(json["small"].toObject());
        emit smallChanged(m_small.data());
        m_big->unmarshalJson(json["big"].toObject());
        emit bigChanged(m_big.data());
    }

}
