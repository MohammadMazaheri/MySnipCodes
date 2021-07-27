#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "listmodel.hpp"

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

    ListModel listModel;
    listModel.append("Item test1", 3.14);
    listModel.append("Item test2", 3.15);
    engine.rootContext()->setContextProperty("listModel", QVariant::fromValue(&listModel));

    QList<QVariantList> list;
    list.append(QVariantList {"Item 1", 3.14});
    list.append(QVariantList {"Item 2", 3.15});
    list.append(QVariantList {"Item 3", 3.16});
    listModel.replace(list);

    //... End of my codes

    engine.load(url);

    return app.exec();
}
