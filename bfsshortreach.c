/**
 *  This code solves following HackerRank challenge:
 *      https://www.hackerrank.com/challenges/bfsshortreach
 *
 *  @author Ulises Tirado Zatarain <ulises.tirado@cimat.mx>
 */
#include <stdio.h>
#include <stdlib.h>

#define allocate_memory(T,S) (T*)malloc((S) * (sizeof(T)))
#define allocate_memory_with_zero(T,S) (T*)calloc(S,sizeof(T))

/**
 *  Defining some macros to autodocument the code.
 */
#define ERROR -1
#define SUCCESS 0
#define UNVISITED -1
#define STARTING_POINT 0
#define VISITED 6
#define ARE_NEIGHBOURS 1

/**
 * Struct to representing a queue of integers.
 */
struct queue{
    int size;
    int *data;
    int tail;
    int head;
};

/**
 *  Initializes a queue of integers, allocating enough memory for the size
 *  indicated by second argument.
 */
int queue_initialize(struct queue*,int);

/**
 *  Inserts an element into the queue.
 */
void queue_push(struct queue*,int);

/**
 *  Extracts an element from the queue.
 */
int queue_pop(struct queue*,int*);

/**
 *  Checks if the queue is empty.
 */
int queue_is_empty(struct queue*);

/**
 *  Destroys the queue.
 */
void queue_destroy(struct queue*);

/**
 * Struct to representing a graph by adjacency matrix.
 */
struct graph{
    int nodes;
    int **edges;
};

/**
 *  Read a graph representation from standard input.
 */
int graph_read_and_build(struct graph*);

/**
 *  Performs traversing (breadth first search) in the graph.
 */
int graph_bfs(struct graph*,int,int*);

/**
 *  Destroys the graph.
 */
void graph_destroy(struct graph*);

int main(int nargs,char* vargs[]){
    int q, s;
    // Read number of queries.
    scanf("%d\n",&q);
    int query, node;
    struct graph testcase;
    // Array to store the output.
    int *output;
    for(query = 1; query <= q; query++){
        if(graph_read_and_build(&testcase) == ERROR){
            return ERROR;
        }
        // Reading the starting vertex.
        scanf("%d",&s);
        // Remembering that we using 0-index.
        s--;
        // Allocating enough memory for the output.
        output = allocate_memory(int,testcase.nodes);
        if(output == NULL){
            return ERROR;
        }

        // Traversing the graph to get the output.
        if(graph_bfs(&testcase,s,output) == SUCCESS){
            // Displaying the output.
            for(node = 0; node < testcase.nodes; node++){
                if(node != s){
                    printf("%d ",output[node]);
                }
            }
            printf("\n");
        }else{
            free(output);
            return ERROR;
        }
        free(output);
        graph_destroy(&testcase);
    }
    return SUCCESS;
}

int queue_initialize(struct queue* container,int size){
    // Allocating memory for the queue as indicated in second argument.
    container->data = allocate_memory(int,size);
    if(container->data == NULL){
        return ERROR;
    }
    container->size = size;
    // Initializing the counters.
    container->tail = 0;
    container->head = 0;
    return SUCCESS;
}

void queue_push(struct queue* container,int value){
    // TODO: In strict sense, we need to check when the queue is full.
    container->data[container->tail++] = value;
}

int queue_pop(struct queue* container,int* value){
    if(queue_is_empty(container)){
        return ERROR;
    }
    *value = container->data[container->head++];

    // Reseting the counters when queue is empty.
    if(queue_is_empty(container)){
        container->tail = 0;
        container->head = 0;
    }
    return SUCCESS;
}

int queue_is_empty(struct queue* container){
    // The queue is empty when both counters are equals.
    return container->tail == container->head;
}

void queue_destroy(struct queue* container){
    // Realeasing dynamic memory of the queue.
    free(container->data);
}

int graph_read_and_build(struct graph* map){
    int m,i,u,v;
    // Reading the size of the graph: number of nodes and edges.
    scanf("%d %d\n",&(map->nodes),&m);
    int *edges = allocate_memory_with_zero(int,map->nodes*map->nodes);
    map->edges = allocate_memory(int*,map->nodes);
    if((edges == NULL) || (map->edges == NULL)){
        return ERROR;
    }
    // Making the adjacency matrix.
    for(i = 0; i < map->nodes; i++){
        map->edges[i] = &edges[i*map->nodes];
    }
    for(i = 1; i <= m; i++){
        // Reading each edge.
        scanf("%d %d\n",&u,&v);
        // Remembering that we using 0-index.
        u--; v--;
        // Making that u and v become neighbours.
        map->edges[u][v] = map->edges[v][u] = ARE_NEIGHBOURS;
    }
    return SUCCESS;
}

int graph_bfs(struct graph* map,int start,int* result){
    int current,node;
    struct queue aux;
    if(queue_initialize(&aux,map->nodes) == ERROR){
        return ERROR;
    }
    // Initializing all nodes as UNVISITED.
    for(node = 0; node < map->nodes; node++){
        result[node] = UNVISITED;
    }
    // Pushing starting point to the queue and marking as not UNVISITED.
    result[start] = STARTING_POINT;
    queue_push(&aux,start);
    while(!queue_is_empty(&aux)){
        // Popping the one node from the queue.
        queue_pop(&aux,&current);
        for(node = 0; node < map->nodes; node++){
            // Pushing UNVISITED neighbours of the current node in the queue.
            if((map->edges[current][node] == ARE_NEIGHBOURS) && (result[node] == UNVISITED)){
                // Computing the distance and marking as VISITED.
                result[node] = result[current] + VISITED;
                queue_push(&aux,node);
            }
        }
    }
    queue_destroy(&aux);
    return SUCCESS;
}

void graph_destroy(struct graph* map){
    // Realeasing dynamic memory of the graph.
    free(map->edges[0]);
    free(map->edges);
}
