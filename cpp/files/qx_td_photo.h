#ifndef QX_TD_PHOTO_H
#define QX_TD_PHOTO_H

#include "qx_td_file.h"

class QxTdPhoto : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QxTdFile *small READ small NOTIFY smallChanged)
    Q_PROPERTY(QxTdFile *big READ big NOTIFY bigChanged)
    Q_PROPERTY(QString smallPhotoPath READ smallPhotoPath NOTIFY smallChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdPhoto cannot be created in QML.")
public:
    explicit QxTdPhoto(QObject *parent = nullptr);

    /**
     * @brief A small (160x160) user profile photo
     */
    QxTdFile *small() const;
    /**
     * @brief A big (640x640) user profile photo
     */
    QxTdFile *big() const;

    void unmarshalJson(const QJsonObject &json) override;

    QString smallPhotoPath();

signals:
    void smallChanged(QxTdFile *small);
    void bigChanged(QxTdFile *big);

private:
    QScopedPointer<QxTdFile> m_small;
    QScopedPointer<QxTdFile> m_big;
};

#endif // QX_TD_PHOTO_H
