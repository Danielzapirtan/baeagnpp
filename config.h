#ifndef CONFIG_H
#define CONFIG_H

#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace std;

#define _ALLOW_CASTLE (1)
#ifndef _MAXINDEX
#define _MAXINDEX (200)
#endif
#define _MAXLEVEL (25)
#define _FRAMESPERSEC (32)
#define _NPS (5 << 18)
#define _SKIPFRAMES (_NPS / _FRAMESPERSEC)
#define _ALPHA (-INF)
#define _BETA (INF)
#define _OVERDEPTH (1)
#ifndef _PIECE_CODES
#define _PIECE_CODES (1)
#define _WP (1)
#define _WN (2)
#define _WB (3)
#define _WR (4)
#define _WQ (5)
#define _WK (6)
#define _BP (-1)
#define _BN (-2)
#define _BB (-3)
#define _BR (-4)
#define _BQ (-5)
#define _BK (-6)
#define _WM (7)
#define _BM (-7)
#define _UO (0)
#define _BS (-8)
#endif

typedef int s3;
typedef int s4;
typedef int s5;
typedef unsigned u3;
typedef unsigned u4;
typedef unsigned u5;
typedef unsigned long u6;

typedef u4 LEVEL;
typedef u4 MOVEINDEX;
typedef u6 NODES;
typedef s4 VALUE;

class RANGE {};

template<class T, int dim>class array {
	public:
		T &operator [](int i) {
			return data[i];
		}
	private:
		T data[dim];
};

class MOVE: public array<s3, 6> { };

class MOVELIST: public array<MOVE, _MAXINDEX> {
	public:
		MOVEINDEX maxindex;
};

const VALUE _PAWNUNIT     = (100);
const VALUE _THRESHOLD    = (16381);
const VALUE _VALUES[6]    = { 0, 100, 315, 325, 500, 980, };

extern int newpv;
extern int pvsready;
extern LEVEL gdepth;
extern LEVEL glevel;
extern MOVE best_move;
extern NODES nodes;
extern s4 gmode;
extern s4 stm;

extern char pieceToFenSymbol(int pieceId);
extern char *streval(VALUE);
extern s4 move_cmp(MOVE src, MOVE dest);
extern void warn(const char *msg);

#endif

