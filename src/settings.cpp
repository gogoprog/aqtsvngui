#include "settings.h"

#include <QMenu>
#include <QDebug>
#include <QSettings>
#include <QDir>

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
}
