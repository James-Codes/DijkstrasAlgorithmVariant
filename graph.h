//Dijkstra's Algorithm Implementation

class graph {

};


//Struct for nodes in adjacency list
struct AdjListNode {
    int src; //predescessor
    int dest; //vertex
    float w; //weight
    struct AdjListNode *next;
};

//Adjacency List Structure
struct AdjList {
    struct AdjListNode *head;
};

//Graph Structure, an array of adjacency lists
//V represents the size of the array or number of vertices
//specifies directed or undirected
struct Graph {
    int directed; //1 for directed, 0 for undirected
    int V; //number of vertices
    struct AdjList *array; //linked list of adjacent nodes
};

//function to create a new adjacency list node
struct AdjListNode *newAdjListNode(int dest, int weight);

//function to create a graph
struct Graph *createGraph(int V, int flag);

//function to add edge to undirected graph
void addEdge(struct Graph *graph, int src, int dest, float weight, int flag);

void deleteGraph();


