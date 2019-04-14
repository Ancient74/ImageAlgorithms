import QtQuick 2.12
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4

QtObject {
    property int fontPointSize: 18
    property color fontColor: "lightgrey"

    property Gradient buttonGradientHovered: Gradient {
        GradientStop { position: 0; color: "#1C172C" }
        GradientStop { position: 1; color: "#332B50" }
    }
    property Gradient buttonGradient: Gradient {
        GradientStop { position: 0; color: "#050020" }
        GradientStop { position: 1; color: "#1F1B36" }
    }
    property Gradient buttonGradientHighlighted: Gradient {
        GradientStop { position: 0; color: "#332B50" }
        GradientStop { position: 1; color: "#1F1B36" }
    }
    property Gradient buttonGradientDisabled: Gradient {
        GradientStop { position: 0; color: Qt.darker("#050020") }
        GradientStop { position: 1; color: Qt.darker("#1F1B36") }
    }

    property int buttonRadius: 4
    property color buttonBorderColor: "grey"
    property int buttonBorderWidth: 1
}
