#ifndef SVNMANAGER_H_
#define SVNMANAGER_H_

#include "svnentry.h"
#include <QList>

class SVNManager
{
public:
    SVNManager();
    ~SVNManager();

    enum
    {
        FilterCount = 4
    };

    static SVNManager & getInstance()
    {
        static SVNManager *manager = new SVNManager();
        return *manager;
    }

    const QList<SVNEntry *> & getEntryList() const
        {
        return entryList;
    }

    void setFilter(const SVNEntry::Status status, const bool it_is_enabled)
    {
        filterIsEnabled[status] = it_is_enabled;
    }

    void clear();
    void analyze(const QString & path);
    void commit(const QString & message);
    void updateCurrent();

private:
    void parseLine(const QString & line);

    QList<SVNEntry *> entryList;
    bool filterIsEnabled[FilterCount];
    QString currentPath;

};

#endif
