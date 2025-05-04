#include "config.h"
#include "board.h"
#include "movegen.h"
#include "tree.h"

void TREE::ReportLn(void)
{
	Time.update();
	double dTime = Time.dclock();
	aux = board;
	cout<<"<< info depth "<<depth - _OVERDEPTH<<" score cp "<<best<<" pv ";
	for (LEVEL i = 0; i < len - _OVERDEPTH; i++) {
		BOARD aux2;
		char buf[80];
		show_move(line[i], aux, (i + stm) % 2, buf);
		makemove(aux, line[i], aux2);
		aux = aux2;
		cout<<buf<<" ";
	}
	int nps = (int) ((double) nodes / dTime);
	cout<<"time "<<(int) (1000.0 * dTime)<<" nodes "<<nodes<<" nps "<<nps<<endl;
}

#define abs(x) ((x > 0) ? (x) : ((-x)))
#define min(x, y) (((x) < (y)) ? (x) : (y))
void TREE::Eval(LEVEL level)
{
	nodes++;
	if ((nodes % (NODES) _SKIPFRAMES) == 0L) {
		Time.update();
		if ((double) nodes >= 1e9)
			exit(0);
	}
	EVAL eval;
	eval.board = board;
	eval.parent = parent;
	value = eval.Material(level);
	if (abs(value) > _THRESHOLD)
		return;
	value += eval.Centrality();
	value += eval.Custom(level);
	value += eval.Mobility(level);
	return;
}

void TREE::Gen(void)
{
	GENERATOR generator;
	generator.gendeep(board, movelist, 1);
}

VALUE TREE::Search(LEVEL level)
{
	Eval(level);
	len = depth;
	if (value < -_THRESHOLD) {
		return (level - INF);
	}
	if (depth == 0) {
		return (value);
	}
	if (depth <= _OVERDEPTH)
		if (value > -(_PAWNUNIT >> 1)) {
			return (value);
		}
	if (depth)
		glevel = level;
	Gen();
	if (movelist.maxindex == 0) {
		return (-INF + level);
	}
	best = -INF;
	for (index = 0; index < movelist.maxindex; index++) {
		if ((level == 0) && depth)
			cout<<"<< info moveindex "<<(1 + index)<<"\r"<<flush;
		TREE tree;
		move = movelist[index];
		makemove(board, move, aux);
		tree.root = root;
		tree.parent = this;
		tree.board = aux;
		tree.level = level + 1;
		tree.depth = depth - 1;
		tree.alpha = -beta;
		tree.beta = -alpha;
		value = -tree.Search(level + 1);
		if (value > _THRESHOLD)
			return value;
		if (value > best) {
			best = value;
			line[0] = move;
			len = tree.len + 1;
			for (LEVEL bl_lev = 0; bl_lev < tree.len; bl_lev++)
				line[bl_lev + 1] = tree.line[bl_lev];
			if (best > alpha)
				alpha = best;
			if (alpha >= beta)
				return beta;
		}
	}
	return best;
}

void TREE::Analysis(void)
{
	board.Load();
	//board.Save();
	Time.init();
	nodes = 0L;
	pvsready = 0;
	LEVEL maxlevel = 10;
	for (LEVEL depth1 = 5; depth1 < maxlevel; depth1 += 1) {
		root = this;
		parent = NULL;
		level = 0;
		depth = depth1 + _OVERDEPTH;
		gdepth = depth;
		alpha = -INF;
		beta = INF;
		newpv = 0;
		best = Search(0);
		pvsready = 1;
		ReportLn();
	}
}

