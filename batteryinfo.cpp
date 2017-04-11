#include "batteryinfo.h"

BatteryInfo::BatteryInfo(QObject *parent)
    : QObject(parent)
{

}

BatteryInfo::Status BatteryInfo::status() const
{
    return Status1;
}

double BatteryInfo::percentage() const
{
    return 48.0;
}

quint64 BatteryInfo::timeToFull() const
{
    return 60 * 123;
}

quint64 BatteryInfo::timeToEmpty() const
{
    return 60 * 43;
}
