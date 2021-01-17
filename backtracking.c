#include <stdio.h>
#include "backtracking.h"
#include "util.h"
#include <iostream>
#include <queue>

using namespace std;

char*   string_permute(char *fix, char* ch)
{
    int count = 0;
    int flen = 0;
    if (NULL == ch) {
        return fix;
    } else {
        count = strlen(ch);
        switch ( count) {
            case 1: 
                if (fix) cout << fix;
                cout << ch[0] ;
                break;
            default:  
                int i = 0;
                flen = strlen(fix);
                while ( i < count) {
                    memset(fix+flen, 0, 10-flen);
                    swapChar(ch, 0, i);
                    fix[flen] = ch[0];
                    i++;
                    string_permute(fix, ch+1);
                    swapChar(ch, 0, i-1);
                }
        }
        cout << "\n"; 
    }
}
void    test_string_permute(char *in)
{
    char*   change = in;
    char*   fixed = new char[10];
    string_permute(fixed, change);
    delete[] fixed;
}
#define AVAILABLE   0
#define QPRESENT    1
#define QCLASH      2

bool    queen_spot_available(int x, int y, int pos[][NQUEEN])  
{
    int i = 0, j =0;
    for ( i = 0; i < NQUEEN; i++) {
        // if any queen already placed in same row or same column
        if (pos[x][i] || pos[i][y]) return false;
    }
    for ( i= x, j = y; j >= 0 && i >= 0; i--, j--) {
        if (pos[i][j]) return false;
    }
    for ( i= x, j = y; j < NQUEEN && i >= 0; i--, j++) {
        if(pos[i][j]) return false;
    }
    for ( i= x, j = y; j >= 0 && i < NQUEEN ; i++, j--) {
        if(pos[i][j]) return false;
    }
    for ( i= x, j = y; j < NQUEEN && i < NQUEEN; i++, j++) {
        if (pos[i][j]) return false;
    }
    return true;
}
bool n_queen(int n, int pos[][NQUEEN])
{
    int     i, j;
    int     found = 1;
    for ( i = n ; i < NQUEEN; i++) {
        //  For each row try placing the queen in any of the columns
        found = 0;
        for (j = 0; j < NQUEEN; j++) {
            if (queen_spot_available(i, j, pos)) {
                // Found placement for this row. Find for other rows.
                pos[i][j] = QPRESENT;
                found = n_queen(i+1, pos);
                if (!found) {
                    // Didn't find placement in other rows. 
                    // Look for next placement here. 
                    // undo the previos marking
                    pos[i][j] = AVAILABLE;
                } else {
                    //Placements found in all rows after this, return
                    return found;
                }
            }
        }
        if (!found) {
            // Didn't find any placement for this row, return failure
            return found;
        }
    }
    return found;
}
void print_nqueen(int pos[][NQUEEN])
{
    int i = 0, j = 0;
    for ( i = 0; i < NQUEEN; i++) {
        for (j = 0; j < NQUEEN; j++) {
            printf ("%d, ", pos[i][j]);
        }
        printf("\n");
    }
}
void test_n_queen(int n)
{
    int     pos[NQUEEN][NQUEEN] = {0};
    printf("%s\n", __FUNCTION__);
    n_queen(0, pos);
    print_nqueen(pos);
}
void practise_backtracking(int tc, int argc, char* argv[])
{
    switch(tc) {
        case 1: 
            if (argc)
            test_string_permute(argv[0]);
            break;
        case 2: 
            if (argc) {
                test_n_queen(atoi(argv[0]));
            }
                    break;
        default:
            printf("No test specified\n");
    }
}
