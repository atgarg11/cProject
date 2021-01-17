#include <stdio.h>
#include <stdlib.h>
#include "ds.h" 
#include "adt.h" 
#include "tree.h" 
#include "sort.h" 
#include <iostream>
#include <queue>
using namespace std;
/*
    BInary Tree Functions 
*/
BTNode*	allocBTNode(void) 
{
	BTNode	*tmp = (BTNode*)malloc(sizeof(BTNode));
	tmp->value = 0;
	tmp->left = tmp->right = NULL;
	return tmp;
}

/*	Create a binary tree for int array of size size	i
    if you think about it, creating a binary tree from sorted 
    array is actually creating a btree from in ordered array
 */

BTNode*	create_binary_tree(BTNode *root, int	*array, int size)
{
	int i = 0, index = 0;
	
	if (0 == size) return root; 

	if (NULL == root) {
		root = allocBTNode();
	}

	/*	Assuming array is sorted */

	if (1 == size) {
		root->value = array[i];
		return root;
	}
    
    /*  Find the root   */
	index = size%2 ? size/2: (size/2-1);
	root->value = array[index];

    /*  Find the left & right sub trees */
	root->left = create_binary_tree(root->left, array, index);
	root->right = create_binary_tree(root->right, array+index+1, size-index-1);
		
	return root;
}

BTNode*  createBTreeFromInPre
    (BTNode*    root, int *in, int *pre, int size)
{
    int i = 0, index = 0;
    if (0 == size) return root;

    if(NULL == root) {
        root = allocBTNode();
    }
     
    if (1 == size) {
        root->value = in[i];
        return root;
    }
    
    root->value = pre[i];
    index = findIndex(in, size, root->value);

    root->left = createBTreeFromInPre(NULL, in, pre+1, index);
    root->right= createBTreeFromInPre(NULL, in+index+1, pre+index+1, size-index-1);
    return root;
}

void print_bt_inorder(BTNode  *root) 
{
    if (NULL == root) { 
        return;
    }
    if(root->left) print_bt_inorder(root->left);
    printf("%d,",root->value);
    if(root->right) print_bt_inorder(root->right);
}

void print_bt_preorder(BTNode  *root) 
{
    if (NULL == root) { 
        return;
    }
    printf("%d,",root->value);
    print_bt_preorder(root->left);
    print_bt_preorder(root->right);
}

/*   Find index of an element in an array   */
int findIndex(int *ar, int size, int elem)
{
    int i = 0;
    for(i = 0; i < size; i++) {
        if (ar[i] == elem) {
            break;
        }
    }
    if (i == size) return -1; // error condition
    return i;
}

void print_bt_level_order(BTNode    *root, int level )
{
    int i;

    if (NULL == root ) return;

    if(root->left) printf("%d,", root->left->value);
    if(root->right) printf("%d,", root->right->value);
    print_bt_level_order(root->left, level-1);
    print_bt_level_order(root->right, level-1);
}
void swap_bt_children(BTNode *root)
{
    BTNode  *tmp_left = NULL, *tmp_right = NULL;
    if (NULL == root) return;

    tmp_left = root->left;
    root->left = root->right;
    root->right = tmp_left;
}
/*  make the left child right and vice - versa*/
BTNode *invert_bt(BTNode    *root)
{
    if( NULL == root) return root;
    swap_bt_children(root);
    invert_bt(root->left);
    invert_bt(root->right);
}

int bst(BTNode *root, int *min, int *max, int *size) 
{
    int lmax = 0, rmin = 0;
    int lbst = 0, rbst = 0;

    if (NULL == root) return true;
    if ((root->left == root->right) && (root->left  == NULL)) { 
        *min = root->value ; *max = root->value; 
        (*size)++;
        return true;
    }
    if (root->left) {
        lbst = bst(root->left, min, &lmax, size);
    } else {
        lbst = true; *min = root->value; 
        lmax = root->value;
    }

    if (root->right) {
        rbst = bst(root->right, &rmin, max, size);
    } else { 
        rbst = true; rmin = root->value; *max = root->value;
    }
    if (lbst && rbst) {
        if (root->value >= lmax && root->value <= rmin) {
            (*size)++;
            return true;
        } else {
            return false;
        }
    }
    return false;
}

