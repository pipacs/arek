#ifndef COUNTER_H
#define COUNTER_H

#include <sys/time.h>

#include <QObject>
#include <QVariantHash>
#include <QAccelerometer>
#include <qplatformdefs.h>

QTM_USE_NAMESPACE

/// Accelerometer wrapper.
class Counter: public QObject, public QAccelerometerFilter {
    Q_OBJECT

    /// Start/stop measuring.
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

    /// Measurement frequency.
    Q_PROPERTY(int dataRate READ dataRate WRITE setDataRate NOTIFY dataRateChanged)

    /// Reading: a dictionnary of "date":date, "x":real, "y":real, "z":real.
    Q_PROPERTY(QVariantMap reading READ reading NOTIFY readingChanged)

public:
    explicit Counter(QObject *parent = 0);
    ~Counter();
    bool running();
    void setRunning(bool v);
    int dataRate();
    void setDataRate(int v);
    QVariantMap reading();

signals:
    void runningChanged();
    void dataRateChanged();
    void readingChanged(QVariantMap r);

private slots:

    // Override of QAcclerometerFilter::filter(QAccelerometerReading*)
    bool filter(QAccelerometerReading* r);

public:
    QAccelerometer *accelerometer_;
    QVariantMap reading_;
};

#endif // COUNTER_H
