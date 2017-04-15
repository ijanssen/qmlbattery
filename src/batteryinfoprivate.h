#ifndef BATTERYINFOPRIVATE_H
#define BATTERYINFOPRIVATE_H

#include <QObject>

class BatteryInfoPrivate : public QObject
{
    Q_OBJECT
public:
    explicit BatteryInfoPrivate(QObject *parent = nullptr);

    double percentage() const;
    quint64 timeToFull() const;
    quint64 timeToEmpty() const;

    void setPercentage(double percentage);
    void setTimeToFull(quint64 timeToFull);
    void setTimeToEmpty(quint64 timeToEmpty);


signals:
    //void statusChanged(Status status);
    void percentageChanged(double percentage);
    void timeToFullChanged(quint64 timeToFull);
    void timeToEmptyChanged(quint64 timeToEmpty);

private:
    double m_percentage;
    quint64 m_timeToFull;
    quint64 m_timeToEmpty;
};

#endif // BATTERYINFOPRIVATE_H
