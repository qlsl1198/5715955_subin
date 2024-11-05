#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

typedef struct {
    int vertex;
    int key;
} Element;

typedef struct {
    Element heap[MAX_VERTICES];
    int heap_size;
} MinHeap;

struct Edge {
    int start, end, weight;
};

typedef struct GraphType {
    int n;
    int weight[MAX_VERTICES][MAX_VERTICES];
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

void init(MinHeap* h) {
    h->heap_size = 0;
}

void insert_min_heap(MinHeap* h, int vertex, int key) {
    int i = ++(h->heap_size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].key = key;
}

Element delete_min_heap(MinHeap* h) {
    int parent, child;
    Element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        if ((child < h->heap_size) && (h->heap[child].key > h->heap[child + 1].key))
            child++;
        if (temp.key <= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child *= 2;
    }
    h->heap[parent] = temp;
    return item;
}

void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;
        }
    }
}

void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;

    g->weight[start][end] = w;
    g->weight[end][start] = w;
}

void Dijkstra(GraphType* g) {
    int i, u, v;
    MinHeap h;
    init(&h);
    int order[MAX_VERTICES];
    int count = 0;

    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[1] = 0;
    insert_min_heap(&h, 1, 0);

    while (h.heap_size > 0) {
        Element min = delete_min_heap(&h);
        u = min.vertex;

        if (selected[u]) continue;
        selected[u] = TRUE;
        order[count++] = u;  // 발견 순서 저장

        printf("Distance : ");
        // Print distance array
        for (int j = 1; j <= 10; j++) {
            if (distance[j] == INF)
                printf(" *");
            else
                printf(" %d", distance[j]);
        }
        printf("\n");

        printf("Found : ");
        // Print Found array
        for (int j = 1; j <= 10; j++) {
            printf(" %d", selected[j]);
        }
        printf("\n\n");

        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v]) {
                int new_dist = distance[u] + g->weight[u][v];
                if (new_dist < distance[v]) {
                    distance[v] = new_dist;
                    insert_min_heap(&h, v, distance[v]);
                }
            }
        }
    }

    printf("Found Order: ");
    for (int k = 0; k < count; k++) {
        printf("%d ", order[k]);
    }
    printf("\n");
}


void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    Dijkstra(g);

    free(g);
    return 0;
}
