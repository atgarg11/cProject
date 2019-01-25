#include <stdio.h>
#include <stdlib.h>
#include "ds.h" 
#include "adt.h" 
#include "tree.h" 

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
    print_bt_inorder(root->left);
    printf("%d,",root->value);
    print_bt_inorder(root->right);
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

test3_bst(BTNode *root)
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
void practise_trees(int tc)
{
    BTNode  *root = NULL;
	int ar[] = {1,2,3, 4, 5, 6, 7};
    root = create_binary_tree(NULL, ar, sizeof(ar)/sizeof(int));
    int c  = 0;

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
    int *a = malloc((n1+n2)* sizeof(int));
    int *a1 = malloc(n1* sizeof(int));
    int *a2 = malloc(n2* sizeof(int));
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

