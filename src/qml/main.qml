import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import org.test.batteryinfo 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Battery")

    function getTime(secs) {
        var m = Math.floor((secs + 30) / 60)
        var h = Math.floor(m / 60)
        m %= 60
        if (m < 10)
            m = '0' + m;
        return h + ':' + m
    }

    BatteryInfo {
        id: batteryInfo
    }

    Column {
        anchors.centerIn: parent
        Label {
            text: qsTr("Status: ") + batteryInfo.status
        }
        Label {
            text: qsTr("Level: ") + batteryInfo.level
        }
        Label {
            text: qsTr("Percentage: ") + batteryInfo.percentage + qsTr("%")
        }
        Label {
            text: qsTr("Time To Empty: ") + getTime(batteryInfo.timeToEmpty)
        }
        Label {
            text: qsTr("Time To Full: ") + getTime(batteryInfo.timeToFull)
        }
    }
}
