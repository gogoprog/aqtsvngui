#ifndef Settings_H
#define Settings_H

#include <QList>
#include "contextmenu.h"
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

    const QList<ContextMenu::Action> & getActionList() const { return actionList; }

private:
    QSettings *settings;
    QList<ContextMenu::Action> actionList;
};

#endif
