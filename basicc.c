#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include "ds.h"
#include "basicc.h"
#include "adt.h"

typedef struct one_ {
    char cb[0];
}one;

void test2_static()
{
    char *a = "hello"; // a is pointer to constant buffer declare as const cha
    char *b = NULL;
    static char *c = NULL;
    char    const *d    = a;

    b = (char*) malloc(10);
    c = (char*)malloc(10);

    printf("data segment string at 0x%x, %s\n", a, a);

    *b='h';*(b+1) = 'e'; *(b+2)='l';
    *(b+3) = 'l'; *(b+4) = 'o';

    *c='h';*(c+1) = 'e'; *(c+2)='l';
    *(c+3) = 'l'; *(c+4) = 'o';
    d = d+1;
    printf("heap example: string at 0x%x, %s\n", b, b);
    printf("heap example: string at 0x%x, %s\n", d, d);
    printf("static example: string at 0x%x, %s\n", c, c);

    //*a = 'y';  // will core dump 
    printf("string at 0x%x, %s\n", a, a);
}

int lprint(int n, ...)
{
    int i = 0, sum = 0;
    va_list args;
    va_start(args, n);
    for (i = 0; i < n; i++) {
        sum += va_arg(args, int);        
    }
    printf("%d\n",sum);
}

void test1()
{
    printf("size of one %d\n", sizeof(one));
}

void test4()
{
    char s[10];
    // remove comments below to test this function
    //gets(s); 
    printf("%s\n", s);
}

void test_null_ta()
{
    null_t  *nulta;
    nulta = (null_t*)malloc(sizeof(null_t) + (5 * sizeof(int)));
    printf("%s, data type:%d, data:%d\n", __FUNCTION__, 
            sizeof(null_t), sizeof(nulta));
}
void practise_basic(int tc, int argc, char* argv[])
{
    int inar[] = {7,6,5,4,3,2,1}; 
    int one= -1, two = -1;
    
    switch (tc) {
        case 1: 
            test1();
            break;
        case 2: 
            test2_static();
            test2_static();
            break;
        case 3: 
            lprint(4, 1, 1,1, 3);
            break;
        case 4: 
            test4();
            break;
        case 5: 
            test5_delete_node();
            break;
        case 6:
            test6_cycle();
            break;
        case 7:
            test7_find_odd_numbers();
            break;
        case 8:
            test8_copy_list_with_random();
            break;
        case 10:
            test10_two_keys();
            break;
        case 11:
            test11_modulo();
            break;
        case 12:
            test_hash();
            break;
        case 13:
            one = system("echo hi");
            printf("Before: %d,, %d\n", one, two);
            two = system("python testloop.py");
            printf("After: %d,, %d\n", one, two);
            break;
        case 14:
            test_null_ta();
            break;
        case 15:
            if (argc >=3)
            test_number_of_occurences
                (atoi(argv[0]), atoi(argv[1]), atoi(argv[2]));
        default :
            break;
    };
    printf("\n");
}
int basic_occurence(int num_to_check, int num)
{
    int count = 0;
    while (num) {
        if ((num % 10) == num_to_check){
            count++;
        }
        num = num/10;
    }
    return count;
}
void test_number_of_occurences(int num, int low, int high)
{
    int count = 0;
    int i = 0;
    for ( i = low ; i < high ; i++) {
        count += basic_occurence(num, i);        
    }
    printf("Number of occurrences:%d \n", count);
}
