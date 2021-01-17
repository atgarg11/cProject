#include <stdio.h>
#include <stdlib.h>
#include "ds.h" 
#include "adt.h" 
#include "basicc.h" 

#define SSIZE 32

/*  Find number of elements in list*/
int find_num_list_elements(listNode *head)
{
    int i = 0;
    listNode    *node = head;
    while (node != NULL) {
        node = node->next;
        i++;
    }
    return i;
}
/*********************/
listNode*   list_insert_head(listNode   **head, listNode    *node)
{
    node->next = *head;
    *head = node;
    return node;
}

/*
    Linked list Functions
 */
listNode*   allocListNode(int data)
{
    listNode    *tmp = (listNode*)malloc(sizeof(listNode));
    tmp->next = tmp->prev = NULL;
    tmp->data = NULL;
    tmp->int_data   = data ;
    return tmp;
}
listNode*   alloc_list_node(int data, int end)
{
    listNode    *tmp = (listNode*)malloc(sizeof(listNode));
    tmp->next = tmp->prev = NULL;
    tmp->data = NULL;
    tmp->int_data   = data ;
    tmp->value = data ;
    tmp->end = end;
    return tmp;
}

/*  
    Print the list and return the last node
 */
listNode*   print_list(listNode *head)
{
    listNode    *node = head;
    listNode    *next = head;
    if (NULL == head) return NULL;
    do {
        printf("%d,",next->value);
        node = next;
        next    = node->next;
    }while (NULL != next && next != head);
    printf("\n");
    return node;
}

listNode*   listInsertHead(listNode **head, int data)
{
    listNode    *tmp = *head;
    listNode    *node   = NULL;

    node    = allocListNode(data);
    node->next = tmp;   
    *head = node;
    return *head;
}

/*  Insert a node after a given node    */
listNode*   list_insert(listNode **head, listNode    *node)
{
    listNode    *tmp = *head;
    listNode    *tmp2 = *head;
    if (node) {
        if (tmp ) {
            tmp2 = tmp->next;
            tmp->next = node;
            node->next = tmp2;
        } else {
            *head = node;
        }
    }
    return node;
}

listNode*   listInsert(listNode **head, int data)
{
    listNode    *node   = NULL;
    node    = allocListNode(data);
    return list_insert(head, node);
}

listNode*   dll_insert(listNode   **head, int data)
{
    listNode    *tmp = *head;
    listNode     *node = allocListNode(data);
    listNode    *next  = NULL;

    if (tmp) { 
        node->next = tmp;
        node->prev = tmp->prev;
        tmp->prev = node;
        node->prev->next = node;
    } else {
        node->next = node->prev = node;
    }
    *head = node;
    return node;
}

listNode*   dll_insert2(listNode  **head, listNode    *node)
{
    listNode    *tmp = *head;
    listNode    *thead = *head;
    listNode    *next = *head;
    listNode    *prev = *head;

    if( tmp) {      // insert the node after the previous of head;
        prev = tmp->prev;
        prev->next = node;
        node->next = tmp;

        node->prev = prev;
        thead->prev = node;
    } else {
        node->next = node->prev = node;
        *head = node;
    }
    return node;
}


/*      Return a linked list node for a given index */
listNode*   getNode(listNode    *head, int index)
{
    int i = 0; 
    listNode    *node = head;
    while (NULL != node) {
        if ( index == i++) break;;
        node = node->next;
    }
    return node;
}

listNode* delete_node(listNode  *node)
{
    if (NULL == node) return node;

    listNode    *tmp = node->next;
    if (tmp) {
    node->int_data = tmp->int_data;
    node->next = tmp->next;
    free(tmp);
    } else { 
        free(node);
        node = NULL;
    }
    return node;
}
/*  Create  a `linked list from an array. Insert the new element at the 
    head of the list
 */
listNode* createList(listNode **head, int *data, int size)
{
    int i = 0;
    for (i = 0; i < size; i++) {
        listInsertHead(head, data[i]);
    }
    return *head;
}

