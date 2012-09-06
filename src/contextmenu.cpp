#include "contextmenu.h"

#include <QMenu>

ContextMenu::ContextMenu(QWidget *parent)
: QMenu(parent)
{
    addAction( "Diff" );
    addAction( "Revert" );
}

ContextMenu::~ContextMenu()
{
}