void test3_bst(BTNode *root)
{
    int min, max ;
    int size = 0;
   // invert_bt(root);
    if (bst(root, &min, &max, &size)) { 
        printf("BST with size: %d\n", size);
    } else {
        printf("Not a BST\n");
    }
}

int is_leaf(BTNode    *root)
{
    BTNode  *tmp = NULL;
    if ( NULL == root) return false;
    if ( NULL == root->left && NULL == root->right) {
        return true;
    }
    return false;
}

/*  Get the leaves for a binary tree    */
BTNode* get_bt_leaves(BTNode   *root)
{
    if (NULL == root) return root;

    if (is_leaf(root)) { 
        printf ("%d,",root->value);
        return NULL;
    }
    else {
        root->left = get_bt_leaves(root->left);
        root->right = get_bt_leaves(root->right);
    }
    return root;
}

/*  Get the height of a binary tree */
int get_bt_height(BTNode    *root)
{
   int h = 0, lh = 0, rh = 0; 
   if (NULL == root) return h;
    
   lh = get_bt_height(root->left);
   rh = get_bt_height(root->right);
   h = lh > rh ? lh : rh;
   return (h+1);
}
BTNode  *bt_min(BTNode *root)
{
    if (NULL == root) return root;
    if (NULL == root->left ) return root;
    else return bt_min (root->left);
}
BTNode* find_bt_node(BTNode *root, int value)
{
    if ( root) {
        if (value == root->value) 
            return root;
        else if (value < root->value) 
            return find_bt_node(root->left, value);
        else 
            return find_bt_node(root->right, value);
    }
}
BTNode* get_inorder_succeessor(BTNode   *root, BTNode   *node)
{
    BTNode  *succ = NULL, *succ2 = NULL;
    if ( NULL == root || NULL == node) 
        return NULL;
    
    if (is_leaf(root)) return NULL;

    if (node->right) return bt_min(node->right);

    if (node->value < root->value ) {
        succ = root;   
        // root can be a successor 
        // for left nodes only
        succ2 = get_inorder_succeessor(root->left , node);
            if (succ2) return succ2;
    }
    if (succ) return succ;

    return get_inorder_succeessor(root->right, node);  

}
BTNode *get_sum_path(BTNode *root, int sum)
{
    BTNode  *tmp = NULL;
    if (NULL == root) return root;

    if (root->value == sum && is_leaf(root)) {
        return root;
    }
    if (root->left) { 
        tmp = get_sum_path(root->left, sum-root->value);
        if (tmp) return tmp;
    } 
    if (root->right) {
        tmp = get_sum_path(root->right, sum-root->value);
    }
    return tmp;
}   
void test6_inorder_succ(BTNode  *root, int value)
{
    BTNode  *tmp = NULL, *tmp2 = NULL;
    if (NULL == root) { printf("NULL tree\n");}
    tmp = bt_min(root);
    while (tmp) {
        printf ("%d,", tmp->value);
        tmp = get_inorder_succeessor(root, tmp);
    }
}

/******************************/
listNode* get_largest_seq(BTNode* root, listNode    **seq)
{
    listNode    *lnode = NULL;
    int         length = 0;
    if (NULL == root ) return lnode;

    lnode = *seq; 

    if (root->left != NULL) {
        *seq = get_largest_seq(root->left, &lnode);
    }
    lnode = listInsert(&lnode, root->value);

    if (root->right != NULL) {
        *seq = get_largest_seq(root->right, &lnode);
    }
    return lnode;
}
void test8_largest_seq(BTNode   *root)
{
    listNode    tmp;
    tmp.next = NULL; tmp.int_data = 0;
    listNode    *lnode = &tmp;
    get_largest_seq(root, &lnode);
    print_bt_inorder(root);
    print_list(lnode);
}
void bt_top_view_left(BTNode *root)
{
    if (NULL == root) return;
    if (root->left) {
        bt_top_view_left(root->left);
    }
    printf("%d,", root->value);
}
void bt_top_view_right(BTNode *root)
{
    if (NULL == root) return;
    printf("%d,", root->value);
    if (root->right) {
        bt_top_view_right(root->right);
    }
}

