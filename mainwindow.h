#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "loginwidget.h"
#include "dashboardwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onLoginSuccess(const QString &username, const QString &role);
    void onLogout();

private:
    QStackedWidget *stackedWidget;
    LoginWidget *loginWidget;
    DashboardWidget *dashboardWidget;
};

#endif // MAINWINDOW_H