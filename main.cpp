#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <boardmodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<BoardModel>("BoardModels",1,0,"BoardModel"); //Register Board model in QML
    qmlRegisterUncreatableMetaObject(
      enums::staticMetaObject,
      "BoardModels",
      1, 0,
      "Pieces",
      "Error: only enums"
    ); //Registers pieces enum in QML


    BoardModel boardModel;

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
