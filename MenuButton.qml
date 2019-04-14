import QtQuick 2.12
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

Button {
    id:root

    Layout.fillWidth: true
    Layout.margins: 10

    Theme { id:theme }

    hoverEnabled: enabled

    background: Rectangle {
                radius: theme.buttonRadius
                gradient: enabled ?
                              root.hovered ?
                                  root.pressed ?
                                      theme.buttonGradientHighlighted :
                               theme.buttonGradientHovered :
                            theme.buttonGradient :
                        theme.buttonGradientDisabled

                border.color: theme.buttonBorderColor
                border.width: theme.buttonBorderWidth
        }

    contentItem: Text {
        text: root.text
        color: theme.fontColor
        font.pointSize: theme.fontPointSize
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}
