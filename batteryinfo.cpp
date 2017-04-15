#include "batteryinfo.h"

#include "battery_linux.h"
#include "battery_emul.h"
#include "batteryinfoprivate.h"

BatteryInfo::BatteryInfo(QObject *parent)
    : QObject(parent)
    //, d_ptr(new BatteryInfoPrivate(this))
    //, d_ptr(new BatteryInfoLinux(this))
    , d_ptr(new BatteryInfoEmul(this))
{    connect(d_ptr, &BatteryInfoPrivate::percentageChanged, this, &BatteryInfo::percentageChanged);
    connect(d_ptr, &BatteryInfoPrivate::timeToFullChanged, this, &BatteryInfo::timeToFullChanged);
    connect(d_ptr, &BatteryInfoPrivate::timeToEmptyChanged, this, &BatteryInfo::timeToEmptyChanged);
}

BatteryInfo::Status BatteryInfo::status() const
{
    return Status1;
}

double BatteryInfo::percentage() const
{
    return d_ptr->percentage();
}

quint64 BatteryInfo::timeToFull() const
{
    return d_ptr->timeToFull();
}

quint64 BatteryInfo::timeToEmpty() const
{
    return d_ptr->timeToEmpty();
}
