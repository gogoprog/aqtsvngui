#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QWidget>
#include "ui_aqtsvngui.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void commitButtonClicked();

private:
    Ui::aqtsvnguiClass ui;
};

#endif
