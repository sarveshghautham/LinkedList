//
//  list.h
//  LinkedList
//
//  Created by Sarvesh Ghautham on 2/22/14.
//

#ifndef LinkedList_list_h
#define LinkedList_list_h

#include "main.h"
#define MAX_LISTS 100
#define MAX_NODES_IN_LIST 100

typedef struct node
{
    struct node *next;
    int list_id;
    int data;
}node;

node * create(int, int);
void insert(node **, int, int);
void display (node *);
int remove_node (node **, int);
void remove_list (node *);
node * read_from_file_and_construct_list(FILE **, int, long *);
node * create_node_reconstruction(int);
void write_to_file (node *, FILE **);
void rewrite_to_file (node **, FILE **, int, int);
int check_line_number(int *, int , long);
void write_list_number_file(FILE **, int, long);
int load_in_memory (FILE **, node **);
void remove_from_listid_file(FILE **, int);
int check_node_present (node *, int);
long get_list_id(FILE **, int *, int *);

#endif
