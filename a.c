#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/param.h>

#define SIZE 40
#define m 999999999

struct queue {
    int items[SIZE];
    int front;
    int rear;
};

int **MatrixAllocation(int size){
    int **M;
    M = (int **) malloc(sizeof(int *)*size);
    for(int i = 0; i < size; i++){
        M[i] = (int*) calloc(sizeof(int),size);
    }
    return M;
}

int **gen_rand(int size, float p){
    int **M = MatrixAllocation(size);
    srand(time(NULL));
    float u = 0;
    float uu;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            uu = rand();
            u = uu/m;
//            printf("uu value : %d\n", uu);
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

void print(int dist[], int V) {
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

    print(dist1d, V);
}

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

void bfs(struct Graph *graph, int startVertex) {
    struct queue *q = createQueue();

    // Add to visited list and put in queue
    graph->visited[startVertex] = 1;
    enqueue(q, startVertex);
    printf("Breadth first traversal from vertex %d is:\n", startVertex);

    // Iterate while queue not empty
    while (!isEmpty(q)) {
        printf("%d ", pollQueue(q));
        int currentVertex = dequeue(q);

        struct node *temp = graph->adjLists[currentVertex];
        // Add all unvisited neighbours of current vertex to queue to be printed
        // next
        while (temp) {
            int adjVertex = temp->vertex;
            // Only add if neighbour is unvisited
            if (graph->visited[adjVertex] == 0) {
                graph->visited[adjVertex] = 1;
                enqueue(q, adjVertex);
            }
            temp = temp->next;
        }
    }
}

// Returns element at front of queue
int pollQueue(struct queue *q) { return q->items[q->front]; }

int main(){
    int **M = gen_rand(8, 0.66);
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    for(int i =0; i<8; i++){
        M = MatrixProduct(M, M, 8);
    }
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    /*
    for(int i = 0; i<8; i++){
        for(int j = 0; j<8; j++){
            printf("%d\t", M[i][j]);
        }
        printf("\n");
    }
    */
    FloydWarshall(M, 8);
    return 0;
}

