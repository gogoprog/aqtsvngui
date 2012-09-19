#include "contextmenu.h"

#include <QMenu>
#include <QDebug>
#include "svnentry.h"

ContextMenu::ContextMenu(QWidget *parent)
: QMenu(parent)
{
    addAction( "Diff" );
    addAction( "Revert" );

    connect(this, SIGNAL(triggered(QAction*)), this, SLOT(actionClicked(QAction*)));
}

ContextMenu::~ContextMenu()
{
}

void ContextMenu::init(SVNEntry *_entry, const QPoint & pos)
{
    entry = _entry;
    this->popup(pos, 0);
}

void ContextMenu::actionClicked(QAction *action)
{
    // :TODO:
}
