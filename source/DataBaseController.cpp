//
// Created by wmatveev on 02.07.2024.
//

#include "DataBaseController.hpp"

DataBaseController::DataBaseController(QObject *parent)
        : QObject(parent)
{
    OpenDataBase();
}

DataBaseController::~DataBaseController()
{
    qDebug() << "[DB]:\tThe database has been closed.";
    db.close();
}

bool DataBaseController::OpenDataBase()
{
    db = QSqlDatabase::addDatabase("QPSQL");

    db.setHostName(hostName);
    db.setDatabaseName(databaseName);
    db.setUserName(userName);
    db.setPassword(password);

    if (!db.open()) {
        qDebug() << "[DB]:\tFailed to connect to database:" << db.lastError().text();
        return false;
    }

    qDebug() << "DB:\t[Connection to database successful]";
    return true;
}

bool DataBaseController::ExecuteSQLQuery(const QString &query)
{
    QSqlQuery sqlQuery;

    sqlQuery.prepare(query);

    if (!sqlQuery.exec()) {
        qDebug() << "[DB]:\tFailed to insert data into database:" << sqlQuery.lastError().text();
        return false;
    }

    qDebug() << "[DB] Data inserted successfully.";
    return true;
}

