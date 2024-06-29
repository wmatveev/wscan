cmake_minimum_required(VERSION 3.14)

project(wscan LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#set(CMAKE_PREFIX_PATH "/Users/wmatveev/Documents/_dev/QT/6.6.1/macos")

#if (WIN32)
#    set(CURL_INCLUDE_DIR $ENV{CURL_INCLUDE_DIR})
#    set(CURL_LIBRARY $ENV{CURL_LIBRARY})
#elseif (UNIX)
#    find_package(CURL REQUIRED)
#endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS SerialPort)
find_package(CURL REQUIRED)

add_executable(wscan
        "source Files/main.cpp"
        "source Files/TcpServer.cpp"
        "source Files/LaserController.cpp"
        "source Files/ScannerController.cpp"
        "source Files/HttpController.cpp"
        "source Files/PortsController.cpp"
        "source Files/ScaleController.cpp"
        "source Files/TrafficLightController.cpp"

        "headers/includes/TcpServer.hpp"
        "headers/includes/LaserController.hpp"
        "headers/includes/ScannerController.hpp"
        "headers/includes/HttpController.hpp"
        "headers/includes/PortsController.hpp"
        "headers/includes/ScaleController.hpp"
        "headers/includes/TrafficLightController.hpp"

        "headers/interfaces/ITcpServer.hpp"
)

target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::SerialPort)
target_link_libraries(wscan ${CURL_LIBRARIES})

# add path to header files
target_include_directories(wscan PUBLIC "headers/includes/")
target_include_directories(wscan PUBLIC "headers/interfaces/")
target_include_directories(wscan PUBLIC ${CURL_INCLUDE_DIRS})

include(GNUInstallDirs)
install(TARGETS wscan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
