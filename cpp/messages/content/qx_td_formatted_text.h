#ifndef QX_TD_FORMATTED_TEXT_H
#define QX_TD_FORMATTED_TEXT_H

#include <QPointer>
#include "models/qx_td_object_list_model.h"
#include "qx_td_text_entity.h"

class QxTdFormattedText : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text NOTIFY textChanged)
    Q_PROPERTY(QString oneLineText READ oneLineText NOTIFY textChanged)
    Q_PROPERTY(QObject *entities READ qmlEntities NOTIFY entitiesChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdFormattedText cannot be created in QML.")
public:
    explicit QxTdFormattedText(QObject *parent = nullptr);

    QString text() const;
    QString oneLineText() const;

    QxTdObjectListModel<QxTdTextEntity> *entities() const;

    QObject *qmlEntities() const;

    void unmarshalJson(const QJsonObject &json) override;
signals:
    void textChanged();
    void entitiesChanged();

private:
    QString m_text;
    QString m_oneLineText;
    QPointer<QxTdObjectListModel<QxTdTextEntity>> m_entities;
};

#endif // QX_TD_FORMATTED_TEXT_H
