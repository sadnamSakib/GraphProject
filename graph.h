#ifndef GRAPH_H
#define GRAPH_H

#define INFINITY INT_MAX

// Structure to represent a node in the adjacency list
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure to represent the adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure to represent the graph
struct Graph {
    int vertices;
    struct AdjList* array;
};

// Structure to represent a min heap node
struct MinHeapNode {
    int v;
    int dist;
};

// Structure to represent a min heap
struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};

// Function prototypes
struct AdjListNode* newAdjListNode(int dest, int weight);
struct Graph* createGraph(int vertices);
void addEdge(struct Graph* graph, int src, int dest, int weight);
struct MinHeapNode* newMinHeapNode(int v, int dist);
struct MinHeap* createMinHeap(int capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
int isEmpty(struct MinHeap* minHeap);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void decreaseKey(struct MinHeap* minHeap, int v, int dist);
int isInMinHeap(struct MinHeap* minHeap, int v);
void dijkstra(struct Graph* graph, int src, int dist[]);

#endif // GRAPH_H
