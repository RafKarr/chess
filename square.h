#ifndef SQUARE_H
#define SQUARE_H

#include <QObject>
#include "namespaces.h"

using namespace enums;


class Square{

public:

    Square();

    Q_ENUMS(piece)

    piece getPiece();
    void setPiece(const piece &piece);

private:
    piece m_piece;
};



#endif // SQUARE_H


