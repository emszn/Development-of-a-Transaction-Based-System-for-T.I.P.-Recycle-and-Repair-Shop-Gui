#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    loginWidget = new LoginWidget(this);
    dashboardWidget = new DashboardWidget(this);

    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(dashboardWidget);

    connect(loginWidget, &LoginWidget::loginSuccess, this, &MainWindow::onLoginSuccess);
    connect(dashboardWidget, &DashboardWidget::logout, this, &MainWindow::onLogout);

    stackedWidget->setCurrentWidget(loginWidget);

    resize(800, 600);
    setWindowTitle("T.I.P. Recycle and Repair Shop");
}

MainWindow::~MainWindow()
{
}

void MainWindow::onLoginSuccess(const QString &username, const QString &role)
{
    dashboardWidget->setUserInfo(username, role);
    stackedWidget->setCurrentWidget(dashboardWidget);
}

void MainWindow::onLogout()
{
    stackedWidget->setCurrentWidget(loginWidget);
}