#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QList>
#include <QStringList>

bool initializeDatabase();
bool authenticateUser(const QString &username, const QString &password, QString &role);
QList<QStringList> getInventory();
QList<QStringList> getRepairRequests();
QList<QStringList> getTransactionHistory();

#endif // DATABASE_H