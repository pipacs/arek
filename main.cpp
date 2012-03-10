#include <QtGui/QApplication>
#include <QtDeclarative>
#include <QDebug>

#include "qmlapplicationviewer.h"
#include "counter.h"
#include "logger.h"

Q_DECL_EXPORT int main(int argc, char *argv[]) {
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    Counter *counter = new Counter();
    Logger *logger = new Logger();

    QmlApplicationViewer viewer;
    viewer.rootContext()->setContextProperty("counter", counter);
    viewer.rootContext()->setContextProperty("logger", logger);
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/arek/main.qml"));
    viewer.showExpanded();

    int ret = app->exec();

    delete logger;
    delete counter;
    return ret;
}
