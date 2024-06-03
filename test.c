#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "graph.h"

// Function prototypes
void test_shortest_path();
void test_disconnected_graph();
void test_negative_weights();
void test_single_node();
void test_no_edges();
void test_loops();
void test_multiple_shortest_paths();
void test_large_graph();

int main() {
    test_shortest_path();
    test_disconnected_graph();
    test_negative_weights();
    test_single_node();
    test_no_edges();
    test_loops();
    test_multiple_shortest_paths();
    test_large_graph();
    printf("All tests passed!\n");
    return 0;
}

// Function to print the distances (helper function for testing)
void printDist(int dist[], int n) {
    printf("Vertex Distance from Source\n");
    for (int i = 0; n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Test function for shortest path
void test_shortest_path() {
    int V = 6;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 4);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 1, 2);
    addEdge(graph, 1, 3, 1);
    addEdge(graph, 2, 3, 5);
    addEdge(graph, 3, 4, 3);
    addEdge(graph, 4, 5, 1);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0, 3, 1, 4, 7, 8 };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_shortest_path passed!\n");
    free(dist);
}

// Test function for disconnected graph
void test_disconnected_graph() {
    int V = 4;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 2);
    // No edge between 2 and 3, making vertex 3 disconnected

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0, 1, 3, INFINITY };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_disconnected_graph passed!\n");
    free(dist);
}

// Test function for negative weights (Dijkstra's algorithm should not handle this correctly)
void test_negative_weights() {
    int V = 3;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, -1); // Negative weight
    addEdge(graph, 1, 2, 2);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    // Dijkstra's algorithm does not work correctly with negative weights, 
    // so we are not asserting specific values here. Just checking if it runs.
    printf("test_negative_weights passed! (Note: Dijkstra's algorithm does not handle negative weights)\n");
    free(dist);
}

// Test function for a single node
void test_single_node() {
    int V = 1;
    struct Graph* graph = createGraph(V);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0 };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_single_node passed!\n");
    free(dist);
}

// Test function for a graph with multiple nodes but no edges
void test_no_edges() {
    int V = 3;
    struct Graph* graph = createGraph(V);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0, INFINITY, INFINITY };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_no_edges passed!\n");
    free(dist);
}

// Test function for a graph with loops
void test_loops() {
    int V = 3;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 0, 5); // Loop
    addEdge(graph, 1, 1, 3); // Loop
    addEdge(graph, 0, 2, 1);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0, INFINITY, 1 };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_loops passed!\n");
    free(dist);
}

// Test function for a graph with multiple shortest paths
void test_multiple_shortest_paths() {
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 4, 1);
    addEdge(graph, 0, 2, 1);
    addEdge(graph, 2, 3, 1);
    addEdge(graph, 3, 4, 1);
    addEdge(graph, 1, 3, 2);

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);
    int expected_distances[] = { 0, 1, 1, 2, 2 };

    for (int i = 0; i < V; i++) {
        assert(dist[i] == expected_distances[i]);
    }

    printf("test_multiple_shortest_paths passed!\n");
    free(dist);
}

// Test function for a large graph
void test_large_graph() {
    int V = 1000;
    struct Graph* graph = createGraph(V);
    for (int i = 0; i < V - 1; i++) {
        addEdge(graph, i, i + 1, 1);
    }

    int* dist = (int*)malloc(V * sizeof(int));
    if (dist == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    dijkstra(graph, 0, dist);

    for (int i = 0; i < V; i++) {
        assert(dist[i] == i);
    }

    printf("test_large_graph passed!\n");
    free(dist);
}
