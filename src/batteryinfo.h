#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#include <QObject>

class BatteryInfoPrivate;

class BatteryInfo : public QObject
{
    Q_OBJECT

    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    Q_PROPERTY(double percentage READ percentage NOTIFY percentageChanged)
    Q_PROPERTY(quint64 timeToFull READ timeToFull NOTIFY timeToFullChanged)
    Q_PROPERTY(quint64 timeToEmpty READ timeToEmpty NOTIFY timeToEmptyChanged)

    Q_ENUMS(Status)
public:
    enum Status {
        Status0,
        Status1
    };

    explicit BatteryInfo(QObject *parent = 0);

    Status status() const;
    double percentage() const;
    quint64 timeToFull() const;
    quint64 timeToEmpty() const;

signals:
    void statusChanged(Status status);
    void percentageChanged(double percentage);
    void timeToFullChanged(quint64 timeToFull);
    void timeToEmptyChanged(quint64 timeToEmpty);

private:
    BatteryInfoPrivate *d_ptr;
};

#endif // BATTERYINFO_H
