//Dijkstra's Algorithm Implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "graph.h"
#include "heap.h"
#include "util.h"
using namespace std;

//global variables
int n, m, edgeID, directed, pCount, neverFound, p[999];
float weight, pathWeight;
const char* fileName = "";

//data structures initialized
struct Vertex *vArray;
struct Graph *myGraph;
HEAP *heap;
elementP newElement;

//function receives input from user via input, and returns a number for switch case
int assign(string command) {
    if (command == "find") {
        return 1;
    }
    if (command == "write path") {
        return 2;
    }
    if (command == "stop") {
        return 3;
    }
    else return 0;
}

//implementation of dijkstra's shortest path algorithm
struct Vertex* dijkstra(struct Graph *, int src, int dest, int flag) {

    //allocating memory for Vertex Array
    Vertex *vArray = new Vertex[n + 1];
    int curVertex;
    neverFound = 0; //this will change to 1 if search is unsuccessful

    for (int i = 1; i <= n; i++) {

        vArray[i].id = i;
        vArray[i].color = 0; //0 for white, 1 for grey, 2 for black
        vArray[i].d = 999999;
        vArray[i].pi = -1;
        vArray[i].pos = 0;
    }

    vArray[src].d = 0;
    vArray[src].color = 1; //change color to grey

    heap = Initialize(n);

    //create memory and insert the new value
    newElement = new ELEMENT;
    newElement->key = vArray[src].d;
    newElement->pos = vArray[src].pos;
    newElement->vertex = vArray[src].id;

    Insert(heap, newElement, vArray[src], vArray, flag); //line 4 in pseudo code
   // delete[] newElement;

    while(heap->size > 0) {

        curVertex = ExtractMin(heap, 1, vArray, flag);
        vArray[curVertex].color = 2; //line 6

        if (curVertex == dest) {
            deleteHeap();
            delete[] newElement;
            return vArray; //was 0
        }
       // delete[] newElement;
        AdjListNode *temp = myGraph->array[curVertex].head;

        while (temp != NULL) {

            if (vArray[temp->dest].color == 0){
                //line 9, temp->dest is just the current node on the adjacency list
                //being explored. it is the destination of the edge we are going along

                vArray[temp->dest].d = vArray[curVertex].d + temp->w; //line 10
                vArray[temp->dest].pi = vArray[curVertex].id;

                vArray[temp->dest].color = 1; //turns color grey, edn of line 10

                //create memory and insert the new value
                newElement = new ELEMENT;
                newElement->key = vArray[temp->dest].d;
                newElement->pos = vArray[temp->dest].pos;
                newElement->vertex = vArray[temp->dest].id;

                Vertex v = vArray[temp->dest];
                Insert(heap, newElement, v, vArray, flag); //line 11


            }
                //if new shortest path is found
            else if (vArray[temp->dest].d > (vArray[curVertex].d + temp->w)) {
                //change the parent and update the distance 
                float dumby = vArray[temp->dest].d;
                vArray[temp->dest].d = (vArray[curVertex].d + temp->w);
                vArray[temp->dest].pi = vArray[curVertex].id;

                if (flag == 1) {

                    printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", vArray[temp->dest].id, dumby,
                           vArray[temp->dest].d);
                }

               DecreaseKey(heap, vArray[temp->dest].pos, vArray[temp->dest].d, vArray, flag);
            }

            temp = temp->next;
        }
    }

    neverFound = 1; //exits function due to Queue being empty, i.e. search was unsuccessful
    deleteHeap();
    delete[] newElement;

    return vArray;
}


void makePath(int d, int s){

    //define the predescessor
    int pred;
    pred = vArray[d].pi;

    //if the destination is not equal to the source, recursive call to make path
    if(d != s) {
        pCount++;
        p[pCount] = d;
        makePath(pred, s);
    }

    else {
        //print the path
        for (int i = pCount; i > 0; i--) {

            if (i== 1) {
                printf("%d>", p[i]);
            }

            else {
                printf("%d, ", p[i]);
            }
        }
        //reset the count
        pCount = 0;
    }
}


