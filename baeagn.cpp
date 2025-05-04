#include "config.h"
#include "board.h"
#include "movegen.h"
#include "tree.h"
#include "board.cpp"
#include "movegen.cpp"
#include "tools.cpp"
#include "tree.cpp"
#include "eval.cpp"

int newpv;
int pvsready;
int stm;
LEVEL gdepth;
LEVEL glevel;
NODES nodes;
s4 gmode;
TREE maintree;

