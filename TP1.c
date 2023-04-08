#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/param.h>

#define SIZE 40
#define m 999999999

//queue structure that will be used for the bfs algorithm
struct queue {
    int items[SIZE];
    int front;
    int rear;
};

/** @brief Allocates square matrix of size 'size'
*   @param size the size of the matrix
*   @returns array of arrays of integers
*/
int **MatrixAllocation(int size){
    int **M;
    M = (int **) malloc(sizeof(int *)*size);
    for(int i = 0; i < size; i++){
        M[i] = (int*) calloc(sizeof(int),size);
    }
    return M;
}

/**@brief generates a random oriented adjacency matrix
*  @param size the size of the matrix
*  @param p as given in the question
*  @returns the adjacency matrix
*/
int **gen_rand(int size, float p){
    int **M = MatrixAllocation(size);
    srand(time(NULL));
    float u = 0;
    float uu;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            uu = rand();
            u = uu/m;
            if(u>p){
                M[i][j] = 0;
            }
            else {
                M[i][j] = 1;
            }
        }
    }
    return M;
}

/**@brief generates a random non-oriented adjacency matrix
*  @param size the size of the matrix
*  @param p as given in the question
*  @returns the adjacency matrix
*/
int **gen_nonoriented(int size, float p){
    int **M = MatrixAllocation(size);
    srand(time(NULL));
    float u = 0;
    float uu;
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
            uu = rand();
            u = uu/m;
            if(u>p){
                M[i][j] = 0;
                M[j][i] = 0;
            }
            else {
                M[i][j] = 1;
                M[j][i] = 1;
            }
        }
    }
    return M;
}

/**@brief generates a random oriented weighted adjacency matrix
*  @param size the size of the matrix
*  @param p as given in the question
*  @returns the adjacency matrix
*/
int **gen_weighted(int size, float p){
    int **M = MatrixAllocation(size);
    srand(time(NULL));
    float u = 0;
    int uu;
    for(int i = 0; i < size; i++){
        for(int j = i; j < size; j++){
            uu = rand();
            u = uu/m;
            if(u>p){
                M[i][j] = 0;
                M[j][i] = 0;
            }
            else {
                M[i][j] = uu%84;
                M[j][i] = uu%84;
            }
        }
    }
    return M;
}

/**@brief calculates product of 2 matrices and returns it (product as defined in class)
*  @param Matrix1 the first matrix
*  @param Matrix2 the second matrix
*  @param size    the size of the matrices
*  @returns the product of the matrices
*/
int **MatrixProduct(int **Matrix1, int **Matrix2, int size) {
    int **Product = MatrixAllocation(size);
    for(int i=0;i<size;i++) {
        for(int j=0;j<size;j++) {
            for(int n=0;n<size;n=n+1) {
                Product[i][j]=MAX(Product[i][j],Matrix1[i][n]*Matrix2[n][j]);
            }
        }
    }
    return Product;
}

/**@brief prints the floydwarshall result
*  @param dist the distance array
*  @param V the size of the matrix
*/
void printfloyd(int dist[], int V) {
    printf("\nThe Distance matrix for Floyd - Warshall\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i * V + j] != INT_MAX)
                printf("%d\t", dist[i * V + j]);
            else
                printf("INF\t");
        }
        printf("\n");
    }
}

/**@brief the Floyd Warshall algorithm to calculate distances
*  @param dist the matrix of which we calculate the distances
*  @param V    the size of the matrix
*/
void FloydWarshall(int **dist, int V) {
    // Calculate distances
    for (int k = 0; k < V; k++)
        // Choose an intermediate vertex

        for (int i = 0; i < V; i++)
            // Choose a source vertex for given intermediate

            for (int j = 0; j < V; j++)
                // Choose a destination vertex for above source vertex

                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j])
                    // If the distance through intermediate vertex is less than
                    // direct edge then update value in distance array
                    dist[i][j] = dist[i][k] + dist[k][j];

    // Convert 2d array to 1d array for print
    int dist1d[V * V];
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++) dist1d[i * V + j] = dist[i][j];

    printfloyd(dist1d, V);
}

/**@brief allocates and returns queue variable
*  @returns allocated and initialized pointer to a queue variable
*/
struct queue *createQueue() {
    struct queue *q = malloc(sizeof(struct queue));
    q->front = -1;
    q->rear = -1;
    return q;
}

// Checks for empty queue
int isEmpty(struct queue *q) {
    if (q->rear == -1)
        return 1;
    else
        return 0;
}

// Inserts item at start of queue
void enqueue(struct queue *q, int value) {
    if (q->rear == SIZE - 1)
        printf("\nQueue is Full!!");
    else {
        if (q->front == -1)
            q->front = 0;
        q->rear++;
        q->items[q->rear] = value;
    }
}

