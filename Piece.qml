import QtQuick 2.0

Item {
    property var url
    property var index
    anchors.fill: parent
    Image {
        source: url
        anchors.fill: parent
    }

}
