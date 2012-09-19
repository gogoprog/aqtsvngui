#ifndef Settings_H
#define Settings_H

#include <QMenu>
#include <QModelIndex>
#include <QVariant>
#include <QMap>
class QSettings;

class Settings
{
public:

    Settings();
    ~Settings();

    static Settings & getInstance()
    {
        static Settings *instance = new Settings();
        return *instance;
    }

    void initialize();

private:
    QSettings *settings;
};

#endif
