//
// Created by yura on 24.05.2021.
//

#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include "dialog.h"
#include <string.h>

Graph* new_matrix(Graph* graph) {
    graph = (Graph*)malloc(sizeof(Graph));
    graph->list = NULL;
    graph->count = 0;
    return graph;
}

//////////////// Insertion ///////////////

void add_vertex(Graph* graph) {
    Item* node = NULL;
    List* list = NULL;
    int keys[2];
    char* name = NULL;
    printf("Please, enter name of this vertex\nName-->");
    name = scan_string(name);
    printf("Please, enter coordinates of vertex\nX-->");
    scan_int(&keys[0]);
    printf("Y-->");
    scan_int(&keys[1]);
    list = check_name_coords(graph, name, keys);
    if (list != NULL) {
        printf("You have already used this name or coordinates!\n");
        return;
    }
    node = new_node(keys, name);
    input_graph(graph, node);
}

Item* new_node(int keys[], char* name) {
    Node* node = NULL;
    Item* item = NULL;
    node = (Node*)malloc(sizeof(Node));
    item = (Item*)malloc(sizeof(Item));
    node->coordinates[0] = keys[0];
    node->coordinates[1] = keys[1];
    node->name = name;
    item->node = node;
    item->next = NULL;
    item->prev = NULL;
    item->weight = 0;
    return item;
}

void input_graph(Graph* graph, Item* node) {
    if (graph->count == 0) {
        graph->list = (List**)malloc(sizeof(List));
    }
    else {
        graph->list = (List**)realloc(graph->list, sizeof(List) * graph->count);
    }
    graph->list[graph->count] = (List*)malloc(sizeof(List));
    graph->list[graph->count]->head = node;
    graph->list[graph->count]->tail = node;
    graph->count++;
}


void add_edge(Graph* graph) {
    char* edge_1 = NULL, * edge_2 = NULL;
    int weight;
    printf("Please, enter first edge\nEnter-->");
    edge_1 = scan_string(edge_1);
    printf("Please, enter second edge\nEnter-->");
    edge_2 = scan_string(edge_2);
    printf("Please, enter weight of edge\nEnter-->");
    scan_int(&weight);
    input_edge(graph, edge_1, edge_2, weight);
    free(edge_1);
    free(edge_2);
}


void input_edge(Graph* graph, char* name_1, char* name_2, int weight) {
    List* vertex_1 = NULL, * vertex_2 = NULL;
    Node* node_1 = NULL, * node_2 = NULL;
    Item* item_1 = NULL, * item_2 = NULL;
    if (strcmp(name_1, name_2) == 0) {
        printf("Please, try again! You entered two similar vertexes!\n");
        return;
    }
    for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->list[i]->head->node->name, name_1) == 0) {
            vertex_1 = graph->list[i];
        }
        if (strcmp(graph->list[i]->head->node->name, name_2) == 0) {
            vertex_2 = graph->list[i];
        }
    }
    if (vertex_1 == NULL || vertex_2 == NULL) {
        printf("We can`t find one of this edges!\n");
        return;
    }
    node_1 = vertex_1->head->node;
    node_2 = vertex_2->head->node;
    item_1 = add_item(node_1, weight);
    item_2 = add_item(node_2, weight);
    input_edge_in_list(vertex_1, item_2);
    input_edge_in_list(vertex_2, item_1);
}

Item* add_item(Node* node, int weight) {
    Item* item = NULL;
    item = (Item*)malloc(sizeof(Item));
    item->node = node;
    item->next = NULL;
    item->prev = NULL;
    item->weight = weight;
    return item;
}

void input_edge_in_list(List* list, Item* node) {
    Item* ptr = list->tail;
    ptr->next = node;
    node->prev = ptr;
    list->tail = node;
    node->next = NULL;
}


/////////////// Show /////////////////////

void show_graph(Graph* graph) {
    for (int i = 0; i < graph->count; i++) {
        show_list(graph->list[i]);
        printf("\n");
    }
}

void show_list(List* list) {
    Item* ptr = list->head;
    printf("(%s [%d:%d]): ", ptr->node->name, ptr->node->coordinates[0], ptr->node->coordinates[1]);
    ptr = ptr->next;
    while (ptr != NULL) {
        show_node(ptr);
        ptr = ptr->next;
    }
}

