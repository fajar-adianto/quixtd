#pragma once

#include <QCoreApplication>
#include <QString>

const QString GETTEXT_DOMAIN = "teleports.ubports";

inline QString qxTranslate(const char *source_text) {
    return QCoreApplication::translate("QuixTd", source_text);
}
