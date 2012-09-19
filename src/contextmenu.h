#ifndef ContextMenu_H
#define ContextMenu_H

#include <QMenu>
#include <QModelIndex>
#include <QVariant>
#include <QMap>
class QPoint;
class SVNEntry;

class ContextMenu : public QMenu
{
    Q_OBJECT

public:

    struct MenuAction
    {
        QString text;
        QString command;
        QString icon;
    };

    ContextMenu(QWidget *parent = 0);
    virtual ~ContextMenu();

    void init(SVNEntry *entry, const QPoint & pos);

public slots:
    void actionClicked(QAction *action);

private:
    SVNEntry *entry;
    QMap<QAction*,MenuAction> actionMap;
};

#endif
