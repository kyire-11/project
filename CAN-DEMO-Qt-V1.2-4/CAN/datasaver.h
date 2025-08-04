#ifndef DATASAVER_H
#define DATASAVER_H

#include <QObject>
#include <QDateTime>
#include <QString>
#include <QMutex>
#include <QFile>

class QTableWidget;

class datasaver : public QObject
{
    Q_OBJECT
public:
    explicit datasaver( QObject *parent = nullptr);//QTableWidget *tableWidget,
    // ~datasaver();

    void checkAndChangeFile();

    void setSavePath(const QString &path);
    void saveData(const QList<QStringList> &data);

signals:
    void saveFinished();
    void errorOccurred(const QString &errorMessage);

private:
    QString savePath;
    QString currentSavePath;
    QDateTime lastSaveTime;

};

#endif // DATASAVER_H




