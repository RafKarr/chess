#include "boardmodel.h"
#include <QDebug>
#include <math.h>

BoardModel::BoardModel(QObject *parent) : QObject(parent), squares(64)
{
    resetPieces();
}

void BoardModel::resetPieces()
{
    m_turn = WHITE;
    for (int i = 0;i<64;i++){
        squares[i].setPiece(EMPTY);
    }

    squares[0].setPiece(BLACK_ROOK);
    squares[1].setPiece(BLACK_KNIGHT);
    squares[2].setPiece(BLACK_BISHOP);
    squares[3].setPiece(BLACK_QUEEN);
    squares[4].setPiece(BLACK_KING);
    squares[5].setPiece(BLACK_BISHOP);
    squares[6].setPiece(BLACK_KNIGHT);
    squares[7].setPiece(BLACK_ROOK);

    for (int i=8;i<16;i++){
        squares[i].setPiece(BLACK_PAWN);
    }

    squares[56].setPiece(WHITE_ROOK);
    squares[57].setPiece(WHITE_KNIGHT);
    squares[58].setPiece(WHITE_BISHOP);
    squares[59].setPiece(WHITE_QUEEN);
    squares[60].setPiece(WHITE_KING);
    squares[61].setPiece(WHITE_BISHOP);
    squares[62].setPiece(WHITE_KNIGHT);
    squares[63].setPiece(WHITE_ROOK);

    for (int i=48;i<56;i++){
        squares[i].setPiece(WHITE_PAWN);
    }

}

int BoardModel::getIndex(int x, int y)
{
    return x + 8*y;
}

QVector<int> BoardModel::getIndexes(int index)
{
    QVector<int> returnVector(2);

    returnVector[0] = index % 8;
    returnVector[1] = index / 8;

    return returnVector;
}

QVector<int> BoardModel::getMovevementsOfPawn(piece piece, int x, int y)
{
    QVector<int> returnVector;

    switch (piece) {
    case WHITE_PAWN:
        if (m_turn == WHITE){
            if (y!=0){
                if (checkAvailabilityOfSquare(piece,y-1)==0)
                    returnVector.append(getIndex(x,y-1));
                if (y == 6) {
                    if (checkAvailabilityOfSquare(piece,y-2)==0)
                        returnVector.append(getIndex(x,y-2));
                }
            }
        }
        break;
    case BLACK_PAWN:
        if (m_turn == BLACK){
            if (y != 7){
                if (checkAvailabilityOfSquare(piece,y+1)==0)
                    returnVector.append(getIndex(x,y+1));
                if (y == 1) {
                    if (checkAvailabilityOfSquare(piece,y+2)==0)
                        returnVector.append(getIndex(x,y+2));
                }
            }
        }
        break;
    default:
        break;
    }

    return returnVector;
}

QVector<int> BoardModel::getMovementsOfKnight(piece piece, int x, int y)
{
    QVector<int> returnVector;
    int toAddX;
    int toAddY;
    int newX;
    int newY;

    switch (piece) {

    case WHITE_KNIGHT:
        if (m_turn == BLACK){
            return returnVector;
        }
        break;
    case BLACK_KNIGHT:
        if (m_turn == WHITE){
            return returnVector;
        }
        break;
    default:
        return returnVector;
        break;
    }

    for (int i=0; i<4;i++){
        for (int j=0; j<2;j++){
            toAddX = cos(i * 2* M_PI/4) * 2;
            toAddY = sin(i * 2* M_PI/4) * 2;

            if (toAddX == 0){
                toAddX = (j == 0) ? 1 : -1;
            }

            if (toAddY == 0){
                toAddY = (j == 0) ? 1 : -1;
            }

            newX = x + toAddX;
            newY = y + toAddY;
            if (( newX >= 0) && (newX <= 7)){
                if ((newY >= 0) && (newY <= 7)){

                }
            }

        }
    }

    return returnVector;
}

QVector<int> BoardModel::getMovementsOfBishop(piece piece, int x, int y)
{
    QVector<int> returnVector;
    int toAddX;
    int toAddY;
    int newX;
    int newY;
    int operators[4][2]= {{1,1},{1,-1},{-1,1},{-1,-1}};


    switch (piece) {

    case WHITE_BISHOP:
        if (m_turn == BLACK){
            return returnVector;
        }
        break;
    case BLACK_BISHOP:
        if (m_turn == WHITE){
            return returnVector;
        }
        break;
    default:
        return returnVector;
        break;
    }

    for (int i=0; i<4; i++){
        toAddX = 0;
        toAddY = 0;
        while(true){
            toAddX += operators[i][0];
            toAddY += operators[i][1];
            newX = x + toAddX;
            newY = y + toAddY;
            if (( newX >= 0) && (newX <= 7)){
                if ((newY >= 0) && (newY <= 7)){
                    returnVector.append(getIndex(newX,newY));
                    continue;
                }
            }
            break;
        }
    }

    return returnVector;

}

QVector<int> BoardModel::getMovementsOfRook(piece piece, int x, int y)
{
    QVector<int> returnVector;
    int toAddX;
    int toAddY;
    int newX;
    int newY;
    int operators[4][2]= {{1,0},{0,1},{-1,0},{0,-1}};


    switch (piece) {

    case WHITE_ROOK:
        if (m_turn == BLACK){
            return returnVector;
        }
        break;
    case BLACK_ROOK:
        if (m_turn == WHITE){
            return returnVector;
        }
        break;
    default:
        return returnVector;
        break;
    }

    for (int i=0; i<4; i++){
        toAddX = 0;
        toAddY = 0;
        while(true){
            toAddX += operators[i][0];
            toAddY += operators[i][1];
            newX = x + toAddX;
            newY = y + toAddY;
            if (( newX >= 0) && (newX <= 7)){
                if ((newY >= 0) && (newY <= 7)){
                    returnVector.append(getIndex(newX,newY));
                    continue;
                }
            }
            break;
        }
    }

    return returnVector;

}

