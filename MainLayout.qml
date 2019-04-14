import QtQuick 2.0
import Application 1.0

Rectangle {
    id: root
    anchors.fill: parent;
    color: "black"

    property AppImpl application

    MenuView {
        id: menu
        anchors.right: root.right
        width: 320
        height: root.height
        imageReady: application.isImageReady
    }

    ImageView {
        id: image1
        imageVisible: application.isImageReady
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.leftMargin: 40
        width: 320
        height: 240
        onClicked: application.selectImage()
    }

    Connections {
        target: application
        onImageChanged: image1.imageItem.image = application.image
    }

    Connections {
        target: application
        onImageProcessed: image2.imageItem.image = application.processedImage
    }

    ImageView {
        id:image2
        imageVisible: application.isProcessedImageReady
        anchors.right: menu.left
        anchors.verticalCenter: parent.verticalCenter
        anchors.rightMargin: 40
        emptyText: qsTr("Processed image")
        enableHandCursor: false
        width: 320
        height: 240
    }
}
