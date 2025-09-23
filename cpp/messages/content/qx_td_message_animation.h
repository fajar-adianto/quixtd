#ifndef QX_TD_MESSAGE_ANIMATION_H
#define QX_TD_MESSAGE_ANIMATION_H

#include "messages/qx_td_message_content.h"
#include "files/qx_td_animation.h"
#include "qx_td_formatted_text.h"

class QxTdMessageAnimation : public QxTdMessageContent
{
    Q_OBJECT
    Q_PROPERTY(QxTdAnimation *animation READ animation NOTIFY dataChanged)
    Q_PROPERTY(QxTdFormattedText *caption READ caption NOTIFY dataChanged)
    QML_ELEMENT
    QML_UNCREATABLE("QxTdMessageAnimation cannot be created in QML.")
public:
    explicit QxTdMessageAnimation(QObject *parent = nullptr);

    QxTdAnimation *animation() const;
    QxTdFormattedText *caption() const;

    void unmarshalJson(const QJsonObject &json) override;

signals:
    void dataChanged();

private:
    Q_DISABLE_COPY(QxTdMessageAnimation)
    std::unique_ptr<QxTdAnimation> m_animation;
    std::unique_ptr<QxTdFormattedText> m_caption;
};

#endif // QX_TD_MESSAGE_ANIMATION_H
