#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QList>
#include <QvariantMap>
#include <QString>
#include <QThread>

class LoggerWorker;

class Logger: public QObject {
    Q_OBJECT
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

public:
    explicit Logger(QObject *parent = 0);
    ~Logger();
    QString fileName() {return fileName_;}
    void setFileName(const QString &v);
    Q_INVOKABLE void log(const QVariantMap &reading);
    Q_INVOKABLE void flush();

signals:
    void fileNameChanged();

public:
    LoggerWorker *worker_;
    QString fileName_;
    QThread *workerThread_;
};

class LoggerWorker: public QObject {
    Q_OBJECT

public:
    explicit LoggerWorker(QObject *parent = 0);

public slots:
    void setFileName(const QString &v);
    void log(const QVariantMap &reading);
    void flush();

public:
    QString fileName_;
    QList<QVariantMap> readings_;
};

#endif // LOGGER_H
