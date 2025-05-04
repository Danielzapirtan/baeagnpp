#ifndef TREE_H
#define TREE_H

#include "config.h"
#include "time.cpp"

#define INF (32765)

class TREE {
	public:
		TREE(void) { }
		~TREE(void) { }
		void Analysis(void);
		MOVELIST movelist;
		TREE *parent;
	private:
		void Eval(LEVEL);
		void Gen(void);
		void Report(void);
		void ReportLn(void);
		VALUE Search(LEVEL);
	protected:
		BOARD board;
		TREE *root;
	private:
		BOARD aux;
		LEVEL len;
		LEVEL depth;
		LEVEL level;
		array<MOVE, _MAXLEVEL> line;
		MOVE move;
		MOVEINDEX index;
		TIME Time;
		VALUE alpha;
		VALUE best;
		VALUE beta;
		VALUE value;
		array<VALUE, _MAXINDEX> valuelist;
};

class EVAL: public TREE {
	public:
		VALUE Centrality(void);
		VALUE Custom(LEVEL);
		VALUE Ini(void);
		VALUE Material(LEVEL);
		VALUE Mobility(LEVEL);
		VALUE Robw(void);
};

#endif

