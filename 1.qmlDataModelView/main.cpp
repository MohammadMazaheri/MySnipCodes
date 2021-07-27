#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "datamodel.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    QList<QObject*> dataList;
    dataList.append(new DataModel("Item 1", 1.1, 2.2, "red"));
    dataList.append(new DataModel("Item 2", 3.33, 4.44, "green"));
    dataList.append(new DataModel("Item 3", 5.555, 6.666, "blue"));
    dataList.append(new DataModel("Item 4", 7.7777, 8.8888, "yellow"));

    engine.rootContext()->setContextProperty("dataModel", QVariant::fromValue(dataList));

    engine.load(url);

    return app.exec();
}
