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
            height: parent.height
            color: '#3f2929'
            Rectangle {
                id: button
                width: 40
                height: 40
                anchors.left: parent.left
                y: 100
                color: batteryInfo.status === BatteryInfo.StatusMissing ? 'cyan' : 'lightGray'
                MouseArea {
                    anchors.fill: parent
                    enabled: batteryInfo.status !== BatteryInfo.StatusMissing
                    onClicked: batteryPopup.visible = !batteryPopup.visible
                }
            }
        }

        BatteryPopup {
            id: batteryPopup
            anchors.right: panel.left
            y : button.y
            visible: false
        }

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
            text: qsTr("Percentage: ") + Math.round(batteryInfo.percentage) + qsTr("%")
        }
        Label {
            text: qsTr("Time To Empty: ") + getTime(batteryInfo.timeToEmpty)
        }
        Label {
            text: qsTr("Time To Full: ") + getTime(batteryInfo.timeToFull)
        }
    }
}
