#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>

bool initializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("shop.db");

    if (!db.open()) {
        qDebug() << "Error: connection with database failed";
        return false;
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT, role TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS inventory (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, category TEXT, condition TEXT, price REAL, stock INTEGER)");
    query.exec("CREATE TABLE IF NOT EXISTS repair_requests (id INTEGER PRIMARY KEY AUTOINCREMENT, item TEXT, status TEXT, date TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS transactions (id INTEGER PRIMARY KEY AUTOINCREMENT, items TEXT, total REAL, date TEXT)");

    // Add a default admin user if not exists
    query.prepare("INSERT OR IGNORE INTO users (username, password, role) VALUES (?, ?, ?)");
    query.addBindValue("admin");
    query.addBindValue(QString(QCryptographicHash::hash("admin123", QCryptographicHash::Sha256).toHex()));
    query.addBindValue("admin");
    query.exec();

    return true;
}

bool authenticateUser(const QString &username, const QString &password, QString &role)
{
    QSqlQuery query;
    query.prepare("SELECT role FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    
    query.addBindValue(QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex()));

    if (query.exec() && query.next()) {
        role = query.value(0).toString();
        return true;
    }

    return false;
}

QList<QStringList> getInventory()
{
    QList<QStringList> inventory;
    QSqlQuery query("SELECT * FROM inventory");

    while (query.next()) {
        QStringList item;
        item << query.value(0).toString() << query.value(1).toString() << query.value(2).toString()
             << query.value(3).toString() << query.value(4).toString() << query.value(5).toString();
        inventory.append(item);
    }

    return inventory;
}

QList<QStringList> getRepairRequests()
{
    QList<QStringList> repairRequests;
    QSqlQuery query("SELECT * FROM repair_requests");

    while (query.next()) {
        QStringList request;
        request << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
        repairRequests.append(request);
    }

    return repairRequests;
}

QList<QStringList> getTransactionHistory()
{
    QList<QStringList> transactionHistory;
    QSqlQuery query("SELECT * FROM transactions");

    while (query.next()) {
        QStringList transaction;
        transaction << query.value(0).toString() << query.value(1).toString() << query.value(2).toString() << query.value(3).toString();
        transactionHistory.append(transaction);
    }

    return transactionHistory;
}