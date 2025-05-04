#include "config.h"
#include "movegen.h"

void GENERATOR::addm(s5 y, s5 x, s5 y1, s5 x1)
{
    movelist[movelist.maxindex][0] = y;
    movelist[movelist.maxindex][1] = x;
    movelist[movelist.maxindex][2] = y1;
    movelist[movelist.maxindex][3] = x1;
    movelist.maxindex++;
    if (movelist.maxindex >= _MAXINDEX)
        warn("Index too big");
}

void GENERATOR::addprom(s5 y, s5 x, s5 y1, s5 x1, s5 to)
{
    movelist[movelist.maxindex][0] = y;
    movelist[movelist.maxindex][1] = x;
    movelist[movelist.maxindex][2] = y1;
    movelist[movelist.maxindex][3] = x1;
    movelist[movelist.maxindex][4] = to;
    movelist.maxindex++;
    if (movelist.maxindex >= _MAXINDEX)
        warn("Index too big");
}

void GENERATOR::castle(s5 y, s5 x)
{
    BOARD aux;
    if (y != 0) return;
    if (x != 4) return;
    if (board[y][x] != _WK)
        return;
    if (board[0][0] == _WR)
    if (board[0][1] == 0)
    if (board[0][2] == 0)
    if (board[0][3] == 0)
    if (board[8][0] == 1) {
        aux = board;
        aux[0][2] = _WK;
        aux[0][3] = _WK;
        if (! aux.InCheck())
            addm(0, 4, 0, 2);
    }
    if (board[0][7] == _WR)
    if (board[0][6] == 0)
    if (board[0][5] == 0)
    if (board[8][1] == 1) {
        aux = board;
        aux[0][5] = _WK;
        aux[0][6] = _WK;
        if (! aux.InCheck())
            addm(0, 4, 0, 6);
    }
}

void GENERATOR::genP(s5 y, s5 x)
{
    if (board[y + 1][x] == 0) {
        if (y != 6)
            addm(y, x, y + 1, x);
        if (y == 6) {
            s5 to;
            for (to = 5; to >= 2; to--)
                addprom(y, x, y + 1, x, to);
        }
        if (y == 1)
        if (board[y + 2][x] == 0)
            addm(y, x, y + 2, x);
    }
    if (x > 0)
    if (board[y + 1][x - 1] < 0) {
        if (y != 6)
            addm(y, x, y + 1, x - 1);
        else {
            s5 to;
            for (to = 5; to >= 2; to--)
                addprom(y, x, y + 1, x - 1, to);
        }
    }
    if (x < 7)
    if (board[y + 1][x + 1] < 0) {
        if (y != 6)
            addm(y, x, y + 1, x + 1);
        else {
            s5 to;
            for (to = 5; to >= 2; to--)
                addprom(y, x, y + 1, x + 1, to);
        }
    }
}

void GENERATOR::genN(s5 y, s5 x)
{
    nonslider(y, x, +2, -1);
    nonslider(y, x, +2, +1);
    nonslider(y, x, +1, +2);
    nonslider(y, x, +1, -2);
    nonslider(y, x, -1, +2);
    nonslider(y, x, -1, -2);
    nonslider(y, x, -2, -1);
    nonslider(y, x, -2, +1);
}

void GENERATOR::genB(s5 y, s5 x)
{
    slider(y, x, +1, -1);
    slider(y, x, +1, +1);
    slider(y, x, -1, +1);
    slider(y, x, -1, -1);
}

void GENERATOR::genR(s5 y, s5 x)
{
    slider(y, x, +1,  0);
    slider(y, x,  0, -1);
    slider(y, x,  0, +1);
    slider(y, x, -1,  0);
}

void GENERATOR::genQ(s5 y, s5 x)
{
    genR(y, x);
    genB(y, x);
}

void GENERATOR::genK(s5 y, s5 x, LEVEL depth)
{
    nonslider(y, x, -1, -1);
    nonslider(y, x, -1,  0);
    nonslider(y, x, -1, +1);
    nonslider(y, x,  0, -1);
    nonslider(y, x,  0, +1);
    nonslider(y, x, +1, -1);
    nonslider(y, x, +1,  0);
    nonslider(y, x, +1, +1);
#ifdef _ALLOW_CASTLE
    if (depth == 1)
        castle(y, x);
#endif
}

void GENERATOR::nonslider(s5 y, s5 x, s3 dy, s3 dx)
{
    if (y + dy < 0) return;
    if (y + dy > 7) return;
    if (x + dx < 0) return;
    if (x + dx > 7) return;
    if (board[y + dy][x + dx] <= 0)
        addm(y, x, y + dy, x + dx);
}

void GENERATOR::slider(s5 y, s5 x, s3 dy, s3 dx)
{
    s5 y1 = y;
    s5 x1 = x;
    while (1) {
        y1 += dy;
        x1 += dx;
        if (y1 < 0) return;
        if (y1 > 7) return;
        if (x1 < 0) return;
        if (x1 > 7) return;
        if (board[y1][x1] < 0) {
            addm(y, x, y1, x1);
            return;
        }
        if (board[y1][x1] > 0)
            return;
        addm(y, x, y1, x1);
    }
}

void GENERATOR::gendeep(BOARD &pboard, MOVELIST &pmovelist, LEVEL depth)
{
    board = pboard;
    movelist.maxindex = 0;
    s5 x;
    s5 y;
    for (y = 7; y >= 0; y--)
    for (x = 0; x < 8; x++) {
        switch(board[y][x]) {
        case _WP: genP(y, x); break;
        case _WN: genN(y, x); break;
        case _WB: genB(y, x); break;
        case _WR: genR(y, x); break;
        case _WQ: genQ(y, x); break;
        case _WK: genK(y, x, depth); break;
        default:;
        }
    }
    pmovelist = movelist;
}

