#include <stdio.h>
#include <stdlib.h>
#include "strings.h"
#define no_of_chars 256
#define false (0)
#define true (1)
/*  THis function expects two inputs
    pattern, text string    */
void practise_strings(int tc, int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage <text> <pattern>\n");
        return;
    }
    switch(tc) { 
        case 1: // naive string match
            naive_string_match(argv[0], argv[1], strlen(argv[0]), strlen(argv[1]));
        default: 
            printf("String preparation\n");
            break;
    }
}

void test_chars()
{
    int ar[256] = {0};
    ar['a'] = 22;
    printf("%d\n", ar['a']);
}
/*  Dec 15, 2018. Finite string automata  (FSA)   */
/*  fsa_transition_function() takes the pattern and the input char set, 
    and provides a two dimensional output array  represeting 
    the current state, trigger and the resulting state i
 
 */
int* fsa_transition_function(char    *pattern, int len, int fsm[][no_of_chars])
{
    int i = 0;
    for ( i = 0; i < len; i++) { 
        fsm[i][pattern[i]];
    }
    return NULL;
}
int pattern_match(char* text, char *pat, int len)
{
    int i = 0;
   if (!text || ! pat) {
       return false; 
   }
   for ( i = 0 ; i < len; i++) {
       if (text[i] == pat[i]) { 
           continue;
       } else {
           return false;
       }
   }
   return true;
}
/*  Naive String match  */
int naive_string_match(char* text, char * pat, int tlen, int plen)
{
    int i = 0; 
    for ( i = 0 ; i < tlen-plen+1 ; i++) {
        if (text[i] == pat[0]) {    // at shift i, first char match. match rest
            if (pattern_match(text+i, pat, plen)) {
                printf("Pattern: %s found at :%d\n", pat, i);
            }
        }
    }
}
