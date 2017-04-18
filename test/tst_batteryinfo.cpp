#include <QtTest>

#include "../src/batteryinfoprivate.h"

class BatteryInfoTest : public QObject
{
    Q_OBJECT

public:
    BatteryInfoTest();

private Q_SLOTS:
    void testStatus();
    void testLevel();
    void testPercentage();
    void testTimeToFull();
    void testTimeToEmpty();
    void testLevelForPercentage();

private:
    BatteryInfoPrivate battery;
};

BatteryInfoTest::BatteryInfoTest()
{
}

void BatteryInfoTest::testStatus()
{
    battery.setStatus(BatteryInfo::StatusFull);
    QCOMPARE(battery.status(), BatteryInfo::StatusFull);
    battery.setStatus(BatteryInfo::StatusCharging);
    QCOMPARE(battery.status(), BatteryInfo::StatusCharging);
    battery.setStatus(BatteryInfo::StatusDischarging);
    QCOMPARE(battery.status(), BatteryInfo::StatusDischarging);
    battery.setStatus(BatteryInfo::StatusMissing);
    QCOMPARE(battery.status(), BatteryInfo::StatusMissing);
}

void BatteryInfoTest::testLevel()
{
    battery.setLevel(BatteryInfo::LevelEmpty);
    QCOMPARE(battery.level(), BatteryInfo::LevelEmpty);
    battery.setLevel(BatteryInfo::LevelCritical);
    QCOMPARE(battery.level(), BatteryInfo::LevelCritical);
    battery.setLevel(BatteryInfo::LevelLow);
    QCOMPARE(battery.level(), BatteryInfo::LevelLow);
    battery.setLevel(BatteryInfo::LevelMedium);
    QCOMPARE(battery.level(), BatteryInfo::LevelMedium);
    battery.setLevel(BatteryInfo::LevelHigh);
    QCOMPARE(battery.level(), BatteryInfo::LevelHigh);
    battery.setLevel(BatteryInfo::LevelFull);
    QCOMPARE(battery.level(), BatteryInfo::LevelFull);
}

void BatteryInfoTest::testPercentage()
{
    battery.setPercentage(56.2);
    QCOMPARE(battery.percentage(), 56.2);
    battery.setPercentage(0.0);
    QCOMPARE(battery.percentage(), 0.0);
    battery.setPercentage(100.0);
    QCOMPARE(battery.percentage(), 100.0);
    battery.setPercentage(77.77);
    QCOMPARE(battery.percentage(), 77.77);
}

void BatteryInfoTest::testTimeToFull()
{
    battery.setTimeToFull(244456);
    QCOMPARE(battery.timeToFull(), 244456ULL);
    battery.setTimeToFull(0);
    QCOMPARE(battery.timeToFull(), 0ULL);
    battery.setTimeToFull(9999999999ULL);
    QCOMPARE(battery.timeToFull(), 9999999999ULL);
    battery.setTimeToFull(1);
    QCOMPARE(battery.timeToFull(), 1ULL);
    battery.setTimeToFull(999);
    QCOMPARE(battery.timeToFull(), 999ULL);

}

void BatteryInfoTest::testTimeToEmpty()
{
    battery.setTimeToEmpty(244456);
    QCOMPARE(battery.timeToEmpty(), 244456ULL);
    battery.setTimeToEmpty(1);
    QCOMPARE(battery.timeToEmpty(), 1ULL);
    battery.setTimeToEmpty(0);
    QCOMPARE(battery.timeToEmpty(), 0ULL);
    battery.setTimeToEmpty(9999999999ULL);
    QCOMPARE(battery.timeToEmpty(), 9999999999ULL);
    battery.setTimeToEmpty(10000ULL);
    QCOMPARE(battery.timeToEmpty(), 10000ULL);
}

void BatteryInfoTest::testLevelForPercentage()
{
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(11.0), BatteryInfo::LevelCritical);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(0.0), BatteryInfo::LevelEmpty);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(100.0), BatteryInfo::LevelFull);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(31.0), BatteryInfo::LevelLow);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(55.5), BatteryInfo::LevelMedium);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(99.9), BatteryInfo::LevelHigh);
    QCOMPARE(BatteryInfoPrivate::levelForPercentage(90.0), BatteryInfo::LevelHigh);
}

QTEST_APPLESS_MAIN(BatteryInfoTest)

#include "tst_batteryinfo.moc"
