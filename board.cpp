#include "config.h"
#include "board.h"

#define brdfilename "brd/start.brd"

static FILE *f = stdout;

void BOARD::Init(void)
{
    static s3 init[9][8] = {
        {_WR, _WN, _WB, _WQ, _WK, _WB, _WN, _WR, },
        {_WP, _WP, _WP, _WP, _WP, _WP, _WP, _WP, },
        {_UO, _UO, _UO, _UO, _UO, _UO, _UO, _UO, }, 
        {_UO, _UO, _UO, _UO, _UO, _UO, _UO, _UO, }, 
        {_UO, _UO, _UO, _UO, _UO, _UO, _UO, _UO, }, 
        {_UO, _UO, _UO, _UO, _UO, _UO, _UO, _UO, }, 
        {_BP, _BP, _BP, _BP, _BP, _BP, _BP, _BP, },
        {_BR, _BN, _BB, _BQ, _BK, _BB, _BN, _BR, },
        { 1, 1, 1, 1, 0, 0, 0, 0, },
    };
    for (int y = 0; y < 9; y++)
    for (int x = 0; x < 8; x++)
	    (*this)[y][x] = init[y][x];
}

void BOARD::Load(void)
{
    FILE *f;
    s5 pp;
    u5 x;
    u5 y;
    f = fopen(brdfilename, "r");
    if (!f)
        warn("Cannot open .brd file for read");
    for (y = 8; y > 0; y--)
    for (x = 0; x < 8; x++) {
        fscanf(f, "%d", &pp);
        (*this)[y - 1][x] = (s3) pp;
    }
    for (x = 0; x < 8; x++)
        (*this)[8][x] = (x < 4);
    fscanf(f, "%d", &stm);
    fclose(f);
    if (stm)
       Transpose();
}

void BOARD::Save(void)
{
    FILE *f;
    s5 pp;
    s5 x;
    s5 y;
    f = fopen(brdfilename, "w");
    if (!f)
        warn("Cannot open .brd file for write");
    for (y = 8; y > 0; y--) {
    for (x = 0; x < 8; x++) {
	pp = (s5) (*this)[y - 1][x];
	fprintf(f, "%2d ", pp);
    }
	fprintf(f, "\n");
    }
    fprintf(f, "%d\n", stm);
    fflush(stdout);
    fclose(f);
    if (stm)
	    Transpose();
}

s4 BOARD::InCheck(void)
{
    BOARD aux;
    MOVE curr_move;
    MOVEINDEX curr_index;
    MOVELIST movelist;
    aux = *this;
    aux.Transpose();
    GENERATOR generator;
    generator.gendeep(aux, movelist, 0);
    for (curr_index = 0; curr_index < movelist.maxindex; curr_index++) {
	curr_move = movelist[curr_index];
        if (aux[(u5) curr_move[2]][(u5) curr_move[3]] == _BK)
        return (1);
    }
    return (0);
}

void BOARD::Show(void)
{
    s3 t;
    u5 x;
    u5 y;
    for (y = 0; y < 8; y++) {
        printf("%d", (int) (8 - y));
    for (x = 0; x < 8; x++) {
        t = (*this)[7 - y][x];
	switch (t) {
		case 0: printf(" . "); break;
		case 1: printf(" P "); break;
		case 2: printf(" N "); break;
		case 3: printf(" B "); break;
		case 4: printf(" R "); break;
		case 5: printf(" Q "); break;
		case 6: printf(" K "); break;
		case -1: printf(" p "); break;
		case -2: printf(" n "); break;
		case -3: printf(" b "); break;
		case -4: printf(" r "); break;
		case -5: printf(" q "); break;
		case -6: printf(" k "); break;
		default: warn("Wrong piece code");
	}
    }
        printf("\n");
    }
    printf("  a  b  c  d  e  f  g  h\n");
    printf("\n");
    fflush(stdout);
}

void BOARD::ShowUTF(void)
{
    s3 t;
    u5 x;
    u5 y;
    for (y = 0; y < 8; y++) {
        printf("%d", (int) (8 - y));
    for (x = 0; x < 8; x++) {
        t = (*this)[7 - y][x];
	switch (t) {
		case  0: cout<<" . "; break;
		case +1: cout<<" \u2659 "; break;
		case +2: cout<<" \u2658 "; break;
		case +3: cout<<" \u2657 "; break;
		case +4: cout<<" \u2656 "; break;
		case +5: cout<<" \u2655 "; break;
		case +6: cout<<" \u2654 "; break;
		case -1: cout<<" \u265F "; break;
		case -2: cout<<" \u265E "; break;
		case -3: cout<<" \u265D "; break;
		case -4: cout<<" \u265C "; break;
		case -5: cout<<" \u265B "; break;
		case -6: cout<<" \u265A "; break;
		default: warn("Wrong piece code");
	}
    }
        printf("\n");
    }
    printf("  a  b  c  d  e  f  g  h\n");
    printf("\n");
    fflush(stdout);
}

