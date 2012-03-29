#include <QFile>
#include <QDateTime>
#include <QDebug>
#include <QDesktopServices>
#include <QTextStream>

#include "logger.h"

const int BATCH_SIZE = 11;

Logger::Logger(QObject *parent): QObject(parent) {
    worker_ = new LoggerWorker();
    workerThread_ = new QThread(this);
    worker_->moveToThread(workerThread_);
    workerThread_->start(QThread::LowestPriority);
}

Logger::~Logger() {
    workerThread_->quit();
    workerThread_->wait();
    delete worker_;
}

void Logger::setFileName(const QString &v) {
    fileName_ = v;
    QMetaObject::invokeMethod(worker_, "setFileName", Q_ARG(QString, v));
    emit fileNameChanged();
}

void Logger::log(const QVariantMap &reading) {
    QMetaObject::invokeMethod(worker_, "log", Q_ARG(QVariantMap, reading));
}

void Logger::flush() {
    QMetaObject::invokeMethod(worker_, "flush");
}

LoggerWorker::LoggerWorker(QObject *parent): QObject(parent) {
}

void LoggerWorker::setFileName(const QString &v) {
    flush();
    if (v.isEmpty()) {
        fileName_ = v;
    } else {
        QDateTime now = QDateTime::currentDateTime();
        fileName_ = QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation);
        fileName_.append("/");
        fileName_.append(now.toString("yyyyMMddhhmmss"));
        fileName_.append("-");
        fileName_.append(v);
        fileName_.append(".csv");
    }
   qDebug() << "LoggerWorker::setFileName" << v << "->" << fileName_;
}

void LoggerWorker::log(const QVariantMap &reading) {
    readings_.append(reading);
    if (readings_.length() > BATCH_SIZE) {
        flush();
    }
}

void LoggerWorker::flush() {
    if (fileName_.length()) {
        QFile f(fileName_);
        if (!f.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qCritical() << "LoggerWorker::flush: Failed to open" << fileName_;
            return;
        }
        QTextStream out(&f);
        foreach (QVariantMap r, readings_) {
            out << r.value("date").toLongLong() << "," << r.value("x").toReal() << "," << r.value("y").toReal() << "," << r.value("z").toReal() << endl;
        }
        f.close();
    }
    readings_.clear();
}
