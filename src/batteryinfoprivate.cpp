#include "batteryinfoprivate.h"

BatteryInfoPrivate::BatteryInfoPrivate(QObject *parent)
    : QObject(parent)
{

}

BatteryInfo::Status BatteryInfoPrivate::status() const
{
    return m_status;
}

BatteryInfo::Level BatteryInfoPrivate::level() const
{
    return m_level;
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

void BatteryInfoPrivate::setStatus(BatteryInfo::Status status)
{
    if (status == m_status)
        return;
    m_status = status;
    emit statusChanged(m_status);
}

void BatteryInfoPrivate::setLevel(BatteryInfo::Level level)
{
    if (level == m_level)
        return;
    m_level = level;
    emit levelChanged(m_level);
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

BatteryInfo::Level BatteryInfoPrivate::levelForPercentage(double p) const
{
    if (p == 0.0)
        return BatteryInfo::LevelEmpty;
    else if (p <= 15.0)
        return BatteryInfo::LevelCritical;
    else if (p <= 40.0)
        return BatteryInfo::LevelLow;
    else if (p <= 70.0)
        return BatteryInfo::LevelMedium;
    else if (p < 100.0)
        return BatteryInfo::LevelHigh;
    return BatteryInfo::LevelFull;
}
