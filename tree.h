#ifndef TREE_H_
#define TREE_H_
#include <stdio.h>
#include <ds.h>
#include <vector>

using namespace std;

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
void test_normal_to_balance_tree();
void test_level_sum();
void print_bt_level_order(BTNode    *root, int level );
void test_tree_from_preorder();
BTNode* bt_create_bt_from_preorder(int* ar, int size);
void practise_trees(int tc, int argc, char* argv[]);
BTNode* create_bt();
void print_path_given_sum(BTNode *root, int sum);
void print_all_paths(BTNode *root, vector<int> path);
BTNode* bt_create_bt(int argc, char* argv[]);
int same_tree(int argc, char* argv[]);
void bt_preorder(BTNode * root, vector<int> &v);

#endif
