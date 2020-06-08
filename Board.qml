import QtQuick 2.0
import QtQuick.Layouts 1.3
import BoardModels 1.0

Item {

    property var circles : []
    property var indexClicked: -1
    property var pieces : []


    function setPieces(){

        boardModel.resetPieces();
        cleanBoard();

        var component = Qt.createComponent("Piece.qml");;
        var object;
        var piece;

        for (let i = 0; i < 64 ; i++) {
            piece = boardModel.getPiece(i);

            switch(piece){
            case Pieces.BLACK_ROOK:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_rook.png"});
                break;
            case Pieces.BLACK_KNIGHT:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_knight.png"});
                break;
            case Pieces.BLACK_BISHOP:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_bishop.png"});
                break;
            case Pieces.BLACK_QUEEN:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_queen.png"});
                break;
            case Pieces.BLACK_KING:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_king.png"});
                break;
            case Pieces.BLACK_PAWN:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/black_pawn.png"});
                break;
            case Pieces.WHITE_ROOK:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_rook.png"});
                break;
            case Pieces.WHITE_KNIGHT:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_knight.png"});
                break;
            case Pieces.WHITE_BISHOP:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_bishop.png"});
                break;
            case Pieces.WHITE_QUEEN:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_queen.png"});
                break;
            case Pieces.WHITE_KING:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_king.png"});
                break;
            case Pieces.WHITE_PAWN:
                object = component.createObject(board.children[0].children[i],{index: i, url:"/img/img/white_pawn.png"});
                break;
            default:
                continue;
            }

            pieces.push(object);
        }
    }

    function cleanBoard(){
        cleanSuggestions();
        pieces.forEach((element) => {
                           element.destroy();
                       })
        pieces = [];

    }

    function cleanSuggestions(){
        circles.forEach((element) => {
                           element.destroy();
                       })
        circles = [];
    }

    function getColor (index){
        let row = Math.floor(index/8);

        if (row % 2 === 0){
            return index % 2 === 0 ? "#fece9e" : "#d18b47"
        } else {
            return index % 2 === 0 ? "#d18b47" :  "#fece9e"
        }
    }

    function suggestMoves(indexes){
        var component;
        console.log("indexes passed: "+ indexes);
        for (var i=0;i<indexes.length;i++){
            component = Qt.createComponent("SuggestionCircle.qml");
            var object = component.createObject(children[0].children[indexes[i]],{index: indexes[i]});
            circles.push(object);
        }
    }

    Grid {
        rows: 8
        columns: 8

        Repeater {
            model: 64
            Rectangle {
                property var indexSquare: index
                width: 70
                height: 70
                color: getColor(index)
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        var moves;
                        if (indexClicked === -1){ //If there was no piece selected
                            if (boardModel.getPiece(indexSquare) !== Pieces.EMPTY){ //If there's a piece
                                moves = boardModel.getPossibleMoves(indexSquare);
                                if (moves.length !== 0){ //And a move can be done
                                    board.suggestMoves(moves);
                                    indexClicked = indexSquare;
                                }
                            }
                        } else { //If there was a piece previously selected
                            var flag = circles.some(element=> element.index === indexSquare); //Check if possible move is been selected
                            cleanSuggestions();
                            if (flag){ //If it's true, move piece
                                console.log("Index to pass to MovePiece: "+indexClicked+","+indexSquare);
                                boardModel.movePiece(indexClicked,indexSquare);
                                indexClicked == -1;
                            } else {
                                if (boardModel.getPiece(indexSquare) !== Pieces.EMPTY)  { //If a piece is selected
                                    moves = boardModel.getPossibleMoves(indexSquare);
                                    if (moves.length !== 0){ //And a move can be done
                                        board.suggestMoves(moves);
                                        indexClicked = indexSquare;
                                    } else {
                                        indexClicked = -1;
                                    }
                                } else {
                                    indexClicked = -1;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

