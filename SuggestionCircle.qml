import QtQuick 2.0

Item {
    anchors.fill: parent

    property int index

    Rectangle {
        anchors.centerIn: parent
        width: parent.width /2
        height: parent.height / 2
        color: "gray"
        opacity: 0.5
        radius: parent.width * 0.5
    }
}
