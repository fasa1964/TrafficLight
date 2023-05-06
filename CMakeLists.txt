cmake_minimum_required(VERSION 3.16)

project(TrafficLight VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick QuickControls2 SerialPort)

qt_standard_project_setup()

qt_add_executable(appTrafficLight
    main.cpp
    classarduinoboard.h
    classarduinoboard.cpp
)

qt_add_qml_module(appTrafficLight
    URI TrafficLight
    VERSION 1.0
    QML_FILES Main.qml
)

set_target_properties(appTrafficLight PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appTrafficLight
    PRIVATE Qt6::Quick
    PRIVATE Qt6::QuickControls2
    PRIVATE Qt6::SerialPort
)

install(TARGETS appTrafficLight
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
