int main(void) {
	return 0;
}

typedef struct {
	int pieces[8][8];
	int stm;
	int flags;
} BOARD;

typedef struct {
	int cor[4];
	int side;
	int flags;
} MOVE;

