#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <boardmodel.h>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

//    qmlRegisterUncreatableType<BoardModel>("BoardModels",1,0,"BoardModel",QStringLiteral("Can't create this type in QML"));
    qmlRegisterType<BoardModel>("BoardModels",1,0,"BoardModel");
    qmlRegisterUncreatableMetaObject(
      enums::staticMetaObject, // static meta object
      "BoardModels",                // import statement (can be any string)
      1, 0,                          // major and minor version of the import
      "Pieces",                 // name in QML (does not have to match C++ name)
      "Error: only enums"            // error in case someone tries to create a MyNamespace object
    );


    BoardModel boardModel;

    QQmlApplicationEngine engine;
//    engine.rootContext()->setContextProperty(QStringLiteral("boardModel"),&boardModel);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
