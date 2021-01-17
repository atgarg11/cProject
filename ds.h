#ifndef _DS_H_
#define _DS_H_

#define true 1
#define false 0
#define SSIZE 32

typedef struct listNode_{ 
	struct listNode_	*next;
	struct listNode_	*prev;
	struct listNode_	*random;
	int			int_data;       // integer key, vertex in case of graph
    char        c_data;
	int			end;
	void		*data;
    int         value;
    int         g_weight;   // graph weight for this edge
    int         picked;
}listNode;

typedef struct listHead_ {
    listNode    *head;
}list_head;

typedef struct BinaryTreeNode_ {
	struct BinaryTreeNode_ *left;
	struct BinaryTreeNode_ *right;
	int			value;
	int			count;
    int         hd; // horizontal distance from root root->hd = 0
}BinaryTreeNode, BTNode;


typedef struct trieNode_ {
    struct trieNode_    *left;
    struct trieNode_    *right;
    unsigned int ip;
    unsigned int bit_pos;
    int is_match;
}trieNode, tNode;

BTNode*	allocBTNode(void);
BTNode*	create_binary_tree(BTNode *root, int	*array, int size);
BTNode* 
createBTreeFromInPre(BTNode*    root, int *in, int *pre, int size);
void printBTreeInorder(BTNode  *root) ;
void printBTreePreorder(BTNode  *root) ;
int findIndex(int *ar, int size, int elem);
BTNode  * insert_bt_node(BTNode *root, int val);

/*  List functions  */
listNode*   allocListNode(int data);
listNode*   getNode(listNode    *head, int index);
listNode*   createList(listNode **head, int *data, int size);
int         find_num_list_elements(listNode *head);
listNode*   list_insert_head(listNode   **head, listNode    *node);
listNode*   list_insert(listNode **head, listNode    *node);
listNode    *reverse_list(listNode  **head, int k);
listNode*   print_list(listNode *head);
listNode*   listInsert(listNode **head, int data);
listNode*   dlist_insert(listNode   **head, int data);
listNode*   listInsertHead(listNode **head, int data);

/*  DLL functions   */
void test21_dll_insert();

/*  Heap Functions  */

int*    create_max_heap(int *array, int size);
int*    heap_sort_array(int ar[], int size);
int heap_extract_max(int *array, int *size);
int heap_get_max(int *array, int size);
void heap_increase_key(int *array, int size, int index, int new_key);
void heap_insert_key(int *array, int* size, int key);

/**/
#endif