void bt_top_view(BTNode *root)
{
    if ( NULL == root) return;
    if (root->left) {
        bt_top_view_left(root->left);
    }
    printf("%d,", root->value);
    if (root->right) {
        bt_top_view_right(root->right);
    }
}
void test9_top_view(BTNode  *root)
{
    BTNode  *tmp = NULL;
    BTNode  n;
    n.value = 1;
    n.left = NULL;
    n.right = NULL;
    tmp = find_bt_node(root, 3);
    tmp->left= &n;
    bt_top_view(root);
}
BTNode*    closest(int val, BTNode *v1, BTNode *v2)
{
    if ((val - v1->value) > (v2->value - val) )
        return v2;
    else 
        return v1;
}
BTNode* bt_closet_value(BTNode    *root, int val, BTNode   *lval, BTNode *rval)
{
    BTNode  *tmp = root;
    if (NULL == tmp) return tmp;
    if (val < root->value) {
        rval = root;
        if (root->left)  {
            return bt_closet_value(root->left, val, lval, rval);
        } else { 
            if (lval && rval) return closest(val, lval, rval) ;
            return rval;
        }
    } 
    else if (val == root->value) {
        return root;

    } else {
        lval = root;
        if (root->right)  {
            return bt_closet_value(root->right, val, lval, rval);
        } else { 
            if (lval && rval) return closest(val, lval, rval) ;
            return lval;
        }
    }
    return NULL;
}
void test_closest(BTNode *root)
{
    BTNode  *l = NULL, *r = NULL;
    BTNode  *tmp = find_bt_node(root, 7);
    tmp->value = 20;
    l = allocBTNode();
    l->value = 11;
    tmp->left = l; l = NULL;

    tmp = bt_closet_value(root, 25, l, r); 
    printf("%d,", tmp->value);
}
int is_left_heavy(BTNode    *root)
{   
    int lh = 0, rh = 0, d = 0;
    if(root->left) lh = get_bt_height(root->left);
    if(root->right) rh = get_bt_height(root->right);
    d = lh-rh;
    if ( d >=2 ) return 1;
    else if (d <= -2) return -1;
    return 0;
}
BTNode  *rotate_right(BTNode    *node)
{
    BTNode  *tmp = node->left;
    node->left->right = node;
    node->left = NULL;
    return tmp;
}
BTNode  *balance_bt(BTNode   *root)
{
    BTNode  *node = root;
    if (NULL == node) return root;
    if ( 1 == is_left_heavy(node)) {
        if (node->left->right) {
        }
        else {
            rotate_right(node);
        }
    }
}
int count_bt_nodes(BTNode *root)
{
    int count = 0;
    if (NULL == root) return count;
    if (root->left) {count += count_bt_nodes(root->left);    } 
    count++;
    if (root->right) count+= count_bt_nodes(root->right);
    return count;
}
/********************************/
void practise_trees(int tc, int argc, char* argv[])
{
    BTNode  *root = NULL;
    int ar[] = {1,2,3, 4, 5, 6, 7};
    root = create_binary_tree(NULL, ar, sizeof(ar)/sizeof(int));
    int c  = 0;
    vector<int> path;

    switch (tc) {
        case 1:     // Tree traversals
            print_bt_inorder(root);
            printf("\n");
            print_bt_preorder(root);
            printf("\n");
            print_bt_level_order(root, 2);
            break;
        case 2:     // Inverting a binary tree 
            invert_bt(root);
            print_bt_level_order(root, 2);
            break;
        case 3:     
            /* finding the larges BST in a binary 
               tree refer tushar roy  video
             */
            test3_bst(root);
            break;
        case 4: /*  Get the leaves of a binary tree */
            get_bt_leaves(root);
            print_bt_inorder(root);
            break;
        case 5: /*  Get the height of a binary tree */
            printf("height: %d\n", get_bt_height(root));
            break;
        case 6:
            test6_inorder_succ(root, 7);
            break;
        case 7:
            printf("%d",get_sum_path(root,15)->value); 
        case 8: 
            test8_largest_seq(root);
            break;
        case 9: 
            test9_top_view(root);
            break;
        case 10: 
            test_closest(root);
            break;
        case 11: 
            c = count_bt_nodes(root);
            printf("%d\n",c);
        case 12: 
            root = test12_removal(root, 5);
            root = test12_removal(root, 6);
            break;
        case 13: 
            test_vertical(root);
            break;
        case 14: 
            test_left_leaf_sum(root);
            break;
        case 15: 
            insert_bt_node(root, 8);
            insert_bt_node(root, 9);
            node_without_sibling(root);
            break;
        case 16: 
            bt_extreme_level_nodes(root);
            break;
        case 21: 
            test_bt_dll(root);
            break;
        case 22:
            test_merge_bts();
            break;
        case 23:
            test_normal_to_balance_tree();
            break;
        case 24:
            test_level_sum();
            break;
        case 25:
            test_tree_from_preorder(); 
        case 26:
            root = create_bt();
            print_bt_inorder(root);
            print_path_given_sum(root, atoi(argv[0]));  
            break;
        case 27:
            root = create_bt();
            print_all_paths(root, path); 
            break;
        case 28:
            root = bt_create_bt(argc, argv);
            print_all_paths(root, path); 
            break;
        case 29:
            cout << (same_tree(argc, argv) ? 
                    "Identical Trees" : " Non identical");
            break;

        default :
            break;
    };
    printf("\n");
}

