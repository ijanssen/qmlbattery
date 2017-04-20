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

    Rectangle {
        anchors.fill: parent
        Rectangle {
            id: panel
            anchors.right: parent.right
            width: 40
            z: 100
            height: parent.height
            color: '#3f2929'
            BatteryIndicator {
                id: button
                width: 40
                height: 40
                anchors.left: parent.left
                y: 100
                enabled: batteryInfo.status !== BatteryInfo.StatusMissing
                img: batteryInfo.status === BatteryInfo.StatusFull ? 'battery-100' : (
                     batteryInfo.status === BatteryInfo.StatusMissing ? 'battery-missing' : (
                     batteryInfo.status === BatteryInfo.StatusDischarging ?
                                   icons[batteryInfo.level] : cicons[batteryInfo.level]))
                onClicked: batteryPopup.visible = !batteryPopup.visible
            }
        }

        BatteryPopup {
            id: batteryPopup
            anchors.right: panel.left
            y : button.y
            visible: false
        }

        MouseArea {
            anchors.fill: parent
            onClicked: batteryPopup.visible = false
        }

    }

    /*Column {
        anchors.centerIn: parent
        Label {
            text: qsTr("Status: ") + batteryInfo.status
        }
        Label {
            text: qsTr("Level: ") + batteryInfo.level
        }
        Label {
            text: qsTr("Percentage: ") + Math.round(batteryInfo.percentage) + qsTr("%")
        }
        Label {
            text: qsTr("Time To Empty: ") + getTime(batteryInfo.timeToEmpty)
        }
        Label {
            text: qsTr("Time To Full: ") + getTime(batteryInfo.timeToFull)
        }
    }*/

    property variant icons: []
    property variant cicons: []

    Component.onCompleted: {
        icons[BatteryInfo.LevelCritical] = 'battery-caution'
        icons[BatteryInfo.LevelLow] = 'battery-040'
        icons[BatteryInfo.LevelMedium] = 'battery-060'
        icons[BatteryInfo.LevelHigh] = 'battery-080'
        icons[BatteryInfo.LevelFull] = 'battery-080'
        cicons[BatteryInfo.LevelCritical] = 'battery-charging-caution'
        cicons[BatteryInfo.LevelLow] = 'battery-charging-040'
        cicons[BatteryInfo.LevelMedium] = 'battery-charging-060'
        cicons[BatteryInfo.LevelHigh] = 'battery-charging-080'
        cicons[BatteryInfo.LevelFull] = 'battery-charging-080'
    }
}
