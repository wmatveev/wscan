//
// Created by wmatveev on 28.06.2024.
//

#ifndef WSCAN_SCALECONTROLLER_HPP
#define WSCAN_SCALECONTROLLER_HPP

#include <QObject>
#include <QThread>
#include <QDebug>
#include <curl/curl.h>
#include <iostream>
#include <string>

// Callback function to handle data received from the server
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

class ScaleController : public QThread
{
    Q_OBJECT

    public:
        explicit ScaleController(QObject *parent = nullptr);
        ~ScaleController();


    protected:
        void run() override;

    private:
        float detectDigitFromPython(const std::string& zoneConfigPath, const std::string& shapesConfigPath, const std::string& videoPath);

    private:
        CURL *curlHandle;
        const int numIterations = 15;
        const int delayMs = 10;
};

#endif // WSCAN_SCALECONTROLLER_HPP
