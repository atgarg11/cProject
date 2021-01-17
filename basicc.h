#ifndef _BASIC_C_H_
#define BASIC_C_H_

void practise_basic(int tc, int argc, char* argv[]);

typedef struct null_t_ {
    int size; 
    int arr[0];
}null_t;

void test6_cycle();
void test5_delete_node();
void test7_find_odd_numbers();
void test8_copy_list_with_random();
void test9_even_odd(listNode    *head);
void test10_two_keys();
void test11_modulo();
void test21_dll_insert();
void test_number_of_occurences(int num, int low, int high);
void test_rotate_array();
#endif
