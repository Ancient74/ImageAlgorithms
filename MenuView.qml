import QtQuick 2.0
import QtQuick.Layouts 1.3


Rectangle {
    color: "#06001A"
    id: root
    border.color: "lightgrey"
    border.width: 1
    Theme { id: theme }

    property bool imageReady: false

    ColumnLayout {
        id: layout
        spacing: 8
        width: root.width

        Text {
            text: qsTr("Main Menu")
            color: theme.fontColor
            font.pointSize: theme.fontPointSize
            Layout.alignment: Qt.AlignHCenter
        }

        MenuButton {
            text: qsTr("Review")
            enabled: imageReady
        }

    }

}

