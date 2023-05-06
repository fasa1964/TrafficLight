
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "classarduinoboard.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    app.setApplicationName("ArduinoConnection");
    app.setOrganizationName("qt-example@arduino");
    app.setOrganizationDomain("qt-example@arduino.com");

    qmlRegisterType<ClassArduinoBoard>("ClassArduinoBoard", 1,0, "Arduino");

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/TrafficLight/Main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
        &app, []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
