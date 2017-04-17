import QtQuick 2.0
import org.test.batteryinfo 1.0

Rectangle {
    color: '#4f2f31'
    width: 300
    height: 40

    function getTime(secs) {
        var m = Math.floor((secs + 30) / 60)
        var h = Math.floor(m / 60)
        m %= 60
        if (m < 10)
            m = '0' + m;
        return h + ':' + m
    }

    function getStatusText() {
        if (batteryInfo.status === BatteryInfo.StatusFull)
            return qsTr('CHARGED')
        if (batteryInfo.status === BatteryInfo.StatusDischarging)
            return qsTr('BATTERY: ') + getTime(batteryInfo.timeToEmpty) + ' ' + qsTr('LEFT')
        if (batteryInfo.status === BatteryInfo.StatusCharging)
            return qsTr('CHARGING: ') + getTime(batteryInfo.timeToFull) + ' ' + qsTr('LEFT')
        return ''
    }

    Text {
        anchors {
            right: parent.right
            rightMargin: 20
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: 16
        color: 'white'
        text: Math.round(batteryInfo.percentage) + qsTr("%")
    }

    Text {
        anchors {
            left: parent.left
            leftMargin: 20
            verticalCenter: parent.verticalCenter
        }
        font.pixelSize: 16
        font.bold: true
        color: '#948283'
        text: getStatusText()
    }
}