/*  Reverse a given linked list */
listNode    *reverse_list(listNode  **head, int k)
{
    listNode    *tmp = NULL, *node = NULL;
    listNode    *tmp2 = NULL;
    int i  = 0;
    node = *head;
    if (head && *head ) {
        if( 0 == k) { 
            k = find_num_list_elements(*head);
        } else {
            // find the head
            tmp = *head;
            for ( i = 0 ; i < k ; i++) {
                tmp = tmp->next;
            }
        }
        // tmp points to the remaining list not to be reversed
        for ( i = 0 ; i < k && node; i++) {
            tmp2 = node->next;
            list_insert_head(&tmp, node);
            node = tmp2;
        }
    }
    *head = tmp;
    return tmp;
}
listNode*   test2_test_reverse_group(int k)
{
    int inar[] = {7,6,5,4,3,2,1}; 
    int number = 0, num_of_groups = 0;
    listNode    *tmp = NULL, *node = NULL;
    listNode    *head = NULL, *tmp2 = NULL;
    int i = 0, j = 0;

    createList(&head, inar, sizeof(inar)/sizeof(int));
    number = find_num_list_elements(head);
    print_list(head);
    if (number < k) {
        print_list(head);
        return head;
    } else {
        num_of_groups = number / k;
        for ( j = 0; j < num_of_groups; j++) {
            tmp = head;
            tmp2 = NULL;
            for (i = 0 ; i < ((num_of_groups-j-1) *k) ; i++) {
                tmp2 = tmp;
                tmp = tmp->next;
            }
            if (tmp2) tmp2->next = reverse_list(&tmp, k);
            else reverse_list(&tmp, k);
        }
    }
    print_list(tmp);
}

int* oddNumbers(int l, int r, int* result_size) {
    int* res = NULL;
    int plus1 = 0, first = 0, i;
    if ((l%2) || (r%2)) {
        plus1 = 1;
    }
    if(l%2) { first = l;} 
    else { first = l+1; }

    *result_size = ((r-l)/2)+plus1;
    res = (int*)malloc(*result_size*sizeof(int));
    for ( i = 0 ; i < *result_size ; i++ ) {
        res[i] = first;
        first = first+2;
    }
    return res;
}
void test7_find_odd_numbers()
{
    int res, i;
    int *arr;
    arr = oddNumbers(2,5,&res);  
    for ( i = 0 ; i < res; i ++) { 
    printf("%d,",arr[i]);
    }
}

void   test5_delete_node()
{
    listNode    *head = NULL;
    int data[] = {1,2,3,4,5,6};
    createList(&head, data, sizeof(data) / sizeof(int));
    print_list(head);
    delete_node(head);
    print_list(head);
}
char* check(listNode* head) {
    listNode *tmp1 = head;
    listNode  *tmp2 = head;
    int n = 0;

    if (NULL == tmp1) return "No";          // no element in the list
    if (NULL == tmp1->next) return "No";    // only one element
    if (NULL == tmp1->next->next) return "No";  // only two elements with no loop

    tmp2 = tmp1->next->next;

    while (tmp2 && n++ < 1000) {

        if (tmp1 == tmp2) return "Yes";

        tmp1 = tmp1->next;

        if (tmp2->next) tmp2 = tmp2->next->next;
        else return "No"; // Null terminated list
    }
    // if (tmp1 == tmp2) return "Yes";
    return "No";
}
void test6_cycle()
{
    int i;
    listNode    *head = NULL;
    listNode    *tmp = NULL;
    int data[] = {1,2};
    createList(&head, data, sizeof(data) / sizeof(int));
    tmp = getNode(head, 1);
    tmp->next = head;

    printf("%s\n", check(head));

}

void print_list_random(listNode *head)
{

    listNode    *node = head;
    listNode    *next = head;

    while (NULL != next) {
        printf("%d,",next->random->int_data);
        node = next;
        next    = node->next;
        if(next == head) break;
    } 
    printf("\n");
}
listNode    *copy_list_with_random(listNode *head)
{
    listNode    *tmp = head, *r = NULL;
    listNode    *head2 = NULL;
    listNode    *tail = NULL;
    print_list_random(head);
    while (tmp) {
        tail = list_insert(&tail, allocListNode(tmp->int_data));
        tail->int_data = tmp->int_data;
        tail->random = tmp->random;
        r = tmp;
        tmp = tmp->next; 
        r->next = tail;
        if (NULL == head2) head2 = tail;
    }
    tmp = head2;
    while (tmp) {
        if (tmp->random && tmp->random->random) 
            tmp->random = tmp->random->random->next;
        tmp = tmp->next;
    }
    print_list(head2);
    print_list_random(head2);
}
void test8_copy_list_with_random()
{
    listNode    *head  = NULL;
    listNode    *tmp  = NULL;
    tmp = listInsert(&head, 1);
    tmp->random = tmp;
    tmp = listInsert(&tmp, 2);
    tmp->random = tmp;
    tmp = listInsert(&tmp, 3);
    tmp->random = tmp;

    copy_list_with_random(head);    
}