void BOARD::Transpose(void)
{
    s3 t;
    u5 x;
    u5 y;
    for (y = 0; y < 4; y++)
    for (x = 0; x < 8; x++) {
        t = (*this)[y][x];
        (*this)[y][x] = (*this)[7 - y][x];
        (*this)[7 - y][x] = t;
    }
    for (y = 0; y < 8; y++)
    for (x = 0; x < 8; x++)
        (*this)[y][x] = -(*this)[y][x];
    t = (*this)[8][0];
    (*this)[8][0] = (*this)[8][2];
    (*this)[8][2] = t;
    t = (*this)[8][1];
    (*this)[8][1] = (*this)[8][3];
    (*this)[8][3] = t;
}

void BOARD::Setup(void)
{
	s5 x = 3;
	s5 y = 3;
	unsigned int symbol = 0;
	ParseFEN();
 	Load();
	while (1) {
		printf("\033[2J");
		printf("\033[1;1H");
		Show();
		system("cat fen/start.fen");
		printf("enter square %d %c%d\n",
			stm, x + 97, y + 1);
		fflush(stdout);
		scanf("%u", &symbol);
		fflush(stdin);
		switch(symbol) {
			case 4: 
				return;
				break;
			case 20: (*this)[y][x] = 0; break;
			case 31: 
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
				(*this)[y][x] = symbol - 30;
				break;
			case 41:
			case 42:
			case 43:
			case 44:
			case 45:
			case 46:
				(*this)[y][x] = 40 - symbol;
				break;
			case 51:
			case 52:
			case 53:
			case 54:
			case 55:
			case 56:
			case 57:
			case 58:
				x = symbol - 51;
				break;
			case 61:
			case 62:
			case 63:
			case 64:
			case 65:
			case 66:
			case 67:
			case 68:
				y = symbol - 61;
				break;
			case 70:
				Init();
				break;
			case 71:
				Load();
				break;
			case 72:
				Save();
				break;
			case 73:
				stm = 1 - stm;
				(*this)[8][4] = stm;
				break;
			case 74:
				exit(0);
				break;
			case 75:
				Transpose();
				break;
			case 76:
				ParseFEN();
				break;
			default:;
		}
	}
}

void BOARD::ParseFEN(void)
{
  FILE *f;
  int x = 1;
  int y = 8;
  int ch;
  int pp;
  f = fopen("fen/start.fen", "r");
  if (!f)
    warn("warn in parse_fen"); // Make sure 'warn' is defined
  while ((ch = fgetc(f)) != EOF && ch != ' ') {
    pp = 0;
    if ((ch >= '1') && (ch <= '8')) {
      while (ch > '0') {
        (*this)[y - 1][x - 1] = 0;
        x++;
        ch--;
      }
      if (x == 9) {
        x = 1;
        y--;
        if (!y) {
	  ch = fgetc(f);
          goto end;
	}
        continue;
      }
    } else if (ch != '/') {
      switch (ch) {
        case 'p': pp = -1; break;
        case 'n': pp = -2; break;
        case 'b': pp = -3; break;
        case 'r': pp = -4; break;
        case 'q': pp = -5; break;
        case 'k': pp = -6; break;
        case 'P': pp = 1; break;
        case 'N': pp = 2; break;
        case 'B': pp = 3; break;
        case 'R': pp = 4; break;
        case 'Q': pp = 5; break;
        case 'K': pp = 6; break;
        default: pp = -8;
      }
      if (pp > -8)
        (*this)[y - 1][x - 1] = pp;
      x++;
      if (x == 9) {
        x = 1;
        y--;
        if (!y) {
          ch = fgetc(f);
          goto end;
        }
      }
    }
  }
end:
  ch = fgetc(f);
  fclose(f);
  // Update stm based on the character read from FEN
  if (ch == 'w')
    stm = 0;
  else if (ch == 'b')
    stm = 1;
  else {
      warn("Cannot set `stm' variable");
  }
}

void BOARD::ParsePGN(void)
{
    if (system("pgn-extract -F pgn/start.pgn > pf") != 0) {
        fprintf(stderr, "Error running pgn-extract\n");
        return;
    }
    FILE *f = fopen("pf", "r");
    FILE *g = fopen("fen/start.fen", "w");
    if (!f || !g) {
        fprintf(stderr, "Error opening files\n");
        if (f) fclose(f);
        if (g) fclose(g);
        return;
    }
    int ch;
    Init();
    while ((ch = fgetc(f)) != '{') {}
    while ((ch = fgetc(f)) != '"') {}
    while ((ch = fgetc(f)) != '"') fputc(ch, g);
    fclose(f);
    fclose(g);
    ParseFEN();
    Save();
}

char *BOARD::ConvertToFEN(void)
{
    static char fenString[256];
    char *q;
    q = (char *) fenString;
    for (int rank = 7; rank >= 0; rank--) {
        int emptyCount = 0;
        for (int file = 0; file < 8; file++) {
            int pieceId = (*this)[rank][file];
            if (pieceId == 0) {
                emptyCount++;
            } else {
                if (emptyCount > 0) {
			(*q++) = '0' + emptyCount;
                    emptyCount = 0;
                }
		(*q++) = pieceToFenSymbol(pieceId);
            }
        }
        if (emptyCount > 0) {
		(*q++) = '0' + emptyCount;
        }
        if (rank > 0) {
		(*q++) = '/';
        }
    }
    (*q++) = '\0';
   return (char *) fenString;
}