void show_node(Item* node) {
    printf("[(%s [%d:%d]) (%d)] ", node->node->name, node->node->coordinates[0], node->node->coordinates[1], node->weight);
}



/////////////// Delete /////////////////////

void delete_vertex(Graph* graph) {
    char* name = NULL;
    printf("Please, enter name of this vertex\nEnter-->");
    name = scan_string(name);
    delete_vertex_key(graph, name);
    free(name);
}

void delete_vertex_key(Graph* graph, char* name) {
    List* list = NULL, * list_ptr = NULL;
    Item* ptr = NULL;
    int i = 0;
    for (i = 0; i < graph->count; i++) {
        if (strcmp(graph->list[i]->head->node->name, name) == 0) {
            list = graph->list[i];
            break;
        }
    }
    ptr = list->head->next;
    while (ptr != NULL) {
        list_ptr = find_list(graph, ptr->node->name);
        delete_in_list(list_ptr, name);
        ptr = ptr->next;
    }
    delete_list(list);
    graph->list[i] = graph->list[graph->count - 1];
    graph->count--;
}

void delete_in_list(List* list, char* name) {
    Item* ptr = NULL;
    ptr = list->head->next;
    while (ptr != NULL) {
        if (strcmp(ptr->node->name, name) == 0) {
            ptr->prev->next = ptr->next;
            if (ptr == list->tail) {
                list->tail = ptr->prev;
            }
            else {
                ptr->next->prev = ptr->prev;
            }
            free(ptr);
            return;
        }
        ptr = ptr->next;
    }
}

void delete_list(List* list) {
    Item* ptr = list->head, * ptr_prev = NULL;
    free(ptr->node->name);
    free(ptr->node);
    while (ptr != NULL) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev);
    }
    free(list);
}


void delete_edge(Graph* graph) {
    char* name_1 = NULL, * name_2 = NULL;
    printf("Please, enter first name of vertex\nEnter-->");
    name_1 = scan_string(name_1);
    printf("Please, enter second name of vertex\nEnter-->");
    name_2 = scan_string(name_2);
    delete_edge_key(graph, name_1, name_2);
    free(name_1);
    free(name_2);
}


void delete_edge_key(Graph* graph, char* name_1, char* name_2) {
    List* list_1 = NULL, * list_2 = NULL;
    list_1 = find_list(graph, name_1);
    list_2 = find_list(graph, name_2);
    if (list_2 == NULL || list_1 == NULL) {
        printf("We can`t find this elements!\n");
        return;
    }
    delete_in_list(list_1, name_2);
    delete_in_list(list_2, name_1);
}

/////////////// BFS ////////////////////////

List* find_list(Graph* graph, char* name) {
    for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->list[i]->head->node->name, name) == 0) {
            return graph->list[i];
        }
    }
    return NULL;
}


List* check_name_coords(Graph* graph, char* name, int keys[]) {
    for (int i = 0; i < graph->count; i++) {
        if (strcmp(graph->list[i]->head->node->name, name) == 0 || (graph->list[i]->head->node->coordinates[0] == keys[0] &&
                                                                    graph->list[i]->head->node->coordinates[1] == keys[1])) {
            return graph->list[i];
        }
    }
    return NULL;
}

Node* DFS(Graph* graph, char* name, char* find) {
    List *list = NULL;
    Item *ptr = NULL;
    Mass *mass = NULL;
    int k;
    mass = new_mass_for_DFS(mass, graph->count);
    mass = add_mass(mass, name);
    for (int i = 0; i < mass->max; i++){
        if (mass->item[i].name == NULL){
            delete_mass(mass);
            return NULL;
        }
        if (mass->item[i].color == 0){
            list = find_list(graph, mass->item[i].name);
            mass->item[i].color = 1;
            ptr = list->head->next;
            while (ptr != NULL){
                k = find_in_mass(mass, ptr->node->name);
                if (k == -1){
                    if (strcmp(find, ptr->node->name) == 0){
                        delete_mass(mass);
                        return ptr->node;
                    }
                    mass = add_mass(mass, ptr->node->name);
                }
                ptr = ptr->next;
            }
        }
    }
    delete_mass(mass);
    return NULL;
}

Mass *add_mass(Mass* mass, char *name){
    mass->item[mass->count].name = (char *) calloc(strlen(name)+1, sizeof (char ));
    strcpy(mass->item[mass->count].name, name);
    mass->count++;
    return mass;
}

