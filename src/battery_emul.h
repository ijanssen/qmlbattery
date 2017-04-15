#ifndef BATTERY_EMUL_H
#define BATTERY_EMUL_H

#include "batteryinfoprivate.h"

class QTimeLine;

class BatteryInfoEmul : public BatteryInfoPrivate
{
    Q_OBJECT
public:
    explicit BatteryInfoEmul(QObject *parent = nullptr);
    ~BatteryInfoEmul();

private slots:
    void startTimeLine1();
    void onTimeLine1FrameChanged(int i);
    void onTimeLine1Finished();
    void onTimeLine2FrameChanged(int i);
    void onTimeLine2Finished();
    void startTimeLine2();

private:
    void updateTimes();

    QTimeLine *m_timeLine1;
    QTimeLine *m_timeLine2;
};

#endif // BATTERY_EMUL_H
