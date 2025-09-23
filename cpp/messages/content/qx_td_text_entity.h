#ifndef QX_TD_TEXT_ENTITY_H
#define QX_TD_TEXT_ENTITY_H

#include "qx_td_text_entity_type.h"

class QxTdTextEntity : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(qint32 offset READ offset NOTIFY entityChanged)
    Q_PROPERTY(qint32 length READ length NOTIFY entityChanged)
    Q_PROPERTY(QxTdTextEntityType *entityType READ entityType NOTIFY entityChanged)
    QML_ELEMENT
public:
    explicit QxTdTextEntity(QObject *parent = nullptr);

    qint32 offset() const;

    qint32 length() const;

    QxTdTextEntityType *entityType() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void entityChanged();

private:
    Q_DISABLE_COPY(QxTdTextEntity)
    qint32 m_offset;
    qint32 m_length;
    std::unique_ptr<QxTdTextEntityType> m_type;
};

#endif // QX_TD_TEXT_ENTITY_H
