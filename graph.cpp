//Dijkstra's Algorithm Implementation

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int V;
struct Graph *graph;
struct AdjListNode *newNode;

void deleteGraph() {

    //delete [] graph->array;
    delete [] graph;
    delete [] newNode;

}

//function to create a graph
struct Graph *createGraph(int V, int directed) {

    //build the graph
    struct Graph *graph = new Graph;
    graph->V = V;

    //allocate memory for new adjacency list
    graph->array = new AdjList[V + 1];

    for (int i = 1; i < V; ++i) {
        graph->array[i].head = NULL;
    }

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest, float weight, int directed) {


    //add edge from src to dest
   newNode = new AdjListNode;
    newNode->src = src;
    newNode->dest = dest;
    newNode->w = weight;
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    //delete[] newNode;



  //prints out edges as they are read in
/*
    printf("%d", graph->array[src].head->src);
    printf(" ----> ");
    printf("%d   ", newNode->dest);
    printf("weight: %f\n", newNode->w);
*/

    if (directed == 0)   //if graph is undirected, then add another edge from dest to src
    {
        newNode = new AdjListNode;
        newNode->src = dest;
        newNode->dest = src;
        newNode->w = weight;
        newNode->next = graph->array[dest].head;
        graph->array[dest].head = newNode;
       // delete[] newNode;


/*      prints out the edges as they are read in
        printf("%d", newNode->src);
        printf(" ----> ");
        printf("%d   ", newNode->dest);
        printf("weight: %f\n", newNode->w);

        */

    }
    //delete[] newNode;
}


