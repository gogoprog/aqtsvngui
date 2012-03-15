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

    void startLogMode();
    void endLogMode();
    void applyTreeModel();

public slots:
    void commitButtonClicked();
    void lineEditReturnPressed();
    void filterChanged0(int state);
    void filterChanged1(int state);
    void filterChanged2(int state);
    void filterChanged3(int state);
    void addLogLine(const QString &line);
    void addLog(const QString &line);
    void analyzeTerminated(bool success);
    void commitTerminated(bool success);

private:
    void fillFromPath(const QString & path);


    static MainWindow *instance;
    Ui::aqtsvnguiClass ui;
};

#endif
