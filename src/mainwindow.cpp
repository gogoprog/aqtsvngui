#include "mainwindow.h"

#include <QDir>
#include "treemodel.h"
#include "svnmanager.h"
#include "svnentry.h"

// Public:

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QString currentPath;

    instance = this;

    ui.setupUi(this);

    currentPath = getenv("PWD");

    fillFromPath(currentPath);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addLogLine(const QString &line)
{
    ui.textEdit->append(line);
    ui.textEdit->append("\n");
}

// Public slots:

void MainWindow::commitButtonClicked()
{
    SVNManager::getInstance().commit(ui.textEdit->toPlainText());
}

void MainWindow::lineEditReturnPressed()
{
    QString path = ui.lineEdit->text();

    if(QDir(path).exists()) {
        fillFromPath(path);
    }
}

void MainWindow::filterChanged0(int state)
{
    SVNManager::getInstance().setFilter(SVNEntry::Unversioned, state);
    SVNManager::getInstance().updateCurrent();
    applyTreeModel();
}

void MainWindow::filterChanged1(int state)
{
    SVNManager::getInstance().setFilter(SVNEntry::Added, state);
    SVNManager::getInstance().updateCurrent();
    applyTreeModel();
}

void MainWindow::filterChanged2(int state)
{
    SVNManager::getInstance().setFilter(SVNEntry::Deleted, state);
    SVNManager::getInstance().updateCurrent();
    applyTreeModel();
}

void MainWindow::filterChanged3(int state)
{
    SVNManager::getInstance().setFilter(SVNEntry::Modified, state);
    SVNManager::getInstance().updateCurrent();
    applyTreeModel();
}

// Private:

void MainWindow::fillFromPath(const QString & path)
{
    SVNManager::getInstance().clear();
    SVNManager::getInstance().analyze(path);
    ui.lineEdit->setText(path);

    applyTreeModel();
}

void MainWindow::applyTreeModel()
{
    ui.treeView->setModel(new TreeModel());
    ui.treeView->setColumnWidth(0, 48);
    ui.treeView->setColumnWidth(1, 128);
}

MainWindow *MainWindow::instance = NULL;
