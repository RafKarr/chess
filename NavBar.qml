import QtQuick 2.0
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.0

ToolBar {
    RowLayout {
        ToolButton {
            text: "Set Pieces"
            onClicked: board.setPieces()
        }
        ToolButton {
            text: "Clean Board"
            onClicked: board.cleanBoard()
        }
    }
}
