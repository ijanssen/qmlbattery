#ifndef BATTERY_LINUX_H
#define BATTERY_LINUX_H

#include <QtDBus>
#include "batteryinfoprivate.h"

class UPowerInterface : public QDBusAbstractInterface
{
    Q_OBJECT

public:
    explicit UPowerInterface(QObject *parent = nullptr);
    ~UPowerInterface();

    QList<QDBusObjectPath> enumerateDevices();
};

class UPowerDeviceInterface : public  QDBusAbstractInterface
{
    Q_OBJECT
public:
    explicit UPowerDeviceInterface(const QString &dbusPathName, QObject *parent = nullptr);
    ~UPowerDeviceInterface();

    quint16 type();
    quint16 state();
    double percentage();
    qint64 timeToFull();
    quint64 timeToEmpty();


signals:
    void changed();

private slots:
    void updateProperties();

private:
    QDBusInterface *m_propInterface;
    QVariantMap m_properties;
    QString m_path;
};

class BatteryInfoLinux : public BatteryInfoPrivate
{
    Q_OBJECT
public:
    explicit BatteryInfoLinux(QObject *parent = nullptr);

protected slots:
    void onChanged();

private:
    UPowerInterface *m_upowerIface;
    UPowerDeviceInterface *m_batteryIface;
};

#endif // BATTERY_LINUX_H
