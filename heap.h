//Dijkstra's Algorithm Implementation

#ifndef PROJECT3_HEAP_H
#define PROJECT3_HEAP_H

class heap {

};

struct Vertex {
    int id; //name of vertex
    int color; //color of vertex (white, gray, black)
    int pi; //current predecessor
    float d; //distance from source i.e. weight of current s-v path
    int pos; //index in the heap array
};


//ELEMENT DATA STRUCTURE
typedef struct TAG_ELEMENT {
    int vertex;
    int pos;
    float key;
} ELEMENT; //instantiate ELEMENT of type tag-element struct ; vertex ?
typedef ELEMENT *elementP;  //instantiate pointer to element structure


//HEAP DATA STRUCTURE
typedef struct TAG_HEAP {    //define heap data structure
    int capacity;   //max size of heap
    int size;   //current size of heap
    elementP *elements; //pointer to pointers to elements
} HEAP; //instantiate HEAP of type tag-heap struct


//function for building new HEAP with parameter capacity
HEAP *Initialize(int value);

//function for printing out elements in HEAP using pointers
void printHeap(HEAP *heap);

//***FUNCTION TO INSERT ELEMENT INTO HEAP*** //changing to return pos (was HEAP*)
void Insert(HEAP *heap, ELEMENT *newElement, Vertex v, struct Vertex vArray[], int f);

//***FUNCTION TO EXTRACT MIN ELEMENT FROM HEAP***
int ExtractMin(HEAP *heap, int flag, struct Vertex vArray[], int f);

//***FUNCTION TO EXTRACT MIN ELEMENT FROM HEAP***
void DecreaseKey(HEAP *heap, int index, int value, struct Vertex vArray[], int f);

//***FUNCTION TO RE-ORGANIZE MIN HEAP***
void minHeapify(HEAP *heap, int index, int flag, struct Vertex vArray[]);

void deleteHeap();

#endif //PROJECT3_HEAP_H

