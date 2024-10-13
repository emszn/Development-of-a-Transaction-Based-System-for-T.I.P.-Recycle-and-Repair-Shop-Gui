#ifndef DASHBOARDWIDGET_H
#define DASHBOARDWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLabel>

class DashboardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DashboardWidget(QWidget *parent = nullptr);
    void setUserInfo(const QString &username, const QString &role);

signals:
    void logout();

private:
    QTabWidget *tabWidget;
    QLabel *userInfoLabel;
    QPushButton *logoutButton;

    void setupInventoryTab();
    void setupCartTab();
    void setupRepairRequestsTab();
    void setupTransactionHistoryTab();
    void setupAdminTab();
};

#endif // DASHBOARDWIDGET_H 