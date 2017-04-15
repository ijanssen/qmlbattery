#include "battery_emul.h"

#include <QTimer>
#include <QTimeLine>

BatteryInfoEmul::BatteryInfoEmul(QObject *parent)
    : BatteryInfoPrivate(parent)
{
    setPercentage(100.0);
    updateTimes();
    m_timeLine1 = new QTimeLine(30000, this);
    m_timeLine1->setCurveShape(QTimeLine::LinearCurve);
    m_timeLine1->setFrameRange(100, 10);
    connect(m_timeLine1, &QTimeLine::frameChanged, this, &BatteryInfoEmul::onTimeLine1FrameChanged);
    connect(m_timeLine1, &QTimeLine::finished, this, &BatteryInfoEmul::onTimeLine1Finished);
    m_timeLine2 = new QTimeLine(20000, this);
    m_timeLine2->setCurveShape(QTimeLine::LinearCurve);
    m_timeLine2->setFrameRange(10, 100);
    connect(m_timeLine2, &QTimeLine::frameChanged, this, &BatteryInfoEmul::onTimeLine2FrameChanged);
    connect(m_timeLine2, &QTimeLine::finished, this, &BatteryInfoEmul::onTimeLine2Finished);
    QTimer::singleShot(5000, this, &BatteryInfoEmul::startTimeLine1);
}

BatteryInfoEmul::~BatteryInfoEmul()
{

}

void BatteryInfoEmul::startTimeLine1()
{
    m_timeLine1->start();
}

void BatteryInfoEmul::onTimeLine1FrameChanged(int i)
{
    setPercentage(i);
    updateTimes();
}

void BatteryInfoEmul::onTimeLine1Finished()
{
    QTimer::singleShot(5000, this, &BatteryInfoEmul::startTimeLine2);
}

void BatteryInfoEmul::onTimeLine2FrameChanged(int i)
{
    setPercentage(i);
    updateTimes();
}

void BatteryInfoEmul::onTimeLine2Finished()
{
    QTimer::singleShot(5000, this, &BatteryInfoEmul::startTimeLine1);
}

void BatteryInfoEmul::startTimeLine2()
{
    m_timeLine2->start();
}

void BatteryInfoEmul::updateTimes()
{
    setTimeToEmpty(percentage() * 5.0 * 60.0);
    setTimeToFull((100.0 - percentage()) * 2.0 * 60.0);
}
