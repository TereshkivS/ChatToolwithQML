#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<MainWindow>("user", 1, 0, "MainWindow");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
//    QObject* rect = engine.findChild<QObject*>("portobject");
//    if(rect)
//        rect->setProperty("text", "300");

    return app.exec();
}
