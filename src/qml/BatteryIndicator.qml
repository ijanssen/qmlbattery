import QtQuick 2.0

Item {
    property string img: 'battery-missing'
    signal clicked()

    Image {
        id: image
        anchors.centerIn: parent
        source: 'qrc:/images/' + parent.img + '.png'
    }
    MouseArea {
        id: area
        anchors.fill: parent

        onClicked: {
            parent.clicked()
        }
    }
}