QVector<int> BoardModel::getMovementOfQueen(piece piece, int x, int y)
{
    QVector<int> returnVector;

    switch (piece) {

    case WHITE_QUEEN:
        if (m_turn == BLACK){
            return returnVector;
        }
        returnVector.append(getMovementsOfBishop(WHITE_BISHOP,x,y));
        returnVector.append(getMovementsOfRook(WHITE_ROOK,x,y));
        return returnVector;
    case BLACK_QUEEN:
        returnVector.append(getMovementsOfBishop(BLACK_BISHOP,x,y));
        returnVector.append(getMovementsOfRook(BLACK_ROOK,x,y));
        return returnVector;
    default:
        return returnVector;
        break;
    }
}

QVector<int> BoardModel::getMovementOfKing(piece piece, int x, int y)
{
    QVector<int> returnVector;
    int newX;
    int newY;
    int operators[8][2]= {{1,0},{0,1},{-1,0},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}};


    switch (piece) {

    case WHITE_KING:
        if (m_turn == BLACK){
            return returnVector;
        }
        break;
    case BLACK_KING:
        if (m_turn == WHITE){
            return returnVector;
        }
        break;
    default:
        return returnVector;
        break;
    }

    for (int i=0; i<8; i++){
        newX = x + operators[i][0];
        newY = y + operators[i][1];
        if (( newX >= 0) && (newX <= 7)){
            if ((newY >= 0) && (newY <= 7)){
                returnVector.append(getIndex(newX,newY));
            }
        }
    }
    return returnVector;
}


/** This function checks if the square is empty, if it's full by a takeable piece or if it's occupied by a non takeable piece
 * @brief BoardModel::checkAvailabilityOfSquare
 * @param piece
 * @param index
 * @return -1 if occupied by a non takeable piece, 0 if square is empty, 1 if it's occupied by a takeable piece. Return -2 if error
 */
int BoardModel::checkAvailabilityOfSquare(piece piece, int index)
{
    enum piece checkedSquare = squares[index].getPiece();

    if (checkedSquare == EMPTY) return 0;

    if ((piece >= 1) && (piece <= 6)) { //If piece is white
            if (checkedSquare >= 7 && checkedSquare <= 11) {
                return 1;
            } else {
                return -1;
            }
    } else {
        if ((piece >= 7) && (piece <= 12)){ //If piece is black
            if (checkedSquare >= 1 && checkedSquare <= 5) {
                return 1;
            } else {
                return -1;
            }
        }
    }

    return -2;

}


void BoardModel::changeTurn()
{
    if (m_turn == WHITE){
        m_turn = BLACK;
    } else {
        m_turn = WHITE;
    }
}

int BoardModel::getPiece(int index)
{
    return squares[index].getPiece();
}

QVector<int> BoardModel::getPossibleMoves(int index)
{
    piece piece = squares[index].getPiece();
    QVector<int> returnVector;
    QVector<int> indexes = getIndexes(index);

    switch(piece){
    case BLACK_ROOK:
        returnVector = getMovementsOfRook(BLACK_ROOK,indexes[0],indexes[1]);
        break;
    case BLACK_KNIGHT:
        returnVector = getMovementsOfKnight(BLACK_KNIGHT,indexes[0],indexes[1]);
         break;
    case BLACK_BISHOP:
        returnVector = getMovementsOfBishop(BLACK_BISHOP,indexes[0],indexes[1]);
        break;
    case BLACK_QUEEN:
        returnVector = getMovementOfQueen(BLACK_QUEEN,indexes[0],indexes[1]);
        break;
    case BLACK_KING:
        returnVector = getMovementOfKing(BLACK_KING,indexes[0],indexes[1]);
        break;
    case BLACK_PAWN:
        returnVector = getMovevementsOfPawn(BLACK_PAWN,indexes[0],indexes[1]);
        break;
    case WHITE_ROOK:
        returnVector = getMovementsOfRook(WHITE_ROOK,indexes[0],indexes[1]);
        break;
    case WHITE_KNIGHT:
        returnVector = getMovementsOfKnight(WHITE_KNIGHT,indexes[0],indexes[1]);
        break;
    case WHITE_BISHOP:
        returnVector = getMovementsOfBishop(WHITE_BISHOP,indexes[0],indexes[1]);
        break;
    case WHITE_QUEEN:
        returnVector = getMovementOfQueen(WHITE_QUEEN,indexes[0],indexes[1]);
        break;
    case WHITE_KING:
        returnVector = getMovementOfKing(WHITE_KING,indexes[0],indexes[1]);
        break;
    case WHITE_PAWN:
        returnVector = getMovevementsOfPawn(WHITE_PAWN,indexes[0],indexes[1]);
        break;
    default:
        break;
    }

    return returnVector;
}

void BoardModel::movePiece(int indexFrom, int indexTo)
{
    QVector<int> possibleMoves = getPossibleMoves(indexFrom);
    if (possibleMoves.contains(indexTo)){
        piece actualPiece = squares[indexFrom].getPiece();
        squares[indexFrom].setPiece(EMPTY);
        squares[indexTo].setPiece(actualPiece);
        changeTurn();
        emit notifyMoveOfPiece(indexFrom, indexTo);
    }
}
