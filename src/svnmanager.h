#ifndef SVNMANAGER_H_
#define SVNMANAGER_H_

#include "svnentry.h"
#include <QList>

class SVNManager
{
public:
    SVNManager();
    ~SVNManager();

    static SVNManager & getInstance() {
        static SVNManager *manager = new SVNManager();
        return *manager;
    }

    const QList<SVNEntry *> & getEntryList() const {
        return entryList;
    }

    void analyze(const QString & path);

private:
    void parseLine(const QString & line);

    QList<SVNEntry *> entryList;

};

#endif
