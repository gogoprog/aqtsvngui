#ifndef ContextMenu_H
#define ContextMenu_H

#include <QMenu>
#include <QModelIndex>
#include <QVariant>
class QPoint;
class SVNEntry;

class ContextMenu : public QMenu
{

public:
    ContextMenu(QWidget *parent = 0);
    ~ContextMenu();

    void init(SVNEntry *entry, const QPoint & pos);
private:

};

#endif
