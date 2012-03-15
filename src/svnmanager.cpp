#include "svnmanager.h"

#include "mainwindow.h"
#include <QString>
#include <QStringList>
#include <stdio.h>

// Public:

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
    QString command;

    if(path != ".") {
        command += "cd " + path + " && ";
    }

    command += "svn st";

    {
        FILE *fp;
        char buffer[256];
        
        fp = popen(command.toAscii(), "r");

        if (fp == NULL)
            return;


        while (fgets(buffer, 256, fp) != NULL) {
            parseLine(buffer);
        }

        pclose(fp);
    }

    currentPath = path;
}

void SVNManager::commit(const QString & message)
{
    QString command;

    command += "svn ci ";

    foreach(const SVNEntry *entry, entryList) {
        if(entry->isSelected()) {
            command += "\"" + entry->getRelativePath() + "\" ";
        }
    }

    command += "-m \"" + message + "\"";

    qDebug(command.toAscii());
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
    }


    fieldList[1].remove('\n');

    entry->relativePath = fieldList[1];

    if(filterIsEnabled[int(entry->status)])
        entryList.push_back(entry);
}
