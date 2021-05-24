//
// Created by yura on 24.05.2021.
//

#ifndef LAB6_LIST_H
#define LAB6_LIST_H

#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include "stdio.h"


typedef struct node_{
    int coordinates[2];
    char *name;
}Node;

typedef struct item_{
    Node *node;
    int weight;
    struct item_* next;
    struct item_* prev;
}Item;

typedef struct list_{
    Item *head;
    Item *tail;
}List;

typedef struct graph_{
    List **list;
    int count;
}Graph;

typedef struct check_{
    char *name;
    struct check_* next;
}Check;

typedef struct list_check_{
    Check *head;
    Check *tail;
}List_Check;

typedef struct mass_item_{
    char *name;
    int weight;
    int color;
}Mass_Item;

typedef struct mass_{
    Mass_Item *item;
    int count;
    int max;
}Mass;


Graph *new_matrix(Graph*);
//////////////// Insertion ///////////////
void add_edge(Graph *);
Item *new_node(int[], char *);
void input_graph(Graph*, Item*);
void add_vertex(Graph*);
void input_edge(Graph*, char *, char *, int);
void input_edge_in_list(List*, Item*);
Item *add_item(Node*, int );
List *check_name_coords(Graph*, char *, int []);
/////////////// Show /////////////////////
void show_graph(Graph*);
void show_list(List*);
void show_node(Item *);
/////////////// Delete /////////////////////
void delete_vertex(Graph*);
void delete_vertex_key(Graph*, char *);
void delete_in_list(List*, char *);
void delete_list(List*);
void delete_edge(Graph*);
void delete_edge_key(Graph*, char *, char *);
/////////////// BFS ////////////////////////
List *find_list(Graph*, char *);
Node *DFS(Graph*, char *, char *);
void show_result(Node*);
List_Check *add_list(List_Check *, char*);
List_Check *new_list(List_Check *);
int check_in_list(List_Check*, char *);
void delete_list_check(List_Check*);
Mass *new_mass_for_DFS(Mass*, int);
Mass *add_mass(Mass*, char *);
/////////////// Remove /////////////////////
void delete_graph(Graph*);
/////////////// Dexter /////////////////////
int Dexter(Graph*, char *, Mass*);
Mass *new_mass(Graph*, Mass*, char *);
int find_min(Mass*);
Mass *reset(Mass*, List*, int);
int find_in_mass(Mass*, char *);
void delete_mass(Mass*);
/////////////// Decomposition /////////////////////
Mass *dec_new_mass(Graph*, Mass*);
Mass *decomposition(Graph*, Mass*);
List_Check *dec_DFS(Graph*, char *, List_Check*);
Mass *transfer(Mass*, List_Check*, int);
void print_check_list(Graph *, List_Check*, int);
/////////////// File /////////////////////
void file_show(FILE*, Graph*);
void file_show_list(FILE*, List*);
void file_show_node(FILE*, Item*);
void file_add_edge(Graph*, FILE*);
char *file_scan_string(FILE*, char *);
void file_add_vertex(FILE *, Graph*);

#endif //GRAPH_LIST_H

#endif //LAB6_LIST_H
