#include <stdio.h>
#include <stdlib.h>

// Maximum number of vertices
#define MAX_VERTICES 10

// Queue structure for BFS
typedef struct {
    int items[MAX_VERTICES];
    int front, rear;
} Queue;

// Graph structure
typedef struct {
    int vertices;
    int** adjacencyMatrix;
} Graph;

// Function prototypes
Graph createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void displayAdjacencyMatrix(Graph* graph);
void BFS(Graph* graph, int startVertex);
void DFS(Graph* graph, int startVertex, int visited[MAX_VERTICES]);
void DFSUtil(Graph* graph, int vertex, int visited[MAX_VERTICES]);

int main() {
    int vertices, choice, src, dest, startVertex;

    // Accept the number of vertices from the user
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    // Create a graph with the given number of vertices
    Graph graph = createGraph(vertices);

    // Menu for adding edges
    do {
        printf("\nMenu:\n");
        printf("1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. BFS Traversal\n");
        printf("4. DFS Traversal\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Add an edge to the graph
                printf("Enter source vertex: ");
                scanf("%d", &src);
                printf("Enter destination vertex: ");
                scanf("%d", &dest);
                addEdge(&graph, src, dest);
                break;
            case 2:
                // Display the adjacency matrix
                displayAdjacencyMatrix(&graph);
                break;
            case 3:
                // Perform BFS traversal
                printf("Enter the starting vertex for BFS: ");
                scanf("%d", &startVertex);
                BFS(&graph, startVertex);
                break;
            case 4:
                // Perform DFS traversal
                printf("Enter the starting vertex for DFS: ");
                scanf("%d", &startVertex);
                int visited[MAX_VERTICES] = {0};
                DFS(&graph, startVertex, visited);
                break;
            case 5:
                // Exit the program
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}

// Function to create a graph with a given number of vertices
Graph createGraph(int vertices) {
    Graph graph;
    graph.vertices = vertices;

    // Allocate memory for the adjacency matrix
    graph.adjacencyMatrix = (int**)malloc(vertices * sizeof(int*));
    for (int i = 0; i < vertices; i++) {
        graph.adjacencyMatrix[i] = (int*)malloc(vertices * sizeof(int));
    }

    // Initialize the adjacency matrix to 0
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            graph.adjacencyMatrix[i][j] = 0;
        }
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(Graph* graph, int src, int dest) {
    if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
        // Add the edge to the adjacency matrix
        graph->adjacencyMatrix[src][dest] = 1;
        graph->adjacencyMatrix[dest][src] = 1;
        printf("Edge (%d, %d) added to the graph.\n", src, dest);
    } else {
        printf("Invalid vertices. Please enter valid vertices.\n");
    }
}

// Function to display the adjacency matrix
void displayAdjacencyMatrix(Graph* graph) {
    printf("Adjacency Matrix:\n");
    for (int i = 0; i < graph->vertices; i++) {
        for (int j = 0; j < graph->vertices; j++) {
            printf("%d ", graph->adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
}

// Function to perform Breadth-First Search (BFS) traversal
void BFS(Graph* graph, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue queue;
    queue.front = queue.rear = -1;

    // Mark the starting vertex as visited and enqueue it
    visited[startVertex] = 1;
    printf("BFS Traversal starting from vertex %d: ", startVertex);
    printf("%d ", startVertex);
    queue.items[++queue.rear] = startVertex;

    while (queue.front <= queue.rear) {
        int currentVertex = queue.items[queue.front++];

        for (int i = 0; i < graph->vertices; i++) {
            if (graph->adjacencyMatrix[currentVertex][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                printf("%d ", i);
                queue.items[++queue.rear] = i;
            }
        }
    }

    printf("\n");
}

// Function to perform Depth-First Search (DFS) traversal
void DFS(Graph* graph, int startVertex, int visited[MAX_VERTICES]) {
    printf("DFS Traversal starting from vertex %d: ", startVertex);
    DFSUtil(graph, startVertex, visited);
    printf("\n");
}

// Utility function for DFS traversal
void DFSUtil(Graph* graph, int vertex, int visited[MAX_VERTICES]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->vertices; i++) {
        if (graph->adjacencyMatrix[vertex][i] == 1 && visited[i] == 0) {
            DFSUtil(graph, i, visited);
        }
    }
}