Mass *new_mass_for_DFS(Mass* mass, int n){
    mass = (Mass*)malloc(sizeof(Mass));
    mass->count = 0;
    mass->max = n;
    mass->item = (Mass_Item*)calloc(n, sizeof(Mass_Item));
    for (int i = 0; i < n; i++) {
        mass->item[i].name = NULL;
        mass->item[i].color = 0;
    }
    return mass;
}

void show_result(Node* node) {
    printf("(%s [%d:%d])", node->name, node->coordinates[0], node->coordinates[1]);
}

List_Check* new_list(List_Check* list) {
    list = (List_Check*)malloc(sizeof(List_Check));
    list->head = NULL;
    list->tail = NULL;
    return list;
}

List_Check* add_list(List_Check* list, char* name) {
    Check* check = NULL;
    check = (Check*)malloc(sizeof(Check));
    check->name = (char*)calloc(strlen(name) + 1, sizeof(char));
    strcpy(check->name, name);
    check->next = NULL;
    if (list->head == NULL) {
        list->head = check;
        list->tail = check;
    }
    else {
        list->tail->next = check;
        list->tail = check;
    }
    return list;
}

int check_in_list(List_Check* list, char* name) {
    Check* ptr = NULL;
    ptr = list->head;
    while (ptr != NULL) {
        if (strcmp(name, ptr->name) == 0) {
            return 1;
        }
        ptr = ptr->next;
    }
    return 0;
}

void delete_list_check(List_Check* list) {
    Check* ptr = NULL, * ptr_prev = NULL;
    ptr = list->head;
    while (ptr != NULL) {
        ptr_prev = ptr;
        ptr = ptr->next;
        free(ptr_prev->name);
        free(ptr_prev);
    }
    free(list);
}

/////////////// Remove /////////////////////

void delete_graph(Graph* graph) {
    for (int i = 0; i < graph->count; i++) {
        delete_list(graph->list[i]);
    }
    free(graph->list);
    free(graph);
}

/////////////// Dexter /////////////////////

int Dexter(Graph* graph, char* name, Mass* mass) {
    char* now = NULL;
    List* list_1 = NULL;
    int k, number;
    while (1) {
        number = find_min(mass);
        now = mass->item[number].name;
        list_1 = find_list(graph, now);
        mass = reset(mass, list_1, number);
        if (mass == NULL) {
            return -1;
        }
        k = find_in_mass(mass, now);
        if (strcmp(name, now) == 0) {
            return mass->item[k].weight;
        }
        else {
            mass->item[k].color = 1;
        }
    }
}

Mass* new_mass(Graph* graph, Mass* mass, char* name) {
    const int max = 2147483647;
    mass = (Mass*)malloc(sizeof(Mass));
    mass->count = graph->count;
    mass->item = (Mass_Item*)calloc(graph->count, sizeof(Mass_Item));
    for (int i = 0; i < graph->count; i++) {
        mass->item[i].name = (char*)calloc(strlen(graph->list[i]->head->node->name) + 1, sizeof(char));
        strcpy(mass->item[i].name, graph->list[i]->head->node->name);
        if (strcmp(mass->item[i].name, name) == 0) {
            mass->item[i].weight = 0;
        }
        else {
            mass->item[i].weight = max;
        }
        mass->item[i].color = 0;
    }
    return mass;
}

int find_min(Mass* mass) {
    int i, min, k;
    for (i = 0; i < mass->count; i++) {
        if (mass->item[i].color == 0) {
            min = mass->item[i].weight;
            k = i;
            break;
        }
    }
    for (i; i < mass->count; i++) {
        if (mass->item[i].weight < min && mass->item[i].color == 0) {
            min = mass->item[i].weight;
            k = i;
        }
    }
    return k;
}

Mass* reset(Mass* mass, List* list, int number) {
    Item* ptr = list->head->next;
    int head = mass->item[number].weight;
    int i;
    while (ptr != NULL) {
        i = find_in_mass(mass, ptr->node->name);
        if (i == -1) {
            return NULL;
        }
        if (ptr->weight < mass->item[i].weight && mass->item[i].color != 1) {
            mass->item[i].weight = ptr->weight + head;
        }
        ptr = ptr->next;
    }
    return mass;
}

