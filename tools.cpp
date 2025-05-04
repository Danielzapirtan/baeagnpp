#include "config.h"
#include "board.h"

#define _SHARE_DIR "/usr/local/share/baeagn/"

void makemove(BOARD src, MOVE move, BOARD &dest)
{
	dest = src;
	if (dest[move[0]][move[1]] == _WK) {
		if (move[0] == 0)
			if (move[2] == 0)
				if (move[1] == 4) {
					if (move[3] == 2) {
						dest[0][0] = 0;
						dest[0][3] = _WR;
					}
					if (move[3] == 6) {
						dest[0][7] = 0;
						dest[0][5] = _WR;
					}
				}
		dest[8][0] = 0;
		dest[8][1] = 0;
	}
	if (dest[move[0]][move[1]] == _WR)
		if (move[0] == 0) {
			if (move[1] == 0)
				dest[8][0] = 0;
			if (move[1] == 7)
				dest[8][1] = 0;
		}
	if (dest[move[0]][move[1]] == _WP)
		if (move[0] == 6) {
			dest[move[2]][move[3]] = _WQ;
			dest[move[0]][move[1]] = 0;
			dest.Transpose();
			goto end;
		}
	if (dest[move[0]][move[1]] == _WP)
		if (move[0] == 4)
			if (move[1] != move[3])
				if (dest[move[0]][move[3]] == _BP)
					dest[move[0]][move[3]] = 0;
	dest[move[2]][move[3]] = dest[move[0]][move[1]];
	dest[move[0]][move[1]] = 0;
	dest.Transpose();
end:    ;
}

void show_move(MOVE move, BOARD &board, u5 stm, char *buf)
	/*
	 * FIXME
	 * What about promotions?!
	 */
{
	BOARD aux;
	char *p;
	p = buf;
	switch (board[move[0]][move[1]]) {
		case 2: p += sprintf(p, "N"); break;
		case 3: p += sprintf(p, "B"); break;
		case 4: p += sprintf(p, "R"); break;
		case 5: p += sprintf(p, "Q"); break;
		case 6: if ((move[1] == 4) && ((move[3] == 6) || (move[3] == 2))) {
				switch (move[3]) {
					case 6: p += sprintf(p, "O-O"); break;
					case 2: p += sprintf(p, "O-O-O"); break;
					default:;
				}
				return;
			} else p += sprintf(p, "K"); break;
		default:;
	}
	p += sprintf(p, "%c", 97 + move[1]);
	if (stm)
		p += sprintf(p, "%d", 9 - (move[0] + 1));
	else
		p += sprintf(p, "%d", move[0] + 1);
	if (((board[(u5) move[0]][(u5) move[1]] == 1) && \
				(move[1] != move[3])) || \
			((board[(u5) move[0]][(u5) move[1]] > 1) && \
			 (board[(u5) move[2]][(u5) move[3]] < 0)))
		p += sprintf(p, "x");
	p += sprintf(p, "%c", 97 + move[3]);
	if (stm)
		p += sprintf(p, "%d", 9 - (move[2] + 1));
	else
		p += sprintf(p, "%d", move[2] + 1);
	makemove(board, move, aux);
	if (aux.InCheck())
		p += sprintf(p, "+");
	(*p) = 0;
}

void show_move_utf(MOVE move, BOARD &board, u5 stm, char *buf)
	/*
	 * FIXME
	 * What about promotions?!
	 */
{
	BOARD aux;
	char *p;
	p = buf;
	switch (board[(u5) move[0]][(u5) move[1]]) {
		case 2: p += sprintf(p, "\u2658"); break;
		case 3: p += sprintf(p, "\u2657"); break;
		case 4: p += sprintf(p, "\u2656"); break;
		case 5: p += sprintf(p, "\u2655"); break;
		case 6: if ((move[1] == 4) && ((move[3] == 6) || (move[3] == 2))) {
				switch (move[3]) {
					case 6: p += sprintf(p, "O-O"); break;
					case 2: p += sprintf(p, "O-O-O"); break;
					default:;
				}
				return;
			} else p += sprintf(p, "\u2654"); break;
		default:;
	}
	p += sprintf(p, "%c", 97 + move[1]);
	if (stm)
		p += sprintf(p, "%d", 9 - (move[0] + 1));
	else
		p += sprintf(p, "%d", move[0] + 1);
	if (((board[(u5) move[0]][(u5) move[1]] == 1) && \
				(move[1] != move[3])) || \
			((board[(u5) move[0]][(u5) move[1]] > 1) && \
			 (board[(u5) move[2]][(u5) move[3]] < 0)))
		p += sprintf(p, "x");
	p += sprintf(p, "%c", 97 + move[3]);
	if (stm)
		p += sprintf(p, "%d", 9 - (move[2] + 1));
	else
		p += sprintf(p, "%d", move[2] + 1);
	makemove(board, move, aux);
	if (aux.InCheck())
		p += sprintf(p, "+");
	(*p) = 0;
}

int board_cmp(BOARD src, BOARD dest)
{
	u5 x;
	u5 y;
	for (y = 0; y < 9; y++)
		for (x = 0; x < 8; x++)
			if (dest[y][x] != src[y][x])
				return (1);
	return (0);
}

int main(int argc, char *argv[])
{
	gmode = 4;
	chdir(_SHARE_DIR);
	TREE tree;
	tree.Analysis();
	return (0);
}

void warn(const char *msg)
{
	fprintf(stderr, "\nwarn %s\n", msg);
}

char pieceToFenSymbol(int pieceId) {
	switch (pieceId) {
		case 1: return 'P';
		case -1: return 'p';
		case 2: return 'N';
		case -2: return 'n';
		case 3: return 'B';
		case -3: return 'b';
		case 4: return 'R';
		case -4: return 'r';
		case 5: return 'Q';
		case -5: return 'q';
		case 6: return 'K';
		case -6: return 'k';
		default: return '.';
	}
}

char *streval(VALUE value)
{
	static char buf[10];
	if (stm)
		value *= (-1);
	if (value >= 150)
		sprintf(buf, "+-");
	else if (value >= 70)
		sprintf(buf, "+/-");
	else if (value >= 30)
		sprintf(buf, "+/=");
	else if (value >= 1)
		sprintf(buf, "+/~");
	else if (value == 0)
		sprintf(buf, "=");
	else if (value <= -150)
		sprintf(buf, "-+");
	else if (value <= -70)
		sprintf(buf, "-/+");
	else if (value <= -30)
		sprintf(buf, "=/+");
	else
		sprintf(buf, "~/+");
	return (char *) buf;
}

s4 move_cmp(MOVE src, MOVE dest)
{
	u5 u;
	for (u = 0; u < 4; u++)
		if (src[u] != dest[u])
			return (u + 1);
	return (0);
}

