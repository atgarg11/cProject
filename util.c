#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include "util.h"

int compareInts(int a, int b)
{
 return (a > b ? 1 : 0);
}

void swapChar(char  *str, int x, int y)
{
    char tmp =  str[x]; 
    //*(str+x) = *(str+y);
    //*(str+y) = tmp;
    str[x] = str[y];
    str[y] = tmp;
}
char* reverseString(char *str)
{
    int s = strlen(str);
    int x = 0 , y = s-1;
    while (x < y) {
        swapChar(str, x++, y--);
    }
    return str;
}

char* reverseWord(char* str, int len)
{
    int x = 0 , y = len-1;
    while (x < y) {
        swapChar(str, x++, y--);
    }
    return str;

}

char* reverseStringWords(char* str)
{
    return NULL;
}

unsigned int get_ip(char *ip_string)
{
    struct in_addr  addr;
    inet_pton(AF_INET, ip_string, &addr);
    return addr.s_addr;
}

/*  Jan 5th 2019    */
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void print_array(int array[], int size)
{
    int i = 0;
    printf("quick sorted array: ");
    for ( i = 0 ; i < size; i++) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}
