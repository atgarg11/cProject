#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

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

int* merge_sort_merge(int *one, int* two, int size1, int size2) 
{
    int tmp[32] = {0};
    int i, j , loop;
    int max = 0;

    for (i = 0, j = 0, loop = 0; loop < (size1 + size2); ) {
        if ( size1 == i) {
            max = two[j++];
        }
        else if (size2 == j) {
            max = one[i++];

        }
        else if (one[i] < two[j]) {
            max = one[i++];
        }
        else { 
            max = two[j++];
        }
        tmp[loop++] = max;
    }
    memcpy(one, tmp, (size1+size2)*sizeof(int));
    return one;
}
int* merge_sort(int *in, int size)
{
    int *first, *sec;
    int i = 0, j = 0;

    if ( 1 == size) return in;

    i = size/2;

    first = merge_sort(in,i);
    sec = merge_sort(in+i, size-i);

    return ( merge_sort_merge(first, sec, i, size-i));
} 
unsigned int get_ip(char *ip_string)
{
    struct in_addr  addr;
    inet_pton(AF_INET, ip_string, &addr);
    return addr.s_addr;
}
