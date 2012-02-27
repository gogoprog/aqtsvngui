#include "svnmanager.h"

#include <QString>
#include <QStringList>
#include <stdio.h>

// Public:

SVNManager::SVNManager()
{

}

SVNManager::~SVNManager()
{

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
}

// Private:

void SVNManager::parseLine(const QString & line)
{
    QStringList fieldList;

    if (line.contains("warning")) {
        return;
    }

    SVNEntry *entry = new SVNEntry();

    fieldList = line.split(' ', QString::SkipEmptyParts);

    if (fieldList[0] == "?") {
        entry->status = SVNEntry::Unversioned;
    }
    else if (fieldList[0] == "M") {
        entry->status = SVNEntry::Modified;
    }

    fieldList[1].remove('\n');

    entry->relativePath = fieldList[1];

    entryList.push_back(entry);
}
