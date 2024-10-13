#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Initialize database
    if (!initializeDatabase()) {
        qCritical() << "Failed to initialize database";
        return 1;
    }

    MainWindow w;
    w.show();

    return a.exec();
}