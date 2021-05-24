//
// Created by yura on 24.05.2021.
//

#include "dialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Dexter", "5. Decomposition", "6. Input from file","7. Show"};
const int N =sizeof(msgs) / sizeof(msgs[0]);

void dialog(Graph *graph)
{
    int rc = 0;
    while (1) {
        printf("\n-------------------\n");
        for (int i = 0; i < N; i++) {
            puts(msgs[i]);
        }
        puts("Make your choice: --> ");
        scan_int(&rc);
        switch (rc) {
            case 0:{
                return;
            }
            case 1:{
                D_Add(graph);
                break;
            }
            case 2:{
                D_Find(graph);
                break;
            }
            case 3:{
                D_Delete(graph);
                break;
            }
            case 4:{
                D_Dexter(graph);
                break;
            }
            case 5:{
                D_Decomposition(graph);
                break;
            }
            case 6:{
                D_File(graph);
                break;
            }
            default:{
                D_Show(graph);
                break;
            }
        }
    }
}


void D_Add(Graph *graph){
    int choose = 0;
    printf("What do you want to add?\n1)vertex 2)edge\nChoose-->");
    scan_int(&choose);
    if (choose == 1){
        add_vertex(graph);
    } else{
        add_edge(graph);
    }
}

void D_Show(Graph* graph){
    FILE *text = NULL;
    int choose;
    printf("Do you want to print graph in console (enter 1) or in file(print 2)?\nEnter-->");
    scan_int(&choose);
    if (choose == 1){
        printf("\n------------------Graph-----------------\n");
        show_graph(graph);
    } else{
        text = fopen("result.txt", "w");
        if (text == NULL){
            printf("We can`t open this file!\n");
        } else{
            printf("File was successfully created!\n");
        }
        fprintf(text ,"------------------Graph-----------------\n");
        file_show(text, graph);
        fclose(text);
    }
}

void D_Delete(Graph* graph){
    int choose;
    printf("What do you want to delete?\n1)vertex 2)edge\nChoose-->");
    scan_int(&choose);
    if (choose == 1){
        delete_vertex(graph);
    } else{
        delete_edge(graph);
    }
}

void D_Find(Graph* graph) {
    char* name = NULL, * find = NULL;
    Node* node = NULL;
    printf("Please, enter vertex, from which you want start BFS\nEnter-->");
    name = scan_string(name);
    printf("Please, enter vertex, which you want to find\nEnter-->");
    find = scan_string(find);
    node = DFS(graph, name, find);
    if (node == NULL) {
        printf("We can`t find this element!\n");
    }
    else {
        show_result(node);
    }
    free(name);
    free(find);
}

void D_Dexter(Graph* graph) {
    char* name_1 = NULL, * name_2 = NULL;
    int n;
    Mass* mass = NULL;
    printf("Please, enter start vertex\nEnter-->");
    name_1 = scan_string(name_1);
    if (name_1 == NULL) {
        printf("We can`t find this vertex!\n");
        return;
    }
    printf("Please, enter finish vertex\nEnter-->");
    name_2 = scan_string(name_2);
    if (name_2 == NULL) {
        printf("We can`t find this vertex!\n");
        return;
    }
    mass = new_mass(graph, mass, name_1);
    n = Dexter(graph, name_2, mass);
    if (n < 0 || n == 2147483647) {
        printf("Error!\n");
    }
    else {
        printf("%d\n", n);
    }
    delete_mass(mass);
    free(name_1);
    free(name_2);
}

void D_Decomposition(Graph* graph) {
    Mass* mass = NULL;
    mass = dec_new_mass(graph, mass);
    mass = decomposition(graph, mass);
    delete_mass(mass);
}

void D_File(Graph* graph){
    FILE *input = NULL;
    int choose;
    int i = 0;
    input = fopen("enter.txt", "rb");
    fseek(input, 0, SEEK_END);
    long offset = ftell(input);
    fseek(input, 0, SEEK_SET);
    for(i = 0; i < offset; i += 12){
        fscanf(input, "%d", &choose);
        if (choose == 1){
            file_add_vertex(input, graph);
        } else{
            file_add_edge(graph, input);
        }
    }
    fclose(input);
}


void scan_int(int* n) {
    int i = 0;
    do {
        i = scanf("%d", n);
        if (i != 1) {
            printf("You`re wrong! Please, try again!\n");
            scanf("%*c");
        }
    } while (i != 1);
}

char* scan_string(char* n) {
    int k = 0;
    n = (char*)malloc(100 * sizeof(char));
    do {
        k = scanf("%s", n);
        if (k != 1) {
            printf("Please, try again!\n");
        }
    } while (k != 1);
    unsigned int i = strlen(n);
    n = (char*)realloc(n, (i + 1) * sizeof(char));
    return n;
}

char *file_scan_string(FILE* input, char *n){
    n = (char*)malloc(100 * sizeof(char));
    fscanf(input, "%s", n);
    unsigned int i = strlen(n);
    n = (char*)realloc(n, (i + 1) * sizeof(char));
    return n;
}