#include "batteryinfo.h"

#include "battery_linux.h"
#include "battery_emul.h"
#include "batteryinfoprivate.h"

BatteryInfo::BatteryInfo(QObject *parent)
    : QObject(parent)
#ifdef LINUX
    , d_ptr(new BatteryInfoLinux(this))
#elif EMUL
    , d_ptr(new BatteryInfoEmul(this))
#else
    , d_ptr(new BatteryInfoPrivate(this))
#endif

{
    connect(d_ptr, &BatteryInfoPrivate::statusChanged, this, &BatteryInfo::statusChanged);
    connect(d_ptr, &BatteryInfoPrivate::levelChanged, this, &BatteryInfo::levelChanged);
    connect(d_ptr, &BatteryInfoPrivate::percentageChanged, this, &BatteryInfo::percentageChanged);
    connect(d_ptr, &BatteryInfoPrivate::timeToFullChanged, this, &BatteryInfo::timeToFullChanged);
    connect(d_ptr, &BatteryInfoPrivate::timeToEmptyChanged, this, &BatteryInfo::timeToEmptyChanged);
}

BatteryInfo::Status BatteryInfo::status() const
{
    return d_ptr->status();
}

BatteryInfo::Level BatteryInfo::level() const
{
    return d_ptr->level();
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
