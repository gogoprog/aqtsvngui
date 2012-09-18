#include "contextmenu.h"

#include <QMenu>
#include "svnentry.h"

ContextMenu::ContextMenu(QWidget *parent)
: QMenu(parent)
{
    addAction( "Diff" );
    addAction( "Revert" );
}

ContextMenu::~ContextMenu()
{
}

void ContextMenu::init(SVNEntry *entry, const QPoint & pos)
{
    this->popup(pos, 0);
}


