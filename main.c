//
// Taken example from: 
//	http://www.geeksforgeeks.org/graph-and-its-representations/
//
// A C Program to demonstrate adjacency list representation of graphs
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head;  // pointer to head node of list
};
 
// A structure to represent a graph. A graph is an array of adjacency lists.
// Size of array will be V (number of vertices in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest)
{
    struct AdjListNode* newNode =
            (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
     // Initialize each adjacency list as empty by making head as NULL
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
 
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add an edge from src to dest.  A new node is added to the adjacency
    // list of src.  The node is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}
 
// A utility function to print the adjacenncy list representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}

char  *removeschar(char* source) {
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ';')
      i++;
  }
  *i = 0;

	return source;
}

char  *removespaces(char* source) {
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;

	return source;
}

// Reading file
int read_file(struct Graph* graph){

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

	const char s[2] = "->";
	char *word = "->";
	char *token;
	char *node;
	char *edge;

    fp = fopen("graph.dot", "r");
    if (fp == NULL)
		return -1;

    while ((read = getline(&line, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu :\n", read);
        //printf("%s", line);

		if(strstr(line,word) != NULL) {

			/* get the first token */
			token = strtok(line, s);

			int count = 0;

			/* walk through other tokens */
			while( token != NULL ) {
				token = removespaces(token);
				token = removeschar(token);

				if (count == 0 ){
					node = token;
					printf( "node  =  %s ", node);
				}
				
				if (count == 1){
					edge = token;
					printf( "edge  =  %s ", edge);
					count = 0;
				}
			
				count ++;
				token = strtok(NULL, s);
			}
		}

    }

    fclose(fp);
    if (line)
        free(line);
    
	return 0;
}
 
// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    int V = 5;
    struct Graph* graph = createGraph(V);

	read_file(graph); 
    
	// print the adjacency list representation of the above graph

    addEdge(graph, 0,1);
    addEdge(graph, 0,2);
    addEdge(graph, 0,3);
    addEdge(graph, 0,4);

    printGraph(graph);

    return 0;
}

