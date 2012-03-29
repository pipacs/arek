#include <QDebug>
#include <QDateTime>

#include "counter.h"

Counter::Counter(QObject *parent): QObject(parent) {
    accelerometer_ = new QAccelerometer(this);
    accelerometer_->setProperty("alwaysOn", true);
    accelerometer_->setDataRate(20);
    accelerometer_->addFilter(this);
}

Counter::~Counter() {
    accelerometer_->stop();
}

bool Counter::running() {
    return accelerometer_->isActive();
}

void Counter::setRunning(bool v) {
    if (v) {
        if (!accelerometer_->isActive()) {
            accelerometer_->start();
            emit runningChanged();
        }
    } else {
        if (accelerometer_->isActive()) {
            accelerometer_->stop();
            emit runningChanged();
        }
    }
}

bool Counter::filter(QAccelerometerReading *r) {
    reading_["date"] = QDateTime::currentMSecsSinceEpoch();
    reading_["x"] = r->x();
    reading_["y"] = r->y();
    reading_["z"] = r->z();
    emit readingChanged(reading_);
    return true;
}

QVariantMap Counter::reading() {
    return reading_;
}

int Counter::dataRate() {
    return accelerometer_->dataRate();
}

void Counter::setDataRate(int v) {
    accelerometer_->setDataRate(v);
}

QString Counter::version() {
    return AREK_VERSION;
}
