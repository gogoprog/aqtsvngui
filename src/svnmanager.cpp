#include "svnmanager.h"

#include <QString>
#include <QStringList>
#include <QMetaObject>
#include <QDir>
#include <stdio.h>
#include "mainwindow.h"

#if _WINDOWS
#define pipeOpen _popen
#define pipeClose _pclose
#else
#define pipeOpen popen
#define pipeClose pclose
#endif

// Public:

void SVNManager::Job::addLog(const QString & text)
{
    QMetaObject::invokeMethod(&MainWindow::getInstance(), "addLog", Qt::QueuedConnection, Q_ARG(QString, text));
}

void SVNManager::Job::addLogLine(const QString & text)
{
    QMetaObject::invokeMethod(&MainWindow::getInstance(), "addLogLine", Qt::QueuedConnection, Q_ARG(QString, text));
}

void SVNManager::AnalyzeJob::run()
{
    QString command;
    FILE *fp;
    char buffer[256];

    addLogLine("Analyzing " + path + " ..." );

    command += "svn st";

    fp = pipeOpen(command.toAscii(), "r");

    if (fp == NULL)
        return;

    while (fgets(buffer, 256, fp) != NULL) {
        SVNManager::getInstance().parseLine(buffer);
        addLog(".");
    }

    pipeClose(fp);


    SVNManager::getInstance().currentPath = path;

    QMetaObject::invokeMethod(&MainWindow::getInstance(), "analyzeTerminated", Qt::QueuedConnection, Q_ARG(bool, true));
}

void SVNManager::CommitJob::run()
{
    QString command;
    FILE *fp;
    char buffer[256];

    command += "svn ci ";

    foreach(const SVNEntry *entry, SVNManager::getInstance().entryList) {
        if(entry->isSelected()) {
            command += "\"" + entry->getRelativePath() + "\" ";
        }
    }

    command += "-m \"" + message + "\"";

    fp = pipeOpen(command.toAscii(), "r");

    if (fp == NULL)
        return;

    while (fgets(buffer, 256, fp) != NULL) {
        addLog(buffer);
    }

    pipeClose(fp);

    QMetaObject::invokeMethod(&MainWindow::getInstance(), "commitTerminated", Qt::QueuedConnection, Q_ARG(bool, true));
}

SVNManager::SVNManager()
{
    memset(filterIsEnabled, 1, sizeof(bool) * FilterCount);
}

SVNManager::~SVNManager()
{
    clear();
}

void SVNManager::clear()
{
    foreach(SVNEntry *entry, entryList) {
        delete entry;
    }

    entryList.clear();
}

void SVNManager::analyze(const QString & path)
{
    if(path != ".") {
        QDir::setCurrent(path);
    }

    MainWindow::getInstance().startLogMode();
    analyzeJob.path = path;
    analyzeJob.start();
}

void SVNManager::commit(const QString & message)
{
    MainWindow::getInstance().startLogMode();
    commitJob.message = message;
    commitJob.start();
}

void SVNManager::updateCurrent()
{
    clear();
    analyze(currentPath);
}

// Private:

void SVNManager::parseLine(const QString & line)
{
    QStringList fieldList;

    if (line.contains("warning")) {
        MainWindow::getInstance().addLogLine(line);
        return;
    }

    SVNEntry *entry = new SVNEntry();

    fieldList = line.split(' ', QString::SkipEmptyParts);

    if(fieldList.size()<2)
        return;

    switch(fieldList[0].toAscii()[0]) {
        case '?':
            entry->status = SVNEntry::Unversioned;
            break;
        case 'M':
            entry->status = SVNEntry::Modified;
            break;
        case 'D':
            entry->status = SVNEntry::Deleted;
            break;
        case 'A':
            entry->status = SVNEntry::Added;
            break;
        default:
            entry->status = SVNEntry::Unknown;
            break;
    }

    fieldList[1].remove('\n');

    entry->relativePath = fieldList[1];

    if(filterIsEnabled[int(entry->status)])
        entryList.push_back(entry);
}
