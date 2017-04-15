#include <QtTest>

#include "../src/batteryinfoprivate.h"

class BatteryInfoTest : public QObject
{
    Q_OBJECT

public:
    BatteryInfoTest();

private Q_SLOTS:
    void testPercentage();
    void testTimeToFull();
    void testTimeToEmpty();

private:
    BatteryInfoPrivate battery;
};

BatteryInfoTest::BatteryInfoTest()
{
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

QTEST_APPLESS_MAIN(BatteryInfoTest)

#include "tst_batteryinfo.moc"
