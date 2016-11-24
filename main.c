#include <stdio.h>
#include "hash.h"
#include "graph.h"
#include "array.h"
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

int count=0;
FILE *fp;
int verbose_flag = 0;
Array nodes;
Array edges;

char  *clean(char* source,char key) {
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != key)
      i++;
  }
  *i = 0;

	return source;
}

char* itoa(int val, int base){
    static char buf[32] = {0};
    int i = 30;
    for(; val && i ; --i, val /= base)
        buf[i] = "0123456789abcdef"[val % base];
        return &buf[i+1];                
}

int map_name(char *node){
    int key = 0;
    static struct nlist *item; /* hash table */
    struct nlist *np;

	item = lookup(node);

   	if(item != NULL) {
		//printf("Element found: %s\n", item->defn);
        key = atoi(item->defn);
   	} else {
		//printf("Element not found\n");
		//printf("Value %d\n", count) ;
        install(node,itoa(count,10));
        key = count;
        count++;
	}

    return key;
}

// Reading file
int read_file(){

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int node_key ,edge_key = 0; 

	const char s[2] = "->";
	char *word = "->";
	char *token, *node, *edge;

    fp = fopen("graph.dot", "r");
    if (fp == NULL)
		return -1;

    while ((read = getline(&line, &len, fp)) != -1) {

		if(strstr(line,word) != NULL) {

			/* get the first token */
			token = strtok(line, s);

			int count = 0;

			/* walk through other tokens */
			while( token != NULL ) {
				token = clean(token,' ');
				token = clean(token,';');
				token = clean(token,'\n');

				if (count == 0 ){
					node = token;
                    node_key = map_name(node);
					if (verbose_flag){
                    	printf( "node  =  %s , key = %d \n",node,node_key);
					}
					insertarray(&nodes,node_key);
				}
				
				if (count == 1){
					edge = token;
                    edge_key = map_name(edge);
					if (verbose_flag){
                    	printf("node  =  %s , key = %d \n",edge,edge_key);
					}
					insertarray(&edges,edge_key);
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


void print_help(){
	printf("Help : \n");
	printf("	-p : Print Graph network\n");
	printf("	-s : Sort users with more` connections\n");
	printf("	-v : Vervose in ourput.log\n");
	printf(" \n");
} 


void buble_sort( Array* array, Array* tmp){

	int swap, swap_tmp;
	int size = array->used;

	if (verbose_flag){
		
		printf ("\n buble_sort \n");
		printarray(*array);
		printarray(*tmp);
	}

	for (int c = 0 ; c < ( size - 1 ); c++) {
	    for (int d = 0 ; d < size - c - 1; d++) {
			/* For decreasing order use < */
			if (array->array[d] < array->array[d+1]) 
			{
				swap       = array->array[d];
				array->array[d]   = array->array[d+1];
				array->array[d+1] = swap;

				// We have to do this in order to save the position //
				swap_tmp       = tmp->array[d];
				tmp->array[d]   = tmp->array[d+1];
				tmp->array[d+1] = swap_tmp;
			}
		}
	}
	
	if (verbose_flag){
		printarray(*array);
		printarray(*tmp);
	}

}

void sort_graph( struct Graph* graph ){

    int count =0;
	int size = graph->V;
    Array nodes_tmp;

    initarray(&nodes_tmp,1);

    for (int v = 0; v < size; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        while (pCrawl)
        {

		    if (verbose_flag){
                printf("-> %d", pCrawl->dest);
            }
            pCrawl = pCrawl->next;
            count++;
        }

		    if (verbose_flag){
                printf(">> %d", count);
                printf("\n");
            }
        insertarray(&nodes_tmp,count);

        count = 0;
    }

	Array nodes_pos;
	initarray(&nodes_pos,1);

	for ( int j = 0; j < size; j++){
		insertarray(&nodes_pos,j);
	}
	
	buble_sort(&nodes_tmp,&nodes_pos);

	if( verbose_flag ){
		printf ("\n sort_graph \n");
		printarray(nodes_tmp);
		printarray(nodes_pos);
    }

	
	printf ("\n Most Valuable Users \n");

	printf ("Do NOT lose these contacts in your network\n");

	for ( int j = 0; j < size ; j ++ ){
		printf (" User : %d has %d contacts \n",
			 nodes_pos.array[j], nodes_tmp.array[j]);
	} 

	freearray(&nodes_tmp);
	freearray(&nodes_pos);

}


int main (int argc, char **argv) {

	int sort_flag = 0;
	int print_flag = 0;
	int c;

    int size = 0;
    struct Graph* graph;

	if (argc == 1 ){
		print_help();
	}

	while ((c = getopt (argc, argv, "svph")) != -1)
		switch (c) {
			case 'v':
				verbose_flag = 1;
				fp = fopen("output.log", "w");
				break;
			case 'p':
				print_flag = 1;
				break;
			case 's':
				sort_flag = 1;
				break;
			case 'h':
				print_help();
				break;
			default:
				print_help();
        		abort ();
		}

	initarray(&nodes,1);
	initarray(&edges,1);

	read_file(); 

	if (nodes.used == edges.used){
        size = edges.used;
        graph = createGraph(size);
    }	
	
    for (int i = 0; i < size; i++){
		if (verbose_flag){
			fprintf(fp,"addEdge(graph,%d,%d)\n",nodes.array[i],edges.array[i]);
		}
        addEdge(graph,nodes.array[i],edges.array[i]);
    }
 
	if (print_flag){
		printGraph(graph);
	}

	if (sort_flag){
        sort_graph(graph);
	}

	freearray(&nodes);
	freearray(&edges);
	
	if (verbose_flag){
		fclose(fp);
	}
    return 0;
}

