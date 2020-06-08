#ifndef NAMESPACES_H
#define NAMESPACES_H

#include <QObject>

namespace enums {
    Q_NAMESPACE
    enum piece {
        EMPTY,
        WHITE_PAWN, WHITE_BISHOP, WHITE_KNIGHT, WHITE_QUEEN, WHITE_ROOK, WHITE_KING,
        BLACK_PAWN, BLACK_BISHOP, BLACK_KNIGHT, BLACK_QUEEN, BLACK_ROOK, BLACK_KING
    };
    Q_ENUM_NS(piece)
}

#endif // NAMESPACES_H
