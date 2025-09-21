#ifndef QX_TD_MESSAGE_LINK_H
#define QX_TD_MESSAGE_LINK_H

#include "common/qx_td_object.h"

/**
 * @brief The QxTdMessageLink class
 *
 * https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1message_link.html
 */
class QxTdMessageLink : public QxTdObject
{
    Q_OBJECT
    Q_PROPERTY(QString link READ link NOTIFY messageLinkChanged)
    Q_PROPERTY(bool isPublic READ isPublic NOTIFY messageLinkChanged)
    QML_ELEMENT
public:
    explicit QxTdMessageLink(QObject *parent = nullptr);

    QString link() const;
    bool isPublic() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void messageLinkChanged();

private:
    QString m_link { "" };
    bool m_is_public { false };

};

#endif // QX_TD_MESSAGE_LINK_H
