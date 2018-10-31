#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include "ds.h"
#include "util.h"
#include "basicc.h"

int main(int argc, char *argv[])
{
	int ar[] = {1,2,3, 4, 5, 6, 7};
	int inar[] = {3,2,1}; 
	int inar1[] = {4,2,5,1,6,7,3,8};
	int prear[] = {1,2,4,5,3,7,6,8};
    int list1[] = {13,12,11};
    int list2[] = {23,22,21};
    int *ip;
    char    str[] = {'a','b','c', 'd','e'};
    char    str1[] = {'1','2','3', '4','5'};
    char    s[32];
	printf("Alright another interview preparation\n");

    /* 
       ******* Binary Tree *******
    
    *************/
    switch (argc) {
        case 1:
            break;
        case 2:
            break;
        case 3:
        default: 

            if (!strcmp(argv[1], "misc")) {
                practise_basic(atoi(argv[2]));
            } else if (!strcmp(argv[1], "list")) {
                practise_list(atoi(argv[2]));
            } else if (!strcmp(argv[1], "trees")) {
                practise_trees(atoi(argv[2]));
            } else if (!strcmp(argv[1], "heaps")) {
                practise_heaps(atoi(argv[2]));
            } else if (!strcmp(argv[1], "arrays")) {
                practise_arrays(atoi(argv[2]));
            } else if (!strcmp(argv[1], "dp")) {
                practise_dps(atoi(argv[2]), argc, argv);
            } else if (!strcmp(argv[1], "graphs")) {
                practise_graphs(atoi(argv[2]), argc, argv);
            }
            break;
    };

    /* 
     *********  Strings & Arrays ********
    gets(s);
    printf("\n reversed string is %s \n", reverseString(s));

    ***************/

    /*
        *******  sorting  ******
    ip = merge_sort(inar, sizeof(inar)/sizeof(int));

    **************/

    

    /*
        ****double linked list practice *******

    dlist_insert(&head, 2);
    dlist_insert(&head, 3);
    dlist_insert(&head, 4);
    printList(head);

     **********************/

    /*
     ****** Tree Practice *****
            Trie code

    create_trie(troot);
    if (find_in_trie(troot, ntohl(get_ip("192.168.2.7")))) { 
        printf("IP found in trie\n");
    } else { 
        printf("IP not found in trie\n");
    }

     ***************/
	return 0;

}
