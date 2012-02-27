#include "mainwindow.h"

#include "treemodel.h"
#include "svnmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QString currentPath;

    instance = this;

    ui.setupUi(this);

    currentPath = getenv("PWD");

    SVNManager::getInstance().analyze(currentPath);
    ui.lineEdit->setText(currentPath);

    ui.treeView->setModel(new TreeModel());
    ui.treeView->setColumnWidth(0, 48);
    ui.treeView->setColumnWidth(1, 128);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addLogLine(const QString &line)
{
    ui.textEdit->append(line);
    ui.textEdit->append("\n");
}

void MainWindow::commitButtonClicked()
{
    qDebug("test_commit");
}

MainWindow *MainWindow::instance = NULL;
