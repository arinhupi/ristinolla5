#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "RNGame.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    RNGame rngame;

    rngame.initTable(15, 15); // qml table size defined in RNTable.qml
    rngame.initPlayer(1, "human", 1);
    rngame.initPlayer(2, "computer", 2);


    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("rngame", &rngame);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
