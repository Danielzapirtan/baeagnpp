#ifndef GENERATOR_H
#define GENERATOR_H
#include "config.h"

class GENERATOR {
public:
	void gendeep(BOARD &pboard, MOVELIST &pmovelist, LEVEL depth);
private:
	BOARD board;
	MOVELIST movelist;
	void addm(s5 y, s5 x, s5 y1, s5 x1);
	void addprom(s5 y, s5 x, s5 y1, s5 x1, s5 to);
	void castle(s5 y, s5 x);
	void genP(s5 y, s5 x);
	void genN(s5 y, s5 x);
	void genB(s5 y, s5 x);
	void genR(s5 y, s5 x);
	void genQ(s5 y, s5 x);
	void genK(s5 y, s5 x, LEVEL depth);
	void nonslider(s5 y, s5 x, s3 dy, s3 dx);
	void slider(s5 y, s5 x, s3 dy, s3 dx);
};

#endif

