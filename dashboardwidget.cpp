#include "dashboardwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
#include "database.h"

DashboardWidget::DashboardWidget(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();
    userInfoLabel = new QLabel(this);
    logoutButton = new QPushButton("Logout", this);
    topLayout->addWidget(userInfoLabel);
    topLayout->addStretch();
    topLayout->addWidget(logoutButton);

    tabWidget = new QTabWidget(this);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(tabWidget);

    setupInventoryTab();
    setupCartTab();
    setupRepairRequestsTab();
    setupTransactionHistoryTab();

    connect(logoutButton, &QPushButton::clicked, this, &DashboardWidget::logout);
}

void DashboardWidget::setUserInfo(const QString &username, const QString &role)
{
    userInfoLabel->setText(QString("Welcome, %1 (%2)").arg(username, role));
    if (role == "admin") {
        setupAdminTab();
    } else {
        int index = tabWidget->indexOf(tabWidget->findChild<QWidget*>("adminTab"));
        if (index != -1) {
            tabWidget->removeTab(index);
        }
    }
}

void DashboardWidget::setupInventoryTab()
{
    QWidget *inventoryTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(inventoryTab);

    QTableWidget *inventoryTable = new QTableWidget(this);
    inventoryTable->setColumnCount(6);
    inventoryTable->setHorizontalHeaderLabels({"ID", "Name", "Category", "Condition", "Price", "Stock"});
    inventoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Populate inventory table
    QList<QStringList> inventory = getInventory();
    inventoryTable->setRowCount(inventory.size());
    for (int i = 0; i < inventory.size(); ++i) {
        for (int j = 0; j < 6; ++j) {
            inventoryTable->setItem(i, j, new QTableWidgetItem(inventory[i][j]));
        }
    }

    layout->addWidget(inventoryTable);

    tabWidget->addTab(inventoryTab, "Inventory");
}

void DashboardWidget::setupCartTab()
{
    QWidget *cartTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(cartTab);

    QTableWidget *cartTable = new QTableWidget(this);
    cartTable->setColumnCount(4);
    cartTable->setHorizontalHeaderLabels({"ID", "Name", "Price", "Quantity"});
    cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPushButton *checkoutButton = new QPushButton("Checkout", this);
    connect(checkoutButton, &QPushButton::clicked, this, [this, cartTable]() {
        // Implement checkout logic here
        QMessageBox::information(this, "Checkout", "Checkout completed successfully!");
        cartTable->setRowCount(0);
    });

    layout->addWidget(cartTable);
    layout->addWidget(checkoutButton);

    tabWidget->addTab(cartTab, "Cart");
}

void DashboardWidget::setupRepairRequestsTab()
{
    QWidget *repairRequestsTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(repairRequestsTab);

    QTableWidget *repairRequestsTable = new QTableWidget(this);
    repairRequestsTable->setColumnCount(4);
    repairRequestsTable->setHorizontalHeaderLabels({"ID", "Item", "Status", "Date"});
    repairRequestsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Populate repair requests table
    QList<QStringList> repairRequests = getRepairRequests();
    repairRequestsTable->setRowCount(repairRequests.size());
    for (int i = 0; i < repairRequests.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            repairRequestsTable->setItem(i, j, new QTableWidgetItem(repairRequests[i][j]));
        }
    }

    layout->addWidget(repairRequestsTable);

    tabWidget->addTab(repairRequestsTab, "Repair Requests");
}

void DashboardWidget::setupTransactionHistoryTab()
{
    QWidget *transactionHistoryTab = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(transactionHistoryTab);

    QTableWidget *transactionHistoryTable = new QTableWidget(this);
    transactionHistoryTable->setColumnCount(4);
    transactionHistoryTable->setHorizontalHeaderLabels({"ID", "Items", "Total", "Date"});
    transactionHistoryTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Populate transaction history table
    QList<QStringList> transactionHistory = getTransactionHistory();
    transactionHistoryTable->setRowCount(transactionHistory.size());
    for (int i = 0; i < transactionHistory.size(); ++i) {
        for (int j = 0; j < 4; ++j) {
            transactionHistoryTable->setItem(i, j, new QTableWidgetItem(transactionHistory[i][j]));
        }
    }

    layout->addWidget(transactionHistoryTable);

    tabWidget->addTab(transactionHistoryTab, "Transaction History");
}

void DashboardWidget::setupAdminTab()
{
    QWidget *adminTab = new QWidget(this);
    adminTab->setObjectName("adminTab");
    QVBoxLayout *layout = new QVBoxLayout(adminTab);

    QPushButton *manageUsersButton = new QPushButton("Manage Users", this);
    QPushButton *manageInventoryButton = new QPushButton("Manage Inventory", this);
    QPushButton *viewReportsButton = new QPushButton("View Reports", this);

    layout->addWidget(manageUsersButton);
    layout->addWidget(manageInventoryButton);
    layout->addWidget(viewReportsButton);

    tabWidget->addTab(adminTab, "Admin");
}