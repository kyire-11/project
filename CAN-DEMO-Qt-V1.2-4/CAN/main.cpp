#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>


int main(int argc, char *argv[])
{



    qputenv("QT_SCALE_FACTOR", "1");



    // // 禁用Qt的自动DPI缩放
    QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);


    qRegisterMetaType<QVector<quint16>>("QVector<quint16>");
    qRegisterMetaType<QModbusDevice::Error>("QModbusDevice::Error");
    qRegisterMetaType<QModbusDevice::State>("QModbusDevice::State");


    QApplication a(argc, argv);
    MainWindow w;

    w.show();



    return a.exec();
}
