#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "dbinterface.hpp"

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

    QString dbPath = QCoreApplication::applicationDirPath() + "/myDB.db";
    DbInterface dbInterface(dbPath, &engine);
    engine.rootContext()->setContextProperty("dbInterface", QVariant::fromValue(&dbInterface));

    dbInterface.append("Sql Item 1", 3.14);
    qDebug()<<"sql error:"<<dbInterface.getLastError();
    dbInterface.refresh("SELECT * FROM tblTest");

    //... End of my codes

    engine.load(url);

    return app.exec();
}
