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
    
    static MainWindow & getInstance() {
        return *instance;
    }

    void addLogLine(const QString &line);

public slots:
    void commitButtonClicked();

private:
    static MainWindow *instance;
    Ui::aqtsvnguiClass ui;
};

#endif
