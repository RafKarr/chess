#include "square.h"

/*
 * Model for Square
 */

Square::Square()
{
    setPiece(EMPTY);
}

piece Square::getPiece()
{
    return m_piece;
}

void Square::setPiece(const enum piece &piece){
    m_piece = piece;
}
