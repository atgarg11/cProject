#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ds.h"

#define MAX_IP_BITS 32

/*  
 *  Trie functions  
 */

tNode*  alloc_trie_node(unsigned int ip, unsigned int bit_pos)
{
    tNode   *tmp = (tNode*)malloc(sizeof(tNode));
    tmp->left = tmp->right = NULL;
    tmp->ip = ip;
    tmp->bit_pos = bit_pos;
    tmp->is_match = 0;
}
tNode*  find_in_trie(tNode    *root, unsigned int in_ip)
{
    int bit_pos = 0;
    tNode   *tmp = root, *rnode = NULL;

    if(NULL == root) return NULL;
    tmp = root; 

    for ( bit_pos = MAX_IP_BITS -1 ; bit_pos >= 0, tmp ; bit_pos--) {

        if (in_ip & (1 << bit_pos)) {
            tmp = tmp->right;
        }
        else { 
            tmp = tmp->left;
        }
        if (tmp && tmp->is_match)  rnode = tmp;
    }
    return rnode; // largest prefix match
}
tNode*  insert_trie_node(tNode  *root, unsigned int ip, int bits)
{
    tNode   *tmp = NULL;
    int     bit_pos = MAX_IP_BITS-1;
    int     max_bits = MAX_IP_BITS;

    if( NULL == root ) return root;

    tmp = root;
    for ( bit_pos = MAX_IP_BITS-1; bit_pos >= (max_bits-bits);bit_pos--) {

        if (ip & (1 << bit_pos)) {
            if (tmp->right) {
                tmp = tmp->right;
            }
            else {
                tmp->right = alloc_trie_node( ip, bit_pos);
                tmp = tmp->right;
            }
        }
        else { 
            if ( tmp->left) {
                tmp = tmp->left;
            }
            else {
                tmp->left= alloc_trie_node(ip, bit_pos);
                tmp = tmp->left;
            }
        }
    }
    tmp->is_match = 1;
    return tmp;
}

/*  Helper function to create a trie*/

tNode   *create_trie(tNode  *root)
{
    insert_trie_node(root, ntohl(get_ip("192.168.1.2")), 32);
    insert_trie_node(root, ntohl(get_ip("192.168.1.5")), 32);
    insert_trie_node(root, ntohl(get_ip("192.168.1.3")), 32);
    insert_trie_node(root, ntohl(get_ip("192.168.1.4")), 32);
    insert_trie_node(root, ntohl(get_ip("192.168.1.6")), 32);
    insert_trie_node(root, ntohl(get_ip("192.168.1.6")), 16);
}
