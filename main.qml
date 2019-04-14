import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5

import Application 1.0

ApplicationWindow {
    visible: true
    width: 1080
    height: 720
    title: qsTr("Image Algorithms")

    id:root

    property AppImpl application: ctxApplication

    menuBar: MenuBar {
           Menu {
            title: qsTr("&File")
            Action {
                text: qsTr("&Open")
                onTriggered: application.selectImage()
            }
           }
    }

    MainLayout {
        application: root.application
    }

}
