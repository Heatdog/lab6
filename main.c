#include <stdio.h>
#include "list.h"
#include "dialog.h"


int main() {
    Graph *graph = NULL;
    graph = new_matrix(graph);
    dialog(graph);
    delete_graph(graph);
    return 0;
}