BTNode  *remove_bt_node(BTNode  *root, int val)
{
    BTNode  *node = root, *tbr;
    int tmp ;
    if ( NULL == node) return root;

    if (val < node->value && (node->left)) {
        node->left = remove_bt_node(node->left, val);
    } else if (val == node->value) {
        if (node->right && node->left) { 
            tbr = bt_min(node->right);
            tmp = tbr->value;
            node->right = remove_bt_node(node->right, tbr->value);
            node->value = tmp;
        } else  if (node->right) node = node->right;
        else if (node->left) node = node->left;
        else node = NULL;
        return node;
    }

    if (val > node->value && (node->right)) {
        node->right = remove_bt_node(node->right, val);
    }
    return node;
}

BTNode  *test12_removal(BTNode  *root, int val)
{
    BTNode  *tmp ;
    tmp = remove_bt_node(root, val);
    print_bt_level_order(tmp, 0);
    printf("\n");
    return tmp;
}
BTNode  * insert_bt_node(BTNode *root, int val)
{
    BTNode *node = NULL;
    if (NULL == root)  {
        node = allocBTNode();
        node->value  = val;
        node->hd = 0;
        return node;
    }
    if ( val == root->value) return root;
    if ( val < root->value) {  
        if (root->left) insert_bt_node(root->left, val);
        else  {
            root->left = allocBTNode(); 
            root->left->value = val;
            root->left->hd = root->hd -1;
        }
    } else { 
        if (root->right) insert_bt_node(root->right, val);
        else  {
            root->right = allocBTNode(); 
            root->right->value = val;
            root->right->hd = root->hd +1;
        }
    }
    return root;
}
void populate_bt_hd(BTNode  *root)
{
    if (NULL == root) return ;
    if ( root->left) {
        root->left->hd = root->hd -1;
        populate_bt_hd(root->left);
    }
    if (root->right) { 
        root->right->hd = root->hd +1;
        populate_bt_hd(root->right);
    }
}
void print_vertical_order(BTNode    *root, hash_t *hash)
{
    if (NULL == root) return ;
    hash_insert(hash, root->hd, root->value);
    print_vertical_order(root->left, hash);
    print_vertical_order(root->right, hash);

}
void test_vertical(BTNode   *root)
{
    hash_t  *hash = init_hash(8, func1);
    populate_bt_hd(root);
    print_vertical_order(root, hash);
    print_hash(hash);
}
/*  Test case 14: SUm of left leaves of a BT    */
int left_leaf_sum(BTNode    *root)
{
    int sum = 0;
    if (NULL == root) return sum;
    if (is_leaf(root)) return  sum ;

    if (root->left) {
        if (is_leaf(root->left)) {
            sum += root->left->value; 
        } else { sum += left_leaf_sum(root->left); }
    }
    if (root->right) {
        sum += left_leaf_sum(root->right);
    }
    return sum;
}
void test_left_leaf_sum(BTNode  *root)
{
    printf(" Left leaf sum is %d: \n", left_leaf_sum(root));
}