// Returns item at front of queue and removes it from queue
int dequeue(struct queue *q) {
    int item;
    if (isEmpty(q)) {
        printf("Queue is empty");
        item = -1;
    }
    else {
        item = q->items[q->front];
        q->front++;
        if (q->front > q->rear) {
            q->front = q->rear = -1;
        }
    }
    return item;
}

// Returns element at front of queue
int pollQueue(struct queue *q) { return q->items[q->front]; }

/**@brief the bfs algorithm for graphs
*  @param Matrix the matrix we are going to apply the algorithm to
*  @param startVertex the starting vertex of the algorithm
*  @param size the size of the adjacency matrix
*/
void bfs(int **Matrix, int startVertex, int size) {
    struct queue *q = createQueue();
    int visited[size];
    for(int i = 0; i<size; i++){
        visited[i] = 0;
    }

    // Add to visited list and put in queue
    visited[startVertex] = 1;
    enqueue(q, startVertex);
    printf("Breadth first traversal from vertex %d is:\n", 0);

    // Iterate while queue not empty
    while (!isEmpty(q)) {
        printf("%d ", pollQueue(q));
        int currentVertex = dequeue(q);

        // Add all unvisited neighbours of current vertex to queue to be printed
        // next
        for(int i = 0; i< size; i++){
           if(Matrix[currentVertex][i] == 1 && visited[i] == 0){
               visited[i] = 1;
               enqueue(q, i);
           }
        }
    }
}

/**@brief adapted bfs algorithm to find the shortest paths
*  @param Matrix the matrix we are going to apply the algorithm to
*  @param startVertex the starting vertex of the algorithm
*  @param size the size of the adjacency matrix
*/
void bfs_shortest_path(int **Matrix, int startVertex, int size) {
    struct queue *q = createQueue();
    int visited[size];
    int distance[size];

    for(int i = 0; i < size; i++) {
        visited[i] = 0;
        distance[i] = INT_MAX;
    }

    visited[startVertex] = 1;
    distance[startVertex] = 0;
    enqueue(q, startVertex);

    while (!isEmpty(q)) {
        int currentVertex = dequeue(q);

        for(int i = 0; i < size; i++) {
            if(Matrix[currentVertex][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                distance[i] = distance[currentVertex] + 1;
                enqueue(q, i);
            }
        }
    }

    printf("Shortest distances from vertex %d:\n", startVertex);
    for(int i = 0; i < size; i++) {
        printf("%d: %d\n", i, distance[i]);
    }
}

/**@brief the print function for printing vertice distances of bfs
*  @param dist the distance array
*  @param V the size of the matrix
*/
void print(int dist[], int V) {
    printf("\nVertex  Distance\n");
    for (int i = 0; i < V; i++)
    {
        if (dist[i] != INT_MAX)
            printf("%d\t%d\n", i, dist[i]);
        else
            printf("%d\tINF", i);
    }
}

/**@brief calculates minimum distance for the dijkstra algorithm
*  @param mdist the distances array
*  @param vset  the visited vertex array
*  @param V     the size of the adjacency matrix
*  @returns the index of minimum value
*/
int minDistance(int mdist[], int vset[], int V) {
    int minVal = INT_MAX;
    static int minInd = -1; //remembers the previous value if not modified in the loop
    for (int i = 0; i < V; i++)
        if (vset[i] == 0 && mdist[i] < minVal) {
            minVal = mdist[i];
            minInd = i;
        }

    return minInd;
}

/**@brief the dijkstra algorithm
*  @param graph the adjacency matrix
*  @param size the size of the matrix
*  @param src the first vertex to search
*/
void Dijkstra(int **graph, int size, int src) {
    int mdist[size];  // Stores updated distances to vertex
    int vset[size];   // vset[i] is true if the vertex i included
                   // in the shortest path tree

    // Initialise mdist and vset. Set distance of source as zero
    for (int i = 0; i < size; i++) mdist[i] = INT_MAX, vset[i] = 0;

    mdist[src] = 0;

    // iterate to find shortest path
    for (int count = 0; count < size - 1; count++) {
        int u = minDistance(mdist, vset, size);
        vset[u] = 1;

        for (int v = 0; v < size; v++) {
            if (!vset[v] && graph[u][v] != INT_MAX &&
                mdist[u] + graph[u][v] < mdist[v])
                mdist[v] = mdist[u] + graph[u][v];
        }
    }

    print(mdist, size);
    return;
}

int main(){
    int **M = gen_rand(8, 0.66);
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    bfs_shortest_path(M, 5, 8);
//    Dijkstra(M, 8, 0);
    return 0;
}
