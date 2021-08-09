//Dijkstra's Algorithm Implementation

#include <stdio.h>
#include "heap.h"
#include <cmath>
#include <iostream>

HEAP *H;


void deleteHeap() {
    delete [] H;
}


//***FUNCTION TO BUILD HEAP***
HEAP *Initialize(int value)    //n is parameter for capacity of heap
{
    //DYNAMIC MEMORY ALLOCATION OCCURS
    //allocates memory space for the size of one HEAP struct
    HEAP *H = new HEAP[1]; //instantiate new pointer to HEAP struct



    if (!H) {
        printf("Error: cannot allocate memory for heap\n");
    } else {

        //initializes size to zero and sets capacity to value user has inputted
        H->capacity = value + 1;
        H->size = 0; //modified dijkstras to only add s to Q initially

        //DYNAMIC MEMORY ALLOCATION OCCURS
        //allocates memory space for the size of 'n + 1' elementP's
        H->elements = new elementP[value + 1];

        if (!H->elements) {
            printf("Error: cannot allocate memory for heap array\n");
        }
    }


    return H;
}

//***FUNCTION TO PRINT HEAP***
void printHeap(HEAP *heap) {

    if (heap->size == 0) {

        return;
    }
    printf("\nCurrent Queue:\n");
    //loops through the array and prints out element by element, using pointers
    for (int i = 1; i < heap->size; i++) {

        printf("Vertex = %d, ", heap->elements[i]->vertex);
        printf("key = %f, ", heap->elements[i]->key);
        printf("Pos = %d \n", heap->elements[i]->pos);
    };

    //to avoid excess comma, additional statement required
    printf("Vertex = %d, ", heap->elements[heap->size]->vertex);
    printf("key = %f, ", heap->elements[heap->size]->key);
    printf("Pos = %d \n", heap->elements[heap->size]->pos);

};

//***FUNCTION TO INSERT ELEMENT INTO HEAP***
void Insert(HEAP *heap, ELEMENT *newElement, Vertex v, struct Vertex vArray[], int f) {

    heap->size++;

    int i = heap->size;
    v.pos = i;
    heap->elements[i] = newElement;
    newElement->pos=v.pos;

    if (f == 1) {
        printf("Insert vertex %d", heap->elements[i]->vertex);
        printf(", key=%12.4f\n", heap->elements[i]->key);
    }

    int parent = floor(i / 2); //parent of index

    int dumbyPos2 = 0;

    //updates the position
    if (heap->size > 1) {
        while (i > 1 && heap->elements[parent]->key > heap->elements[i]->key) {
            dumbyPos2 = newElement->pos;
            newElement->pos = heap->elements[parent]->pos;
            heap->elements[parent]->pos = dumbyPos2;

            vArray[heap->elements[parent]->vertex].pos = dumbyPos2;
            vArray[heap->elements[i]->vertex].pos = newElement->pos;

            heap->elements[i] = heap->elements[parent];

            i = floor(i / 2);

            parent = floor(i / 2);
            heap->elements[i] = newElement;
        }
    }
   vArray[newElement->vertex].pos = newElement->pos;

    return;
}

//***FUNCTION TO EXTRACT MIN ELEMENT FROM HEAP***
int ExtractMin(HEAP *heap, int flag, struct Vertex vArray[], int f) {
    //the element to be deleted
    elementP extract = heap->elements[1];
    //the key of the minimum value to be returned
    int sendMin = extract->vertex;


    heap->elements[1] = heap->elements[heap->size];
    heap->elements[1]->pos = 1;
    vArray[heap->elements[1]->vertex].pos = 1;
    heap->size--;

    minHeapify(heap, 1, flag, vArray);

    if( heap->size ==1) {
        heap->elements[1]->pos=1;
        vArray[heap->elements[1]->vertex].pos=1;
    }

    if (f == 1) {
        printf("Delete vertex %d", extract->vertex);
        printf(", key=%12.4f\n", extract->key);
    }

    return sendMin;
}

//***FUNCTION TO DECREASE KEY OF HEAP***
void DecreaseKey(HEAP *heap, int index, int value, struct Vertex vArray[], int f) {

    if (index < 1 || index > heap->size) {
        if (f == 1) {
            printf("Error in decrease key\n");
        }
    }
    heap->elements[index]->key = value;

    return;

}


//***FUNCTION TO RE-ORGANIZE MIN HEAP***
void minHeapify(HEAP *heap, int index, int flag, struct Vertex vArray[]) {

    int l = (index * 2);
    int r = ((index * 2) + 1);    //right child
    int smallest = index;

    elementP temp;  //temp var for swap

    //minheapify algorithm
    if (l <= heap->size && heap->elements[l]->key < heap->elements[index]->key) {
        smallest = l;
    }

    if (r <= heap->size && heap->elements[r]->key < heap->elements[smallest]->key) {
        smallest = r;

    }
    if (smallest != index) {


        heap->elements[smallest]->pos = index;
        heap->elements[index]->pos = smallest;

        vArray[heap->elements[smallest]->vertex].pos = index;
        vArray[heap->elements[index]->vertex].pos = smallest;

        temp = heap->elements[smallest];
        heap->elements[smallest] = heap->elements[index];
        heap->elements[index] = temp;
        minHeapify(heap, smallest, flag, vArray);

    }

   return;
}
