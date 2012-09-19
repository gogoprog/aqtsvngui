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

    struct Action
    {
        QString text;
        QString command;
    };

    ContextMenu(QWidget *parent = 0);
    virtual ~ContextMenu();

    void setup(SVNEntry *entry, const QPoint & pos);

public slots:
    void actionClicked(QAction *action);

private:
    SVNEntry *entry;
    QMap<QAction*,Action> actionMap;
};

#endif
