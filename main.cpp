#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "AppImpl.h"
#include "ImageItem.h"
#include "ImageWrap.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);

    qmlRegisterType<AppImpl>("Application", 1, 0, "AppImpl");
    qmlRegisterType<ImageItem>("Application", 1, 0, "ImageItem");
    qmlRegisterType<ImageWrap>("Application", 1, 0, "ImageWrap");

    QQmlApplicationEngine engine;

    AppImpl* app_impl = new AppImpl;
    engine.rootContext()->setContextProperty("ctxApplication", app_impl);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;


    return app.exec();
}
