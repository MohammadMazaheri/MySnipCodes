#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "model.hpp"

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

    //Begin my codes ...

    Model model(&engine);
    engine.rootContext()->setContextProperty("dataModel", QVariant::fromValue(&model));

    model.append("Item 1", 1.1, 11.11, "green");
    model.append("Item 2", 2.2, 22.22, "white");
    model.append("Item 3", 3.3, 33.33, "red");
    model.append("Item 4", 4.4, 44.44, "yellow");

    //... End of my codes

    engine.load(url);

    return app.exec();
}
