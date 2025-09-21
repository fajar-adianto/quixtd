#include "qx_td_call_discard_reason.h"

QxTdCallDiscardReason::QxTdCallDiscardReason(QObject *parent)
    : QxTdObject(parent)
{
    setType(CALL_DISCARD_REASON);
}

QxTdCallDiscardReasonDeclined::QxTdCallDiscardReasonDeclined(QObject *parent)
{
    setType(CALL_DISCARD_REASON_DECLINED);
}

QJsonObject QxTdCallDiscardReasonDeclined::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonDeclined" },
    };
}

QxTdCallDiscardReasonDisconnected::QxTdCallDiscardReasonDisconnected(QObject *parent)
{
    setType(CALL_DISCARD_REASON_DISCONNECTED);
}

QJsonObject QxTdCallDiscardReasonDisconnected::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonDisconnected" },
    };
}

QxTdCallDiscardReasonEmpty::QxTdCallDiscardReasonEmpty(QObject *parent)
{
    setType(CALL_DISCARD_REASON_EMPTY);
}

QJsonObject QxTdCallDiscardReasonEmpty::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonEmpty" },
    };
}

QxTdCallDiscardReasonHungUp::QxTdCallDiscardReasonHungUp(QObject *parent)
{
    setType(CALL_DISCARD_REASON_HUNG_UP);
}

QJsonObject QxTdCallDiscardReasonHungUp::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonHungUp" },
    };
}

QxTdCallDiscardReasonMissed::QxTdCallDiscardReasonMissed(QObject *parent)
{
    setType(CALL_DISCARD_REASON_MISSED);
}

QJsonObject QxTdCallDiscardReasonMissed::marshalJson()
{
    return QJsonObject{
        { "@type", "callDiscardReasonMissed" },
    };
}
