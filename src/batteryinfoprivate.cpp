#include "batteryinfoprivate.h"

BatteryInfoPrivate::BatteryInfoPrivate(QObject *parent)
    : QObject(parent)
{

}

double BatteryInfoPrivate::percentage() const
{
    return m_percentage;
}

quint64 BatteryInfoPrivate::timeToFull() const
{
    return m_timeToFull;
}

quint64 BatteryInfoPrivate::timeToEmpty() const
{
    return m_timeToEmpty;
}

void BatteryInfoPrivate::setPercentage(double percentage)
{
    if (percentage == m_percentage)
        return;
    m_percentage = percentage;
    emit percentageChanged(m_percentage);
}

void BatteryInfoPrivate::setTimeToFull(quint64 timeToFull)
{
    if (timeToFull == m_timeToFull)
        return;
    m_timeToFull = timeToFull;
    emit timeToFullChanged(m_timeToFull);
}

void BatteryInfoPrivate::setTimeToEmpty(quint64 timeToEmpty)
{
    if (timeToEmpty == m_timeToEmpty)
        return;
    m_timeToEmpty = timeToEmpty;
    emit timeToEmptyChanged(m_timeToEmpty);
}
