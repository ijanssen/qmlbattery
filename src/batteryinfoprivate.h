#ifndef BATTERYINFOPRIVATE_H
#define BATTERYINFOPRIVATE_H

#include <QObject>
#include "batteryinfo.h"

class BatteryInfoPrivate : public QObject
{
    Q_OBJECT
public:
    explicit BatteryInfoPrivate(QObject *parent = nullptr);

    BatteryInfo::Status status() const;
    BatteryInfo::Level level() const;
    double percentage() const;
    quint64 timeToFull() const;
    quint64 timeToEmpty() const;

    void setStatus(BatteryInfo::Status status);
    void setLevel(BatteryInfo::Level level);
    void setPercentage(double percentage);
    void setTimeToFull(quint64 timeToFull);
    void setTimeToEmpty(quint64 timeToEmpty);

    static BatteryInfo::Level levelForPercentage(double p);

signals:
    void statusChanged(BatteryInfo::Status status);
    void levelChanged(BatteryInfo::Level level);
    void percentageChanged(double percentage);
    void timeToFullChanged(quint64 timeToFull);
    void timeToEmptyChanged(quint64 timeToEmpty);

private:
    BatteryInfo::Status m_status;
    BatteryInfo::Level m_level;
    double m_percentage;
    quint64 m_timeToFull;
    quint64 m_timeToEmpty;
};

#endif // BATTERYINFOPRIVATE_H
