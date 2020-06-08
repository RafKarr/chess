#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QObject>
#include <square.h>

using namespace enums;

class BoardModel : public QObject
{
    Q_OBJECT

public:
    explicit BoardModel(QObject *parent = nullptr);

    Q_INVOKABLE void resetPieces();
    Q_INVOKABLE int getPiece(int index);
    Q_INVOKABLE QVector<int> getPossibleMoves(int index);
    Q_INVOKABLE void movePiece(int indexFrom, int indexTo);

private:

    enum turn {
        WHITE, BLACK
    };

    turn m_turn = WHITE;

    QVector<Square> squares;
    int getIndex(int x, int y);
    QVector<int> getIndexes(int index);
    QVector<int> getMovevementsOfPawn(piece piece,int x, int y);
    QVector<int> getMovementsOfKnight(piece piece, int x, int y);
    QVector<int> getMovementsOfBishop(piece piece, int x, int y);
    QVector<int> getMovementsOfRook(piece piece, int x, int y);
    QVector<int> getMovementOfQueen(piece piece, int x, int y);
    QVector<int> getMovementOfKing(piece piece, int x, int y);
    int checkAvailabilityOfSquare(piece piece, int index);
    void changeTurn();

signals:
    void notifyMoveOfPiece(int indexFrom, int indexTo);
    void notifyTaking(int index);
    void notifyPromotion(int index);
};

#endif // BOARDMODEL_H
