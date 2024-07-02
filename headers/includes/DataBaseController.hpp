//
// Created by wmatveev on 02.07.2024.
//

#ifndef WSCAN_DATABASECONTROLLER_HPP
#define WSCAN_DATABASECONTROLLER_HPP


#include <QObject>
#include <QDebug>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


class DataBaseController : public QObject
{
    Q_OBJECT

    public:
        explicit DataBaseController(QObject *parent = nullptr);
        ~DataBaseController() override;

    public:
        bool ExecuteSQLQuery(const QString &query);

    private:
        QSqlDatabase db;
        QString hostName     = "192.168.45.197";
        QString databaseName = "w_scan";
        QString userName     = "postgres";
        QString password     = "Matller_17";

        bool OpenDataBase();
};


#endif //WSCAN_DATABASECONTROLLER_HPP
