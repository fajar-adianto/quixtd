#include "qx_td_message_forward_origin_factory.h"
#include "qx_td_message_forward_origin.h"

QxTdMessageForwardOrigin *QxTdMessageForwardOriginFactory::create(const QJsonObject &json, QObject *parent)
{
    const QString type = json["@type"].toString();
    QxTdMessageForwardOrigin *origin = nullptr;
    if (type == "messageForwardOriginChannel") {
        origin = new QxTdMessageForwardOriginChannel(parent);
    } else if (type == "messageForwardOriginChat") {
        origin = new QxTdMessageForwardOriginChat(parent);
    } else if (type == "messageForwardOriginHiddenUser") {
        origin = new QxTdMessageForwardOriginHiddenUser(parent);
    } else if (type == "messageForwardOriginUser") {
        origin = new QxTdMessageForwardOriginUser(parent);
    }
    if (origin) {
        origin->unmarshalJson(json);
    }
    return origin;
}