/*  Test case 15 node withour siblings  */
void node_without_sibling(BTNode    *root)
{
    if (NULL == root) return ;
    if (is_leaf(root)) return;

    if ((root->left) && (root->right ))  {
        node_without_sibling(root->left);
        node_without_sibling(root->right);
    }

    else if (root->left) {
        printf("%d,",root->left->value);
        node_without_sibling(root->left);
    }
    else if (root->right) {
        printf("%d,",root->right->value);
        node_without_sibling(root->right);
    }
}

BTNode*   bt_dll_insert(BTNode  **head, BTNode  *node)
{
    BTNode    *tmp = *head;
    BTNode    *thead = *head;
    BTNode    *next = *head;
    BTNode    *prev = *head;

    if( tmp) {      // insert the node after the previous of head;
        prev = tmp->left;
        prev->right = node;
        node->right = tmp;

        node->left = prev;
        thead->left = node;
    } else {
        node->right = node->left = node;
        *head = node;
    }
    return node;
}

BTNode  *bt_leaves_to_dll(BTNode *root, BTNode** head)
{
   if (NULL == root) return root; 

   if (is_leaf(root)) { 
       bt_dll_insert(head, root); 
       return *head;
   }

   if (root->left) { 
       bt_leaves_to_dll(root->left, head);
   }
   if (root->right) {
       bt_leaves_to_dll(root->right, head);
   }
   return *head;
}
void test_bt_dll(BTNode *root)
{
    BTNode  *head = NULL;
    bt_leaves_to_dll(root, &head);
    bt_print_list(head);
}
BTNode*   bt_print_list(BTNode *head)
{
    BTNode  *node = head;
    BTNode  *next = head;
    if (NULL == head) return NULL;
    do {
        printf("%d,",next->value);
        node = next;
        next    = node->right;
    }while (NULL != next && next != head);
    printf("\n");
    return node;
}
void bt_traverse_level(BTNode   *root, int level, hash_t    *hash)
{
    if (NULL == root) return ;
    if (root->left) { 
        hash_insert(hash, level, root->left->value);
        bt_traverse_level(root->left, level+1, hash);
    }
    if (root->right) { 
        hash_insert(hash, level, root->right->value);
        bt_traverse_level(root->right, level+1, hash);
    }
}
void bt_extreme_level_nodes(BTNode  *root)
{
    hash_t  *hash = init_hash(32, func1);
    int level = 0; 
    hash_insert(hash, level, root->value);
    bt_traverse_level(root, ++level, hash);
    print_hash(hash);
}
void store_bt_inorder(BTNode    *tree, int* a, int *index)
{
    BTNode  *node = tree;
    int i = 0;
    if (node) {
        if ( node->left) {
            store_bt_inorder(node->left, a, index);
        } 
        a[*index] = node->value;
        (*index)++;
        if (node->right) {
            store_bt_inorder(node->right, a, index);
        }
    }
}
BTNode* merge_bts(BTNode    *tree1, BTNode  *tree2, int n1, int n2)
{
    int *a = (int*)malloc((n1+n2)* sizeof(int));
    int *a1 = (int*)malloc(n1* sizeof(int));
    int *a2 = (int*)malloc(n2* sizeof(int));
    int i = 0;
    BTNode  *node = NULL;
    store_bt_inorder(tree1, a1, &i);
    i = 0;
    store_bt_inorder(tree2, a2, &i);
    merge_merge_sort(a1, a2, n1, n2, a);
    printf("hi\n");
}
BTNode* test_merge_bts()
{
    BTNode  *n1 = NULL, *r; 
    BTNode  *n2 = NULL;
    int     a1[] = {1,2,3,4,5};
    int     a2[] = {7,8,9,10};
    n1 = create_binary_tree(n1, a1, sizeof(a1) / sizeof(int) );
    n2 = create_binary_tree(n2, a2, sizeof(a2) / sizeof(int) );
    r = merge_bts(n1, n2, sizeof(a1) / sizeof(int), 
            sizeof(a2) / sizeof(int));
    print_bt_inorder(r);
}
/*      Feb 2019    */
int bt_height(BTNode    *root)
{
    int lh = 0, rh = 0;
    if ( NULL == root) return 0;
    if (is_leaf(root)) return 1;
    if (root->left) {
        lh = 1+ bt_height(root->left);
    }
    if (root->right) {
        rh = 1 + bt_height(root->right);
    }
    return (lh > rh ? lh : rh);
}
/*  March 2019 */
BTNode* bt_max(BTNode*  root)
{
    if ( NULL == root || is_leaf(root)) return root;
    if (root->right) return bt_max(root->right);
    return root;
}

