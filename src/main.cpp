#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "batteryinfo.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<BatteryInfo>("org.test.batteryinfo", 1, 0, "BatteryInfo");
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
