import QtQuick 2.12
import Application 1.0

Rectangle {
    id:root
    focus: true
    border.color: hovered ? "white" : "lightgrey"
    color: "black"
    border.width: imageVisible ? 0 : 2

    property bool imageVisible: false
    property string emptyText: qsTr("Select image")
    property ImageItem imageItem: item
    property bool hovered: mouseArea.containsMouse
    property bool enableHandCursor: true

    signal clicked();

    ImageItem {
        id: item
        width: root.width
        height: root.height
        visible: imageVisible
    }

    Theme { id:theme }

    Text {
        anchors.centerIn: parent
        text: emptyText
        font.pointSize: theme.fontPointSize
        color: theme.fontColor
        visible: !imageVisible
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        hoverEnabled: true
        onClicked: root.clicked()
        cursorShape: enableHandCursor ? Qt.PointingHandCursor : Qt.ArrowCursor
    }
}
