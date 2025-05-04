#ifndef BOARD_H
#define BOARD_H

#include "config.h"

class BOARD: public array<array<s3, 8>, 9> {
public:
	char *ConvertToFEN(void);
	s4 InCheck(void);
	void Init(void);
	void Load(void);
	void ParseFEN(void);
	void ParsePGN(void);
	void Save(void);
	void Setup(void);
	void ShowUTF(void);
	void Show(void);
	void Transpose(void);
private:
	int stm;
	FILE *f;
	char brdfilename[10];
};

#endif

