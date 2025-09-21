#include "common/qx_td_object.h"
#include <QJsonValue>
#include <QDateTime>
#include "qx_td_message_forward_info.h"
#include "qx_td_message_forward_origin_factory.h"
#include "common/qx_td_helpers.h"
#include "user/requests/qx_td_get_user_request.h"
#include "chat/requests/qx_td_get_chat_request.h"
#include "chat/qx_td_chat.h"
#include "utils/qx_td_await.h"
#include "user/qx_td_users.h"
#include "utils/qx_td_translate_tools.h"

QxTdMessageForwardInfo::QxTdMessageForwardInfo(QObject *parent)
    : QxTdObject(parent)
    , m_origin(nullptr)
    , m_date(0)
    , m_fromChatId(0)
    , m_fromMessageId(0)
{
    // Intentionally left empty.
}

QxTdMessageForwardOrigin *QxTdMessageForwardInfo::origin() const
{
    return m_origin.data();
}

QDateTime QxTdMessageForwardInfo::qmlDate() const
{
    return QDateTime::fromSecsSinceEpoch(m_date);
}
qint32 QxTdMessageForwardInfo::date() const
{
    return m_date;
}

QString QxTdMessageForwardInfo::qmlFromChatId() const
{
    return m_fromChatId.toQmlValue();
}
qint64 QxTdMessageForwardInfo::fromChatId() const
{
    return m_fromChatId.value();
}

QString QxTdMessageForwardInfo::qmlFromMessageId() const
{
    return m_fromMessageId.toQmlValue();
}
qint64 QxTdMessageForwardInfo::fromMessageId() const
{
    return m_fromMessageId.value();
}

QString QxTdMessageForwardInfo::displayedName() const
{
    if (m_origin)
    {
        return m_origin->originSummary();
    }
    return qxTranslate("Unknown origin");

}

void QxTdMessageForwardInfo::unmarshalJson(const QJsonObject &json)
{
    if (json.isEmpty()) {
        return;
    }
    QxTdObject::unmarshalJson(json);
    const QJsonObject origin = json["origin"].toObject();
    m_origin.reset(QxTdMessageForwardOriginFactory::create(origin, this));
    connect(m_origin.data(), &QxTdMessageForwardOrigin::forwardOriginChanged, this, &QxTdMessageForwardInfo::forwardInfoChanged);
    m_date = json["date"].toInt();
    m_fromChatId = json["forwarded_from_chat_id"].toVariant().toLongLong();
    m_fromMessageId = json["forwarded_from_message_id"].toVariant().toLongLong();
    emit forwardInfoChanged();
}
