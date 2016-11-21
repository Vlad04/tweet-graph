#include <stdio.h>
#include "hash.h"
#include "graph.h"

int count=0;

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
    static struct nlist *item; /* pointer table */
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
    int node_key ,edge_key ,size= 0; 

	const char s[2] = "->";
	char *word = "->";
	char *token;
	char *node;
	char *edge;

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
                    //printf( "node  =  %s , key = %d \n",node,node_key);
				}
				
				if (count == 1){
					edge = token;
                    edge_key = map_name(edge);
                    //printf( "node  =  %s , key = %d \n",edge,edge_key);
					count = 0;
				}
        
				count ++;
				token = strtok(NULL, s);
			}

            //printf ("addEdge(graph,%d,%d);\n",node_key,edge_key);
            if (node_key > size ) {
                size = node_key;
            }

            if (edge_key > size ) {
                size = edge_key;
            }

		}

    }

    fclose(fp);
    if (line)
        free(line);
    
	return size;
}
 
int main()
{

	// get the number of nodes
	// this should generate a 2 dimentional array with the numbers of ndoe 
	// and edge 
	// in example 
	// [0][24]
	// [0][12]
	// [0][32]

	int size = read_file(); 

	// Create the graph with the proper size
    struct Graph* graph = createGraph(size);
	
	//addEdge(graph,[node],[edge]);
	addEdge(graph,0,1);
	addEdge(graph,1,2);
	addEdge(graph,2,3);

    printGraph(graph);

    return 0;
}