/*  Feb 2019    */
BTNode  *bt_rotate_right(BTNode *root)
{
    BTNode  *btn = NULL, *tmp = NULL;
    if (root && root->left) {
        btn = bt_max(root->left);
        if (btn == root->left ) {
            root->left = NULL;
            btn->right = root;
        } else {
            tmp = btn->left;
            btn->left = root->left;
            btn->right = root;
            root->left = tmp;
        }
    }
    return btn;
}

BTNode* bt_rotate_left(BTNode   *root)
{
    BTNode *btn = NULL, *tmp = NULL;
    if (root && root->right) {
        btn = bt_min(root->right);
        if ( btn == root->right) {
            root->right = NULL;
            btn->left = root;
        } else {
            tmp = btn->right;
            btn->right = root->right;
            btn->left = root;
            root->right = tmp;
        }
    }
    return btn;
}
/*      Feb 2019    */
BTNode* bt_balance_tree(BTNode *root)
{
    int left = 0, right = 0;
    int delta = 0;
    if (NULL == root || is_leaf(root)) return root;
    do {
        left    = bt_height(root->left); 
        right   = bt_height(root->right);
        delta = left - right;
        switch(delta) {
            case 2:
                return bt_rotate_right(root);
                break;
            case -2:
                return bt_rotate_left(root);
                break;
            default:
                // This will change the height of 
                // left & right, reevaluate
                if (root->left) {
                    root->left = bt_balance_tree(root->left);
                }
                if (root->right) {
                    root->right = bt_balance_tree(root->right);
                }
        }
    }while(root);
}
/*  Feb 2019    */
void test_normal_to_balance_tree()
{
    int ar[] = {7,8, 9};
    int ar2[15] = { 0 };
    int index = 0;
    BTNode  *root2 = NULL;
    BTNode  *root = 
        create_binary_tree(NULL, ar, sizeof(ar)/sizeof(int));
    printf("%s\n", __FUNCTION__);
    insert_bt_node(root, 6);
    insert_bt_node(root, 5);
    insert_bt_node(root, 4);
    insert_bt_node(root, 3);
    insert_bt_node(root, 2);
    insert_bt_node(root, 1);
    insert_bt_node(root, 10);
    insert_bt_node(root, 11);
    insert_bt_node(root, 12);
    insert_bt_node(root, 13);
    insert_bt_node(root, 14);
    insert_bt_node(root, 15);
    print_bt_preorder(root);
    store_bt_inorder(root, ar2, &index);
    root2 = create_binary_tree(root2, ar2, index);
    printf("\n");
    print_bt_preorder(root2);
    /*
    root = bt_balance_tree(root);
    print_bt_preorder(root);
    */
}
/*  March 2019 */
int bt_level_sum(BTNode *root)
{
    int esum = 0, osum = 0;
    int level = 1, count = 0;
    BTNode  *nn = NULL, *btn;
    queue<BTNode*> btq;
    if (NULL == root) return 0;

    btq.push(root);
    count++;
    btq.push(nn);
    while (count) {
        btn = btq.front();
        btq.pop();
        if (NULL == btn) { 
            level++;
            btq.push(nn);
        } 
        else {
            count--;
            if (btn->left) {
                btq.push(btn->left); 
                count++;
            }
            if (btn->right) {
                btq.push(btn->right); 
                count++;
            }
            if (level%2) osum += btn->value;
            else esum += btn->value;
        }
    }
    return osum-esum;
}
/*  March 2019  */
void bt_print_level(BTNode  *root)
{
    queue<BTNode*> btq;
    BTNode  *btn = NULL;
    if (NULL == root) return;
    btq.push(root);
    while(! btq.empty()) {
        btn = btq.front();
        btq.pop();
        printf("%d, ", btn->value);
        if (btn->left) {
            btq.push(btn->left);
        } 
        if (btn->right) {
            btq.push(btn->right);
        }
    }
}

