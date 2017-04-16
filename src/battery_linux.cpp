#include "battery_linux.h"

#include <QDebug>

#define	UPOWER_SERVICE             "org.freedesktop.UPower"
#define	UPOWER_PATH                "/org/freedesktop/UPower"
#define	UPOWER_INTERFACE           "org.freedesktop.UPower"
#define	UPOWER_DEVICE_INTERFACE    "org.freedesktop.UPower.Device"
#define	DBUS_PROPERTIES_INTERFACE  "org.freedesktop.DBus.Properties"

UPowerInterface::UPowerInterface(QObject *parent)
    : QDBusAbstractInterface(QLatin1String(UPOWER_SERVICE)
                             , QLatin1String(UPOWER_PATH)
                             , UPOWER_SERVICE
                             , QDBusConnection::systemBus()
                             , parent)
{

}

UPowerInterface::~UPowerInterface()
{

}

QList<QDBusObjectPath> UPowerInterface::enumerateDevices()
{
    QDBusReply<QList<QDBusObjectPath>> reply = call(QLatin1String("EnumerateDevices"));
    return reply.value();
}

UPowerDeviceInterface::UPowerDeviceInterface(const QString &dbusPathName, QObject *parent)
    : QDBusAbstractInterface(QLatin1String(UPOWER_SERVICE)
                             , dbusPathName
                             , UPOWER_DEVICE_INTERFACE
                             , QDBusConnection::systemBus()
                             , parent)
    , m_path(dbusPathName)
{
    m_propInterface = new QDBusInterface(QLatin1String(UPOWER_SERVICE), dbusPathName,
                                         QLatin1String(DBUS_PROPERTIES_INTERFACE),
                                         QDBusConnection::systemBus(),
                                         this);
    updateProperties();
    if (!m_propInterface->connection().connect(QLatin1String(UPOWER_SERVICE),
                                               dbusPathName,
                                               QLatin1String(DBUS_PROPERTIES_INTERFACE),
                                               QLatin1String("PropertiesChanged"),
                                               this, SLOT(updateProperties()))) {
        qDebug() << "Error:" << connection().lastError().message();
    }
}

UPowerDeviceInterface::~UPowerDeviceInterface()
{
    if (!m_propInterface->connection().disconnect(QLatin1String(UPOWER_SERVICE),
                                                  m_path,
                                                  QLatin1String(DBUS_PROPERTIES_INTERFACE),
                                                  QLatin1String("PropertiesChanged"),
                                                  this, SLOT(updateProperties()))) {
        qDebug() << "Error:" << connection().lastError().message();
    }
}

quint16 UPowerDeviceInterface::type()
{
    return m_properties.value("Type", 0).toUInt();
}

quint16 UPowerDeviceInterface::state()
{
    return m_properties.value("State", 0).toUInt();
}

double UPowerDeviceInterface::percentage()
{
    return m_properties.value("Percentage", 0.0).toDouble();
}

qint64 UPowerDeviceInterface::timeToFull()
{
    return m_properties.value("TimeToFull", 0).toLongLong();
}

quint64 UPowerDeviceInterface::timeToEmpty()
{
    return m_properties.value("TimeToEmpty", 0).toLongLong();
}

void UPowerDeviceInterface::updateProperties()
{
    if (m_propInterface && m_propInterface->isValid()) {
        QDBusReply<QVariantMap> r = m_propInterface->call(QLatin1String("GetAll"), QLatin1String(UPOWER_DEVICE_INTERFACE));
        m_properties = r.value();
        qDebug() << m_properties["Percentage"];
        emit changed();
    }
}

BatteryInfoLinux::BatteryInfoLinux(QObject *parent)
    : BatteryInfoPrivate(parent)
    , m_upowerIface(new UPowerInterface(parent))
    , m_batteryIface(nullptr)
{
    if (!m_upowerIface || !m_upowerIface->isValid())
        return;
    foreach (const QDBusObjectPath &device, m_upowerIface->enumerateDevices()) {
        //qDebug() << device.path();
        UPowerDeviceInterface *dev = new UPowerDeviceInterface(device.path(), parent);
        //qDebug() << dev->type();
        if (dev->type() == 2) {
            m_batteryIface = dev;
            onChanged();
            connect(m_batteryIface, &UPowerDeviceInterface::changed,
                    this, &BatteryInfoLinux::onChanged);
            break;
        } else {
            delete dev;
        }
    }
}

void BatteryInfoLinux::onChanged()
{
    if (m_batteryIface->state() == 1)
        setStatus(BatteryInfo::StatusCharging);
    else if (m_batteryIface->state() == 2)
        setStatus(BatteryInfo::StatusDischarging);
    else if (m_batteryIface->state() == 4)
        setStatus(BatteryInfo::StatusFull);
    else
        qWarning() << "Wrong state";
    setPercentage(m_batteryIface->percentage());
    setTimeToFull(m_batteryIface->timeToFull());
    setTimeToEmpty(m_batteryIface->timeToEmpty());
    setLevel(levelForPercentage(percentage()));
    qDebug() << "State: " << m_batteryIface->state();
}
