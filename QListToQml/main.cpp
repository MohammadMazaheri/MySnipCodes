#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "datamodel.hpp"
#include "datamodellist.hpp"

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

    QList<qreal> myList {0.0, 1.1, 2.2, 3.3};
    engine.rootContext()->setContextProperty("myList", QVariant::fromValue(myList));

    DataModel* dataModel = new DataModel("location",20.14,21.54,"green");
    engine.rootContext()->setContextProperty("myData", QVariant::fromValue(dataModel));

    QStringList strList {"H","e","l","l","o"};
    DataModelList* dataModelList = new DataModelList(strList);
    engine.rootContext()->setContextProperty("myDataList", QVariant::fromValue(dataModelList));

    engine.load(url);

    return app.exec();
}
