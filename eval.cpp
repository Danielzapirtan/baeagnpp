#include "config.h"
#include "board.h"
#include "tree.h"

#define _ALLOW_PIECE_EVAL (1)

VALUE EVAL::Centrality(void)
{
	VALUE value = 0;
	for (int y = 0; y < 8; y++)
	for (int x = 0; x < 8; x++) {
		s5 x1 = x;
		s5 y1 = y;
		if (x1 > 3) x1 = 7 - x1;
		if (y1 > 3) y1 = 7 - y1;
		if (board[y][x] < 0)
			value -= (1 + min(x1, y1));
		else if (board[y][x] > 0)
			value += (1 + min(x1, y1));
	}
	return (value);
}

VALUE EVAL::Custom(LEVEL level)
{
	return Robw();
}

VALUE EVAL::Robw(void)
{
	VALUE value = 0;
	if (board[4][7] == _WP)
		value += 100;
	if (board[5][7] == _WP)
		value += 200;
	if (board[6][7] == _WP)
		value += 400;
	if (board[3][7] == _BP)
		value -= 100;
	if (board[2][7] == _BP)
		value -= 200;
	if (board[1][7] == _BP)
		value -= 400;
	return value;
}

VALUE EVAL::Ini(void)
{
	VALUE value = 0;
	if (board[3][3] == 1)
		value += 83;
	if (board[4][3] == -1)
		value -= 83;
	if (board[3][4] == 1)
		value += 79;
	if (board[4][4] == -1)
		value -= 79;
	if (board[0][3] != 5)
		value -= 230;
	if (board[7][3] != -5)
		value += 230;
	if (board[2][5] == 2)
		value += 32;
	if (board[5][5] == -2)
		value -= 32;
	return value;
}

VALUE EVAL::Material(LEVEL level)
{
	int kings = 0;
	VALUE value = 0;
	for (int y = 0; y < 8; y++)
	for (int x = 0; x < 8; x++) {
	switch (board[y][x]) {
#ifdef _ALLOW_PIECE_EVAL
		case _WP:
		switch (y) {
			case 1:
			case 2:
			case 3:
			case 4:
				value += 100;
				break;
			case 5:
				value += 200;
				break;
			case 6:
				value += 400;
			default:;
		}
		break;
		case _WN:
		case _WB:
		case _WR:
		case _WQ:
			value += _VALUES[(u5) board[y][x]];
			break;
		case _BP:
		switch (y) {
			case 6:
			case 5:
			case 4:
			case 3:
				value -= 100;
				break;
			case 2:
				value -= 200;
				break;
			case 1:
				value -= 400;
				break;
			default:;
		}
		break;
		case _BN:
		case _BB:
		case _BR:
		case _BQ:
			value -= _VALUES[(u5) (-board[y][x])];
			break;
#endif
		case _WK: kings++; break;
		case _BK: kings--; break;
		default:;
	} }
	if (kings) {
		if (kings > 0)
			return INF - level;
		else
			return -INF + level;
	}
	return value;
}

VALUE EVAL::Mobility(LEVEL level)
{
	if (level < 2)
		return 0;
	return parent->parent->movelist.maxindex - parent->movelist.maxindex;
}

