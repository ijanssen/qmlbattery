import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import org.test.batteryinfo 1.0

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: qsTr("Battery")

    BatteryInfo {
        id: batteryInfo
    }

    Column {
        anchors.centerIn: parent
        Label {
            text: qsTr("Status: ") + batteryInfo.status
        }
        Label {
            text: qsTr("Percentage: ") + batteryInfo.percentage + qsTr("%")
        }
        Label {
            text: qsTr("Time To Empty: ") + batteryInfo.timeToEmpty
        }
        Label {
            text: qsTr("Time To Full: ") + batteryInfo.timeToFull
        }
    }
}