void test_level_sum()
{
    //int ar[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int ar[] = {1,2,3, 4, 5,6,7};
    BTNode  *root = create_binary_tree(NULL, ar, sizeof(ar) / sizeof(int));
    bt_print_level(root);
    printf("odd even difference:%d\n", bt_level_sum(root));
}
void test_tree_from_preorder()
{
    int ar[] = {4, 2, 1, 3, 6, 5, 7};
    BTNode  *root = NULL;
    root = bt_create_bt_from_preorder(ar, sizeof(ar)/sizeof(int));
    print_bt_inorder(root);
}
BTNode* bt_create_bt_from_preorder(int* ar, int size)
{
    BTNode  *root = NULL;
    int     i = 1;
    int     lsize = 0, rsize = 0;
    if (ar == NULL || 0 == size) return NULL;
    root = allocBTNode();
    root->value = ar[0];
    while (i < size) {
        if (ar[i] > ar[0]) {
            break;
        } 
        i++;
    }
    root->left = bt_create_bt_from_preorder(ar+1,i-1 );
    root->right = bt_create_bt_from_preorder(ar+i,size-i );
    return root;
}
/*  Aug 2019    */
BTNode  *create_node(BTNode *root, int value, int left)
{
    BTNode  *tmp = NULL;
    tmp = allocBTNode();
    tmp->value = value;

    if (NULL == root) {
        ;
    } else if (left) {
        root->left = tmp;
    } else { 
        root->right = tmp;
    }
    return tmp;
}
BTNode* bt_find_node(BTNode *root, int data)
{
    BTNode *node = NULL;
    if (root == NULL) return root;
    if (data == root->value) return root;
    if ( is_leaf(root)) return NULL;

    node = bt_find_node(root->left, data);
    if (NULL == node) {
        node = bt_find_node(root->right, data);
    }
    return node;
}
/*  Function to create any type of binary tree
    input is an array of string of the following format 
    3l11r6
    3r6
    3l11
 */
BTNode* bt_create_bt(int argc, char* argv[])
{
    char    *tree = argv[0];
    char    *ltokens = "lL";
    char    *rtokens = "Rr";
    int     count = 0;
    char    *p = NULL, *l = NULL;
    BTNode  *node = NULL;
    BTNode  *root = NULL;
    int     val;
    while (count < argc) {
        tree = argv[count]; 
        p = strtok(tree, ltokens);
        if (p) {
            // This should be the root
            val = atoi(p);
            node = bt_find_node(root, val); 
            if (NULL == node) {
                root = create_node(NULL, val, 0);
                node = root;
            }
            p = strtok(NULL, rtokens);
            if (p) {
                create_node(node, atoi(p), 1);
                p = strtok(NULL, rtokens);
                if (p) create_node(node, atoi(p), 0);
            } else { 
                l = strrchr(tree, 'r');
                if (l) create_node(node, atoi(l+1), 0);
            }
        } else {
            p = strtok(tree, rtokens);
            if (p) {
                val = atoi(p);
                node = bt_find_node(root, val); 
                if (NULL == node) {
                    root = create_node(NULL, val, 0);
                    node = root;
                }
                p = strtok(NULL, rtokens);
                create_node(node, atoi(p), 0);
            } else {
                node = NULL;
                if (tree) node = bt_find_node(root, atoi(tree));
                if (NULL == node) {
                    root = create_node(root, atoi(tree), 0);    
                    node = root;
                }
            }
        }
        count++;
    }
    return  root;
}
/*  Create any random buinary tree
    Not necessaroly the binary search tree
    3 L 11 L 2
    3 L 11 R 7
    3 R 6 L 8
    3 R 6 R5 L 8 
 */
