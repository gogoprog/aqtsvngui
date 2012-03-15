#ifndef SVNENTRY_H_
#define SVNENTRY_H_

#include <QString>

class SVNEntry
{
    friend class SVNManager;

public:
    enum Status {
        Unversioned,
        Modified,
        Deleted,
        Added
    };

    SVNEntry();
    ~SVNEntry();

    Status getStatus() const
    {
        return status;
    }

    const QString & getRelativePath() const
    {
        return relativePath;
    }

    bool isSelected() const
    {
        return itIsSelected;
    }

    void setIsSelected(const bool value)
    {
        itIsSelected = value;
    }

private:
    Status status;
    QString relativePath;
    bool itIsSelected;
};

#endif
