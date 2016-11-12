#include <stdio.h>
 
#include <graph1.h>
 
int main(void)
{
    graph1 *graph;
    vertex *v;
    vertex *A, *B, *C, *D, *E;
    iterator *vertices, *edges;
    edge *e;
 
    /* Create a graph */
    graph = graph1_create();
 
    /* Add vertices */
    A = graph1_add(graph, "A", NULL);
    B = graph1_add(graph, "B", NULL);
    C = graph1_add(graph, "C", NULL);
    D = graph1_add(graph, "D", NULL);
    E = graph1_add(graph, "E", NULL);
 
    /* Add edges */
    graph1_add_edge(graph, A, B);
    graph1_add_edge(graph, A, D);
    graph1_add_edge(graph, B, C);
    graph1_add_edge(graph, C, B);
    graph1_add_edge(graph, D, A);
    graph1_add_edge(graph, D, C);
    graph1_add_edge(graph, D, E);
 
    /* Display */
    printf("Vertices (%d) and their neighbours:\n\n", graph1_get_vertex_count(graph));
    vertices = graph1_get_vertices(graph);
    while ((v = iterator_get(vertices))) {
        iterator *neighbours;
        vertex *neighbour;
        unsigned int n = 0;
        printf("%s (%d): ", vertex_get_name(v), graph1_get_neighbour_count(graph, v));
        neighbours = graph1_get_neighbours(graph, v);
        while ((neighbour = iterator_get(neighbours))) {
            printf("%s", vertex_get_name(neighbour));
            if (n < graph1_get_neighbour_count(graph, vertex) - 1) {
                fputs(", ", stdout);
            }
            n++;
        }
        putchar('\n');
        iterator_delete(neighbours);
    }
    putchar('\n');
    iterator_delete(vertices);
    printf("Edges (%d):\n\n", graph1_get_edge_count(graph));
    edges = graph1_get_edges(graph);
    while ((e = iterator_get(edges))) {
        printf("<%s, %s>\n", vertex_get_name(edge_get_from(e)), vertex_get_name(edge_get_to(e)));
    }
    putchar('\n');
    iterator_delete(edges);
 
    /* Delete */
    graph1_delete(graph);
 
    return 0;
}
