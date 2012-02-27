#include "mainwindow.h"

#include "treemodel.h"
#include "svnmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);

	SVNManager::getInstance().analyze("/home/gogoprog/code/ggp");

	ui.treeView->setModel(new TreeModel());
	ui.treeView->setColumnWidth(0, 48);
	ui.treeView->setColumnWidth(1, 128);
}

MainWindow::~MainWindow()
{

}

void MainWindow::commitButtonClicked()
{
    qDebug("test_commit");
}