BTNode  *create_bt()
{
    BTNode  *root = NULL;
    BTNode  *left = NULL, *right = NULL;
    root = create_node(root, 3, 0);

    left = create_node(root, 11, 1);
    create_node(left, 2, 1);
    left = create_node(left, 7, 0);

    right = create_node(root, 6, 0);
    create_node(right , 8, 1);
    right = create_node(right, 5, 0);

    left = create_node(right, 2, 1);
    return root;
}

void bt_preorder(BTNode * root, vector<int> &v)
{
    if (NULL == root) return;
    v.push_back(root->value);
    bt_preorder(root->left, v);
    bt_preorder(root->right, v);
}
int same_tree(int argc, char* argv[])
{
    int count = atoi(argv[0]) , i;
    //char*   br1[] = { "3l11r6", "11l2r7", "6l8r5","5l13"};
    //char*   br2[] = { "3l11r6", "11l2r7", "6l8r5","5l12"};
    BTNode  *t1 = NULL;
    BTNode  *t2 = NULL;
    vector<int> v1;
    vector<int> v2;

    if (argc == 0) return 0;
    count = atoi(argv[0]);
    argv++;

    t1 = bt_create_bt(count, argv);
    t2 = bt_create_bt(count, argv+count);

    bt_preorder(t1, v1);
    bt_preorder(t2, v2);

    if (v1.size() == v2.size()) {
        i = v1.size()-1;
        for (; i >=0; i--) {
            if (v1[i] != v2[i]) return 0;
        }
        return 1;
    } else {
        return 0;
    }
}
int check_sum(vector<int> *path, int sum)
{
    int csum = 0;
    vector<int>::reverse_iterator it;
    it = path->rbegin();
    for ( ; it != path->rend (); it++) {
        csum += *it;
        if (csum == sum) { 
            cout << " found the sum\n";
        }
    }
}
int check_sum2(vector<int> &path, int sum)
{
    int csum = 0, j;
    int i = path.size()-1; 

    for ( ; i >= 0; i--) {
        csum += path[i];
        if (csum == sum) { 
            cout << "found the sum\n";
            for ( j = i; j < path.size(); j++) {
                cout << path[j] << ","; 
            }
            cout << "\n";
        }
    }
}

void print_vector(vector<int>& path)
{
    vector<int>::iterator it = path.begin();
    for (; it != path.end(); it++ ) {
        cout << *it << "," ;
    }
    cout << "\n";
}

void recursive_print_path(BTNode   *root, int sum, vector<int> path)
{
    if (NULL == root) return;
    path.push_back(root->value);

    check_sum2(path, sum);
    recursive_print_path(root->left, sum , path);
    recursive_print_path(root->right, sum , path);
}
void print_path_given_sum(BTNode *root, int sum)
{
    vector<int> path;
    if ( NULL == root) { 
        return ;
    }
    path.push_back(root->value);
    check_sum2(path, sum);
    recursive_print_path(root->left, sum , path);
    recursive_print_path(root->right, sum , path);
}


void print_all_paths(BTNode *root, vector<int> path)
{
    if (NULL == root) return;
    path.push_back(root->value);

    if (is_leaf(root)) {
        print_vector(path);
    }
    if (root->left) print_all_paths(root->left, path); 
    if (root->right ) print_all_paths(root->right, path); 
}