int main(int argc, char* argv[]) {
    //read in arguments of main function call
    if (argc > 1) {
        fileName = argv[1];
    }
    string direction = argv[2];

    if (direction == "undirected") {
        directed = 0;

    } else {
        directed = 1; //1 for directed, 0 for undirected
    }

    int pathFound = 1;
    // FileIO using pointers
    FILE *infile;
    string command;
    infile = fopen(fileName, "r");
    int src = 0;
    int dest = 0;


    fscanf(infile, "%d", &n); //read in num of vertices
    fscanf(infile, "%d", &m); //read in num of edges

    // printf("vertex number = %d\n", n);
    // printf("edge number = %d\n", m);

    myGraph = createGraph(n, directed);
/*

    if (directed == 0)   //display the adjacency list for undirected graph
    {
        printf("Adjacency List for undirected graph: \n");
    }

    if (directed == 1)   //display the adjacency list for directed graph
    {
        printf("Adjacency List for directed graph: \n");
    }
*/
    for (int i = 1; i <= m; i++) {
        fscanf(infile, "%d", &edgeID);
        fscanf(infile, "%d", &src);
        fscanf(infile, "%d", &dest);
        fscanf(infile, "%f", &weight);

        //testing print statement for edge list
        // printf("\nEdge %d:  ", i);
        addEdge(myGraph, src, dest, weight, directed);

    }
fclose(infile);

    src = 1; //resetting source

    while (1) {

        int s, d, f, doThis;
        command = nextCommand(&s, &d, &f);
        doThis = assign(command);

        //switch statement assigns the user command to an action
        switch(doThis) {

            //FIND
            case 1:
                //free memory
                delete [] heap;
                deleteHeap();
                //reset the source
                src = s;
                //mark pathFound as 1 to note that a find has occurred
                pathFound = 1;
                printf("Query: find %d %d %d\n", s, d, f);

                if (s > n || s == d || f > 1 || f < 0) {
                    printf("Error: invalid find query\n");
                    pathFound = 0;
                    break;
                }
                //compute the shortest path with dijkstra's algo
                vArray = dijkstra(myGraph, s, d, f);
                break;

            //WRITE PATH
            case 2:

                printf("Query: write path %d %d\n", s, d);
                //set the path weight
                pathWeight = vArray[d].d;

                //check all conditions
                if(pathFound == 0) {
                    printf("Error: no path computation done\n");
                     break;
                }
                if(s != src || d > n) {
                    printf("Error: invalid source destination pair\n");
                    break;
                }
                //catch if no path exists
                if(pathWeight > 999999) {
                    printf("No %d-%d path exists.\n", s, d);
                    break;
                }

                //if destination is white 
                if(vArray[d].color == 0) {
                    //if search occurred but ended due to empty queue, no path exists
                    if((pathFound == 1) & (neverFound == 1)) {
                        printf("No %d-%d path exists.\n", s, d);
                        break;
                    }
                    //else no path has been computed
                    printf("No %d-%d path has been computed.\n", s, d);
                     break;
                }
                //if color is grey, we are not certain the path we found is the shortest
                if(vArray[d].color == 1) {
                    printf("Path not known to be shortest: <%d, ", s);
                    // break;
                }
                //if color is black, path has been computed
                if(vArray[d].color == 2) {

                    printf("Shortest path: <%d, ", s);
                    pathWeight = vArray[d].d;

                }
                //create the path
                makePath(d, s);
                cout << endl;
                printf("The path weight is: %12.4f\n", pathWeight);
                break;

            //STOP
            case 3:
                printf("Query: stop\n");
      

                exit(0);

            case 0:

            default:
                break;

        }

    }
              //freeing memory
                delete[] vArray;
                delete [] myGraph;
                deleteHeap();
                deleteGraph();
                delete [] heap;
    return 0;
}