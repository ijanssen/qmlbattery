#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#include <QObject>

class BatteryInfoPrivate;
/*!
 * \brief Battery information class
 */
class BatteryInfo : public QObject
{
    Q_OBJECT

    /*!
     * \brief Battery status
     *  StatusFull - battery charged
     *  StatusCharging - battery is charging
     *  StatusDischarging - battery is discharging
     *  StatusMissing - there is no battery
     */
    Q_PROPERTY(Status status READ status NOTIFY statusChanged)
    /*!
     * \brief Battery charge level
     *  LevelEmpty     0% charge
     *  LevelCritical  <= 15%
     *  LevelLow       <= 40%
     *  LevelMedium    <= 70%
     *  LevelHigh      < 100%
     *  LevelFull   full charge, 100%
     */
    Q_PROPERTY(Level level READ level NOTIFY levelChanged)
    /*!
     * \brief percentage of charge level
     */
    Q_PROPERTY(double percentage READ percentage NOTIFY percentageChanged)
    /*!
     * \brief Time in seconds for 100% charge
     */
    Q_PROPERTY(quint64 timeToFull READ timeToFull NOTIFY timeToFullChanged)
    /*!
     * \brief Time in seconds for full discharged
     */
    Q_PROPERTY(quint64 timeToEmpty READ timeToEmpty NOTIFY timeToEmptyChanged)

    Q_ENUMS(Status)
    Q_ENUMS(Level)
public:
    enum Status {
        StatusFull,
        StatusCharging,
        StatusDischarging,
        StatusMissing
    };
    enum Level {
        LevelEmpty,
        LevelCritical,
        LevelLow,
        LevelMedium,
        LevelHigh,
        LevelFull
    };

    explicit BatteryInfo(QObject *parent = 0);

    Status status() const;
    Level level() const;
    double percentage() const;
    quint64 timeToFull() const;
    quint64 timeToEmpty() const;

signals:
    void statusChanged(Status status);
    void levelChanged(Level level);
    void percentageChanged(double percentage);
    void timeToFullChanged(quint64 timeToFull);
    void timeToEmptyChanged(quint64 timeToEmpty);

private:
    BatteryInfoPrivate *d_ptr;
};

#endif // BATTERYINFO_H
