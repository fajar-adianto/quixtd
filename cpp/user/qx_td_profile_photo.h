#ifndef QX_TD_PROFILE_PHOTO_H
#define QX_TD_PROFILE_PHOTO_H

#include "files/qx_td_photo.h"

class QxTdProfilePhoto : public QxTdPhoto
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("QxTdProfilePhoto cannot be created in QML.")
    Q_DISABLE_COPY(QxTdProfilePhoto)
public:
    explicit QxTdProfilePhoto(QObject *parent = nullptr);
};

#endif // QX_TD_PROFILE_PHOTO_H
