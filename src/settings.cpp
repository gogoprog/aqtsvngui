#include "settings.h"

#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QStringList>
#include <QString>

Settings::Settings()
    : settings(0)
{
}

Settings::~Settings()
{
    if(settings)
        delete settings;
}

void Settings::initialize()
{
    settings = new QSettings(QDir::homePath() + "/.aqtsvngui.ini", QSettings::IniFormat);

    settings->beginGroup("actions");

    if(settings->childKeys().size() == 0) {
        // Setup default actions
        settings->setValue("Diff","diffuse %f");
        settings->setValue("Revert","svn revert %f");
    }

    foreach(const QString & key, settings->childKeys()) {
        actionList.append(ContextMenu::Action());
        ContextMenu::Action & action = actionList.last();
        action.text = key;
        action.command = settings->value(key,"").toString();
    }

    settings->endGroup();
}