int find_in_mass(Mass* mass, char* name) {
    for (int i = 0; i < mass->count; i++) {
        if (strcmp(mass->item[i].name, name) == 0) {
            return  i;
        }
    }
    return -1;
}

void delete_mass(Mass* mass) {
    for (int i = 0; i < mass->count; i++) {
        free(mass->item[i].name);
    }
    free(mass->item);
    free(mass);
}

/////////////// Decomposition /////////////////////

Mass* dec_new_mass(Graph* graph, Mass* mass) {
    mass = (Mass*)malloc(sizeof(Mass));
    mass->count = graph->count;
    mass->item = (Mass_Item*)calloc(graph->count, sizeof(Mass_Item));
    for (int i = 0; i < graph->count; i++) {
        mass->item[i].name = (char*)calloc(strlen(graph->list[i]->head->node->name) + 1, sizeof(char));
        strcpy(mass->item[i].name, graph->list[i]->head->node->name);
        mass->item[i].color = 0;
        mass->item[i].weight = 0;
    }
    return mass;
}

List_Check* dec_DFS(Graph* graph, char* name, List_Check* list_check) {
    Item* ptr = NULL;
    List* list = NULL;
    list = find_list(graph, name);
    ptr = list->head;
    list_check = add_list(list_check, ptr->node->name);
    while (ptr != NULL) {
        if (check_in_list(list_check, ptr->node->name) == 0) {
            list_check = dec_DFS(graph, ptr->node->name, list_check);
        }
        ptr = ptr->next;
    }
    return list_check;
}

Mass* decomposition(Graph* graph, Mass* mass) {
    int color = 1;
    List_Check* list = NULL;
    for (int i = 0; i < graph->count; i++) {
        if (mass->item[i].color == 0) {
            list = new_list(list);
            list = dec_DFS(graph, mass->item[i].name, list);
            mass = transfer(mass, list, color);
            print_check_list(graph, list, color);
            delete_list_check(list);
            color++;
        }
    }
    return mass;
}

Mass* transfer(Mass* mass, List_Check* list, int color) {
    Check* ptr = NULL;
    ptr = list->head;
    int k;
    while (ptr != NULL) {
        k = find_in_mass(mass, ptr->name);
        mass->item[k].color = color;
        ptr = ptr->next;
    }
    return mass;
}

void print_check_list(Graph* graph, List_Check* list, int color) {
    printf("\n------------------Connectivity number %d-----------------\n", color);
    Check* ptr = list->head;
    List* find = NULL;
    while (ptr != NULL) {
        find = find_list(graph, ptr->name);
        show_list(find);
        printf("\n");
        ptr = ptr->next;
    }
}

/////////////// File /////////////////////

void file_show(FILE* text, Graph* graph){
    for (int i = 0; i < graph->count; i++) {
        file_show_list(text ,graph->list[i]);
        fprintf(text, "\n");
    }
}

void file_show_list(FILE* text, List* list){
    Item* ptr = list->head;
    fprintf(text ,"(%s [%d:%d]): ", ptr->node->name, ptr->node->coordinates[0], ptr->node->coordinates[1]);
    ptr = ptr->next;
    while (ptr != NULL) {
        file_show_node(text ,ptr);
        ptr = ptr->next;
    }
}


void file_show_node(FILE *text,Item* node) {
    fprintf(text ,"[(%s [%d:%d]) (%d)] ", node->node->name, node->node->coordinates[0], node->node->coordinates[1], node->weight);
}

void file_add_edge(Graph* graph, FILE *input) {
    char* edge_1 = NULL, * edge_2 = NULL;
    int weight;
    edge_1 = file_scan_string(input ,edge_1);
    edge_2 = file_scan_string(input, edge_2);
    fscanf(input, "%d", &weight);
    input_edge(graph, edge_1, edge_2, weight);
    free(edge_1);
    free(edge_2);
}

void file_add_vertex(FILE* input, Graph* graph){
    Item* node = NULL;
    List* list = NULL;
    int keys[2];
    char* name = NULL;
    name = file_scan_string(input, name);
    fscanf(input, "%d", &keys[0]);
    fscanf(input, "%d", &keys[1]);
    list = check_name_coords(graph, name, keys);
    if (list != NULL) {
        return;
    }
    node = new_node(keys, name);
    input_graph(graph, node);
}
