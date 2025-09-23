#ifndef QX_TD_EMOJI_STATUS_H
#define QX_TD_EMOJI_STATUS_H

#include <QList>
#include "common/qx_td_object.h"

/**
 * @brief The QxTdEmojiStatus class
 *
 */
class QxTdEmojiStatus : public QxTdObject {
    Q_OBJECT
    Q_PROPERTY(qint64 customEmojiId READ customEmojiId WRITE setCustomEmojiId NOTIFY dataChanged)
    QML_ELEMENT
public:
    explicit QxTdEmojiStatus(QObject *parent = nullptr);
    explicit QxTdEmojiStatus(QObject *parent, qint64 customEmojiId_);

    qint64 customEmojiId() const;
    void setCustomEmojiId(qint64 value);

    void unmarshalJson(const QJsonObject &json) override;
    QJsonObject marshalJson() override;

private:
    Q_DISABLE_COPY(QxTdEmojiStatus)
    qint64 m_customEmojiId;

signals:
    void dataChanged();

};

#endif // QX_TD_EMOJI_STATUS_H
