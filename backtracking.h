#ifndef _BACKTRACKING_H_
#define _BACKTRACKING_H_


void    practise_backtracking(int tc, int argc, char* argv[]);
char*   string_permute(char *fix, char* ch);
void    test_string_permute(char *in);
void    test_n_queen(int n);

#define NQUEEN 4
void    queen_mark_spots(int i, int j, int pos[][NQUEEN], int b);
bool    queen_spot_available(int i, int j, int pos[][NQUEEN]);
bool    n_queen(int n, int pos[][NQUEEN]);
#endif
