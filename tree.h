#ifndef TREE_H_
#define TREE_H_
#include <stdio.h>
#include <ds.h>

BTNode* find_bt_node(BTNode *root, int value);
void test_vertical(BTNode   *root);
BTNode  *test12_removal(BTNode  *root, int val);
void test_vertical(BTNode   *root);
void test_left_leaf_sum(BTNode  *root);
void node_without_sibling(BTNode    *root);
BTNode*   bt_print_list(BTNode *head);
void test_bt_dll(BTNode *root);
void bt_extreme_level_nodes(BTNode  *root);
void store_bt_inorder(BTNode    *tree, int a[], int *index);
BTNode* merge_bts(BTNode    *tree1, BTNode  *tree2, int n1, int n2);
BTNode* test_merge_bts();
#endif
