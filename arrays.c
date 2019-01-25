#include <stdio.h>
#include <stdlib.h>
#include "ds.h"
#include "tree.h"

void  test1_perfect() {
    //code
    int no_cases =0, size = 0;
    int *array;
    int *res, i, j;
    scanf("%d", &no_cases);
    res = (int*) malloc(no_cases * sizeof(int));

    for ( i = 0; i < no_cases; i++) {
        scanf("%d", &size);
        array = (int*)malloc(size * sizeof(int));
        for ( j = 0; j < size ; j++ ) {
            scanf("%d", array+j);
        }
        res[i] = 1;
        for ( j = 0 ; j < (size+1)/2 && res[i]; j++) {
            if (array[j] != array[size-1-j])  {
                res[i]=0; break;
            }
        }
    }

    for (i = 0 ; i < no_cases; i++) {
        if (res[i]) {
            printf("%s\n", "PERFECT");
        } else {
            printf("%s\n", "NOT PERFECT");
        }
    }
}
BTNode* bt_preorder(BTNode  *root, int* i, int k, BTNode **node)
{
    if (NULL == root) {                                                         
        return NULL;                                                                 
    }              
    if (*i == k) return NULL;
    if (root->left ) bt_preorder(root->left, i, k, node); 
    if (root->count == 0) {
        *i = *i+1;    
        if (*i ==k) { 
            *node = root;
            return NULL;
        }
    }
    if (root->right) bt_preorder(root->right, i , k, node);                                             
    return NULL;
}     
void test2_missing_k() 
{
    int no_cases =0, size = 0;
    int n1, n2, k;
    BTNode  *root = NULL, *node = NULL;
    int *array, *array2;
    int *res, i, j;
    scanf("%d", &no_cases);
    res = (int*) malloc(no_cases * sizeof(int));

    for ( i = 0; i < no_cases; i++) {
        scanf("%d %d %d", &n1, &n2, &k);
        array = (int*)malloc(n1 * sizeof(int));
        array2 = (int*)malloc(n2 * sizeof(int));
        for ( j = 0; j < n1 ; j++ ) {
            scanf("%d", array+j);
        }
        for ( j = 0; j < n2 ; j++ ) {
            scanf("%d", array2+j);
        }
        root = create_binary_tree(NULL, array, n1);
        for (j = 0 ; j < n2; j++) {
            node = find_bt_node(root, (int)array2[j]);
            if (node) node->count++;
            node = NULL;
        }
        j = 0; node = NULL;
        bt_preorder(root, &j, k, &node);
        if (node) {
            res[i] = node->value;
        } else {
            res[i] = -1;
        }
    }
    for ( i = 0 ; i < no_cases; i++) {
        printf("%d\n", res[i]);
    }
}

int test3_xor() {
    //code

    int no_cases =0, size = 0;                         
    int *array, tmp;                                        
    int *res, i, j, k, number = 0;                                    
    scanf("%d", &no_cases);                            
    res = (int*) malloc(no_cases * sizeof(int));       

    for ( i = 0; i < no_cases; i++) {                  
        scanf("%d %d", &size, &number);             
        res[i] = 0;
        array = (int*)malloc(size * sizeof(int));      
        for ( j = 0; j < size ; j++ ) {                
            scanf("%d", array+j);                      
        }

        for ( j = 0; j < size; j++) {
            if (0 == (number ^ array[j])) {
                res[i]++; continue;
            }
            for ( k = j+1; k < size; k++) {
                tmp = ((number ^ array[j]) ^ array[k]);
                if (0 == tmp) res[i]++;
            }
        }
    }//no of test cases
    for ( i = 0; i < no_cases; i++) {
        printf("%d\n", res[i]);
    }
}
int endian()
{
    int x = 0x01020304;
    char    *c;
    c = (char*)&x;
    int end = ((x & 0xFF) == *c) ? 1: 0;
    printf("%s\n", end ?  "Little endian": "BIG endian");
    return 0;
}

list_with_two_keys()
{
}
void largest_sub_array_01(int *array, int count)
{
    int i = 0, tmp = 0;
    for (i = 0 ; i < count; i++) {
        switch(array[i]){
            case 0: tmp++;
                    break;
            case 1:
                    tmp--; break;
            default:
                    break;
        }
    }
    printf("Size of the largets array:%d\n", (count -tmp));
}
void practise_arrays(int tc)
{
    int ar[] = {0, 0, 1, 1, 0, 0, 0};
    switch (tc) {
        case 1: 
            test1_perfect();
            break;
        case 2: 
            test2_missing_k();
            break;
        case 3: 
            test3_xor();
            break;
        case 4: 
            endian();
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
        case 9:
            largest_sub_array_01(ar, sizeof(ar) / sizeof(int));
        default :
            break;
    };
    printf("\n");
}

