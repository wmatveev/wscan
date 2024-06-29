//
// Created by wmatveev on 28.06.2024.
//

#include "ScaleController.hpp"

ScaleController::ScaleController(QObject *parent)
        : QThread(parent),
          curlHandle(nullptr)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curlHandle = curl_easy_init();
    if (!curlHandle) {
        std::cerr << "Error initializing libcurl." << std::endl;
    }
}

ScaleController::~ScaleController()
{
    if (curlHandle) {
        curl_easy_cleanup(curlHandle);
    }
    curl_global_cleanup();
}

void ScaleController::run()
{
    if (!curlHandle) {
        std::cerr << "Libcurl handle is not initialized. Exiting thread." << std::endl;
        return;
    }

    QVector<int> weightFromScales;

    std::string zoneConfigPath = "/home/matller/detect_libra_digits/cam202.json";
    std::string shapesConfigPath = "/home/matller/detect_libra_digits/shape.json";
    std::string videoPath = "rtsp://admin:Matller_17@192.168.45.202:554/Streaming/Channels/101";

    for (int i = 0; i < numIterations; ++i)
    {
        float weightNumber = detectDigitFromPython(zoneConfigPath, shapesConfigPath, videoPath);
        weightFromScales.append(weightNumber);

        qDebug() << weightNumber;

        // Delay before the next iteration
        if (i < numIterations - 1) {
            msleep(delayMs);
        }
    }

    emit weightReadyForRead(weightFromScales);
}

float ScaleController::detectDigitFromPython(const std::string &zoneConfigPath, const std::string &shapesConfigPath, const std::string &videoPath)
{
    float result = 0.0;

    if (curlHandle) {
        std::string readBuffer;
        std::string jsonData = "{\"zone_config_path\": \"" + zoneConfigPath + "\", \"shapes_config_path\": \"" + shapesConfigPath + "\", \"video_path\": \"" + videoPath + "\"}";

        curl_easy_setopt(curlHandle, CURLOPT_URL, "http://192.168.45.205:5000/detect_digit");
        curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, jsonData.c_str());

        curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &readBuffer);

        struct curl_slist *headers = nullptr;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curlHandle, CURLOPT_HTTPHEADER, headers);

        CURLcode res = curl_easy_perform(curlHandle);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } else {
            // Parse JSON response
            size_t start = readBuffer.find(":") + 1;
            size_t end = readBuffer.find("}");
            std::string resultStr = readBuffer.substr(start, end - start);
            result = std::stof(resultStr);
        }

        curl_slist_free_all(headers);
    }

    return result;
}
