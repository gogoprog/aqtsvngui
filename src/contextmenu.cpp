#include "contextmenu.h"

#include <QMenu>
#include <QDebug>
#include "svnentry.h"
#include "settings.h"

ContextMenu::ContextMenu(QWidget *parent)
: QMenu(parent)
{
    foreach(const Action & action, Settings::getInstance().getActionList()) {
        actionMap[ addAction(action.text) ] = action;
    }

    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(actionClicked(QAction*)));
}

ContextMenu::~ContextMenu()
{
}

void ContextMenu::setup(SVNEntry *_entry, const QPoint & pos)
{
    entry = _entry;
    this->popup(pos, 0);
}

void ContextMenu::actionClicked(QAction *_action)
{
    QString command;
    Action & action = actionMap[_action];

    command = action.command.replace("%f",entry->getRelativePath());

    system(command.toAscii());
}
