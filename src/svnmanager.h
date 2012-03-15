#ifndef SVNMANAGER_H_
#define SVNMANAGER_H_

#include "svnentry.h"
#include <QList>
#include <QThread>
#include <QObject>

class SVNManager
{
public:

    enum
    {
        FilterCount = 4
    };

    class Job : public QThread
    {
    public:
        void addLog(const QString &);
        void addLogLine(const QString &);
    };

    class AnalyzeJob : public Job
    {
    public:
        void run();
        QString path;
    };

    class CommitJob : public Job
    {
    public:
        void run();
        QString message;
    };

    SVNManager();
    ~SVNManager();

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
    AnalyzeJob analyzeJob;
    CommitJob commitJob;

};

#endif