listNode    *even_odd(listNode    *head)
{
    listNode    *ehead = NULL, *etail = NULL;
    listNode    *ohead = NULL, *otail = NULL;
    listNode    *tmp = NULL, *next = NULL;

    tmp = head;
    while (tmp) { 
        if (tmp->int_data % 2 == 0) {
            //even case
            next = tmp->next;
            etail = list_insert(&etail, tmp);
            if (NULL == ehead ) ehead = tmp;
        } else {
            next = tmp->next;
            otail = list_insert(&otail, tmp);
            if (NULL == ohead ) ohead = tmp;
        }
            tmp = next;
    }
    list_insert(&etail, ohead);
    otail->next = NULL;
    return ehead;
}

void test9_even_odd(listNode    *head)
{
    listNode    *tmp = NULL;
    print_list(head);
    tmp = even_odd(head);
    print_list(tmp);
}

listNode    *insert_sorted_list_2(listNode* head, int start, int end)
{
    listNode    *tmp = head, *n = NULL;
    if (NULL == tmp) {
        tmp = alloc_list_node(start, end);
        return tmp;
    }
    while (tmp) {
        if (start > tmp->end) {
            if (NULL == tmp->next) { 
                list_insert(&tmp, alloc_list_node(start, end)); 
                return head;
            } else if (end < tmp->next->int_data) {
                list_insert(&tmp, alloc_list_node(start, end)); 
                return head;
            }
        } else {
            tmp->int_data = start < tmp->int_data ? start: tmp->int_data;
            tmp->end = end >tmp->end ? end : tmp->end;
            while (tmp->next) {
                if (tmp->end < tmp->next->int_data);
                else {
                    tmp->end = tmp->end > tmp->next->end ? tmp->end : tmp->next->end;
                    tmp->next = tmp->next->next;
                }
            }
        }
        if (end < tmp->int_data) {
            n = alloc_list_node(start, end);
            n->next = head;
        }
        tmp = tmp->next;
    }
}
void print_list_2(listNode  *head)
{
    listNode    *node = head;
    listNode    *next = head;

    while (NULL != next) {
        printf("[%d,%d],",next->int_data, next->end);
        node = next;
        next    = node->next;
        if(next == head) break;
    } 
    printf("\n");
}

void test10_two_keys()
{
    listNode    *node = NULL;
    node = insert_sorted_list_2( node, 1,2);
    node = insert_sorted_list_2( node, 6,8);
    node = insert_sorted_list_2( node, 3,4);
    node = insert_sorted_list_2( node, 5,7);
    node = insert_sorted_list_2( node, 2,7);
    print_list_2(node);
}
void  test11_modulo() {
    //code
    int no_cases =0, size = 0;
    int *res, i, j, elem,k;
    listNode    *list = NULL, *head = NULL, *tmp2 = NULL;
    scanf("%d", &no_cases);
    res = (int*) malloc(no_cases * sizeof(int));

    for ( i = 0; i < no_cases; i++) {
        scanf("%d", &size);
        for ( j = 0; j < size ; j++ ) {
            scanf("%d", &elem);
            list = listInsert(&list, elem); 
            if (NULL == head) head = list;
        }
        scanf("%d", &k);
        list = head;j = 0;
        while (list) {
            j++;
            if ( 0 == j%k) tmp2 = list;
            list = list->next;
        }
        if (tmp2) res[i] = tmp2->int_data;
    }

    for (i = 0 ; i < no_cases; i++) {
            printf("%d\n", res[i] );
        }
}

/***************    Practice list ****/

void practise_list(int tc)
{
    int inar[] = {7,6,5,4,3,2,1}; 
    listNode    *head = NULL, *tmp2 = NULL;

    createList(&head, inar, sizeof(inar)/sizeof(int));
    
    switch (tc) {
        case 1: 
            test1_test_stack();
            break;
        case 2: 
            test2_test_reverse_group(2);
            break;
        case 3: 
            test3_queue();
            break;
        case 4: 
            test4_queue_using_stack();
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
            test9_even_odd(head);
            break;
        case 10:
            test10_two_keys();
            break;
        case 11:
            test11_modulo();
            break;
        case 21:
            test21_dll_insert();
            break;
        case 22:
            test_deque();
            break;
        default :
            break;
    };
    printf("\n");
}

void test21_dll_insert()
{
    listNode    *head = NULL;
    listNode    *node = alloc_list_node(1, 0);
    listNode    *node2 = alloc_list_node(2, 0);
    listNode    *node3 = alloc_list_node(3, 0);
    listNode    *node4 = alloc_list_node(4, 0);

    dll_insert2(&head, node);
    dll_insert2(&head, node2);
    dll_insert2(&head, node3);
    print_list(head);
}
