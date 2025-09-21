#include "qx_td_notification_settings.h"

QxTdNotificationSettings::QxTdNotificationSettings(QObject *parent)
    : QxTdObject(parent)
    , m_muteFor(0)
    , m_useDefaultMuteFor(false)
    , m_showPreview(false)
{
    setType(NOTIFICATION_SETTINGS);
}

qint32 QxTdNotificationSettings::muteFor() const
{
    return m_muteFor;
}

void QxTdNotificationSettings::setMuteFor(const qint32 &duration)
{
    m_muteFor = duration;
}

bool QxTdNotificationSettings::useDefaultMuteFor() const
{
    return m_useDefaultMuteFor;
}

void QxTdNotificationSettings::setUseDefaultMuteFor(const bool &value)
{
    m_useDefaultMuteFor = value;
}

QString QxTdNotificationSettings::sound() const
{
    return m_sound;
}

bool QxTdNotificationSettings::useDefaultSound() const
{
    return m_useDefaultSound;
}

bool QxTdNotificationSettings::showPreview() const
{
    return m_showPreview;
}

bool QxTdNotificationSettings::useDefaultShowPreview() const
{
    return m_useDefaultShowPreview;
}

bool QxTdNotificationSettings::disablePinnedMsgNotes() const
{
    return m_disablePinnedMsgNotes;
}

bool QxTdNotificationSettings::useDefaultDisablePinnedMsgNotes() const
{
    return m_useDefaultDisablePinnedMsgNotes;
}

bool QxTdNotificationSettings::disableMentionNotes() const
{
    return m_disableMentionNotes;
}

bool QxTdNotificationSettings::useDefaultDisableMentionNotes() const
{
    return m_useDefaultDisableMentionNotes;
}

void QxTdNotificationSettings::unmarshalJson(const QJsonObject &json)
{
    QxTdObject::unmarshalJson(json);
    auto muteFor = json["mute_for"].toInt();
    auto useDefaultMuteFor = json["use_default_mute_for"].toBool();
    if (m_muteFor != muteFor || m_useDefaultMuteFor != useDefaultMuteFor) {
        m_muteFor = muteFor;
        m_useDefaultMuteFor = useDefaultMuteFor;
        emit muteForChanged();
    }

    auto sound = json["sound"].toString();
    auto useDefaultSound = json["use_default_sound"].toBool();
    if (m_sound != sound || m_useDefaultSound != useDefaultSound) {
        m_sound = sound;
        m_useDefaultSound = useDefaultSound;
        emit soundChanged();
    }

    auto showPreview = json["show_preview"].toBool();
    auto useDefaultShowPreview = json["use_default_show_preview"].toBool();
    if (m_showPreview != showPreview || m_useDefaultShowPreview != useDefaultShowPreview) {
        m_showPreview = showPreview;
        m_useDefaultShowPreview = useDefaultShowPreview;
        emit showPreviewChanged();
    }

    auto disablePinnedMsgNotes = json["disable_pinned_message_notifications"].toBool();
    auto useDefaultDisablePinnedMsgNotes = json["use_default_disable_pinned_message_notifications"].toBool();
    if (m_disablePinnedMsgNotes != disablePinnedMsgNotes || m_useDefaultDisablePinnedMsgNotes != useDefaultDisablePinnedMsgNotes) {
        m_disablePinnedMsgNotes = disablePinnedMsgNotes;
        m_useDefaultDisablePinnedMsgNotes = useDefaultDisablePinnedMsgNotes;
        emit disablePinnedMsgNotesChanged();
    }

    auto disableMentionNotes = json["disable_mention_notifications"].toBool();
    auto useDefaultDisableMentionNotes = json["use_default_disable_mention_notifications"].toBool();
    if (m_disableMentionNotes != disableMentionNotes || m_useDefaultDisableMentionNotes != useDefaultDisableMentionNotes) {
        m_disableMentionNotes = disableMentionNotes;
        m_useDefaultDisableMentionNotes = useDefaultDisableMentionNotes;
        emit disableMentionNotesChanged();
    }
}

QJsonObject QxTdNotificationSettings::marshalJson()
{
    return QJsonObject{
        { "@type", "chatNotificationSettings" },
        { "use_default_mute_for", m_useDefaultMuteFor },
        { "mute_for", m_muteFor },
        { "use_default_sound", m_useDefaultSound },
        { "sound", m_sound },
        { "use_default_show_preview", m_useDefaultShowPreview },
        { "show_preview", m_showPreview },
        { "use_default_disable_pinned_message_notifications", m_useDefaultDisablePinnedMsgNotes },
        { "disable_pinned_message_notifications", m_disablePinnedMsgNotes },
        { "use_default_disable_mention_notifications", m_useDefaultDisableMentionNotes },
        { "disable_mention_notifications", m_disableMentionNotes }

    };
}
