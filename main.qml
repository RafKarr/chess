import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.0
import BoardModels 1.0


ApplicationWindow {

    Material.theme: Material.Dark
    Material.accent: Material.Purple


    visible: true
    width: 560
    height: 560 + menuBar.height
    title: qsTr("Chess")

    minimumHeight: height
    maximumHeight: height

    minimumWidth: width
    maximumWidth: width

    menuBar: NavBar {

    }

    BoardModel {
        id: boardModel
        onNotifyMoveOfPiece: { //Slot to move a piece in the frontend
            console.log("Moving from " + indexFrom + " to " +indexTo );
            var piece;
            for (var i=0;i<board.pieces.length;i++){
                piece = board.pieces[i];
                if (piece.index === indexFrom) {
                    piece.parent = board.children[0].children[indexTo];
                    piece.index = indexTo;
                    break;
                }
            }
        }
        onNotifyTaking: { //Slot to remove a piece in case of taking
            console.log("Removing piece in " + index);
            var piece;
            var indexInArray;
            for (var i=0;i<board.pieces.length;i++){
                piece = board.pieces[i];
                if (piece.index === index) {
                    piece.destroy();
                    indexInArray = board.pieces.indexOf(piece);
                    board.pieces.splice(indexInArray,1);
                    break;
                }
            }
        }
    }

    Board {
        id : board
    }
}
