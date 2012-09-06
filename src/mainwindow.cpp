#include "mainwindow.h"

#include <QDir>
#include <QTextCursor>
#include <QFileDialog>
#include "treemodel.h"
#include "svnmanager.h"
#include "svnentry.h"
#include "contextmenu.h"

// Public:

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QString currentPath;

    instance = this;

    ui.setupUi(this);

    contextMenu = new ContextMenu();

    currentPath = QDir::currentPath();

    fillFromPath(currentPath);
}

MainWindow::~MainWindow()
{

}

void MainWindow::startLogMode()
{
    ui.textEdit->setEnabled(false);
    ui.textEdit->clear();
}

void MainWindow::endLogMode()
{
    ui.textEdit->setEnabled(true);
}

void MainWindow::applyTreeModel()
{
    ui.treeView->setModel(new TreeModel());
    ui.treeView->header()->setResizeMode(0, QHeaderView::ResizeToContents);
    ui.treeView->header()->setResizeMode(1, QHeaderView::ResizeToContents);
}

// Public slots:

void MainWindow::browseButtonClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("Open Directory"), QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    fillFromPath(path);
}

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

void MainWindow::addLogLine(const QString &line)
{
    ui.textEdit->append(line);
}

void MainWindow::addLog(const QString &text)
{
    QTextCursor textCursor = ui.textEdit->textCursor();
    textCursor.insertText(text);
    textCursor.movePosition(QTextCursor::End);
    ui.textEdit->setTextCursor(textCursor);
}

void MainWindow::analyzeTerminated(bool success)
{
    if(success) {
        endLogMode();
        applyTreeModel();
        ui.textEdit->clear();
    }
}

void MainWindow::commitTerminated(bool success)
{
    if(success)
        ui.commitButton->setText("Ok");
    else
        ui.commitButton->setText("Retry");
}

// Private:

void MainWindow::fillFromPath(const QString & path)
{
    ui.treeView->setModel(NULL);
    SVNManager::getInstance().clear();
    SVNManager::getInstance().analyze(path);
    ui.lineEdit->setText(path);
}

MainWindow *MainWindow::instance = NULL;
