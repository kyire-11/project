#include "datasaver.h"
#include <QTableWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QMutex>

//QTableWidget *tableWidget,
datasaver::datasaver(QObject *parent)
    : QObject{parent}
{}






void datasaver::setSavePath(const QString &path)
{
    savePath = path;
    currentSavePath = path;
    lastSaveTime = QDateTime::currentDateTime();
}

void datasaver::checkAndChangeFile()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    if (lastSaveTime.secsTo(currentTime) >= 600) { // 10分钟 = 600秒
        QString baseName = savePath.left(savePath.lastIndexOf('/'));
        // QString extension = savePath.mid(savePath.lastIndexOf('.'));
        QString newFileName = baseName + "/" + currentTime.toString("yyyy-MM-dd_hh-mm-ss") + ".txt";
        currentSavePath = newFileName;
        lastSaveTime = currentTime;
    }
}

void datasaver::saveData(const QList<QStringList> &data)
{
    checkAndChangeFile();
    QFile file(currentSavePath);
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto &row : data) {
            for (int i = 0; i < row.size(); ++i) {
                out << row[i];
                if (i < row.size() - 1) {
                    out << "\t";
                }
            }
            out << "\n";
        }
        file.close();
        emit saveFinished();
    } else {
        emit errorOccurred("无法打开保存文件！");
    }
}










