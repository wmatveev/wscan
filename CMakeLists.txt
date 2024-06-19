cmake_minimum_required(VERSION 3.14)

project(wscan LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS StateMachine)

add_executable(wscan
        "Source Files/main.cpp"
        "Source Files/TcpServer.cpp"
        "Source Files/ScanStateMachine.cpp"

        "Header Files/Includes/TcpServer.hpp"
        "Header Files/Includes/ScanStateMachine.hpp"

        "Header Files/Interfaces/ITcpServer.hpp"
)

target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(wscan Qt${QT_VERSION_MAJOR}::StateMachine)

# add path to header files
target_include_directories(wscan PUBLIC "./Header Files/Includes/")
target_include_directories(wscan PUBLIC "./Header Files/Interfaces/")

include(GNUInstallDirs)
install(TARGETS wscan
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
