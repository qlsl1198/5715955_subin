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

struct Edge {  // 간선을 나타내는 구조체
    int start, end, weight;
};

typedef struct GraphType {
    int n;  // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES];
int distance[MAX_VERTICES];

// 최소 힙 초기화
void init(MinHeap* h) {
    h->heap_size = 0;
}

// 최소 힙 삽입
void insert_min_heap(MinHeap* h, int vertex, int key) {
    int i = ++(h->heap_size);

    // 부모 노드와 비교하면서 올라가며 삽입
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].key = key;
}

// 최소 힙에서 최소 원소를 제거하고 반환
Element delete_min_heap(MinHeap* h) {
    int parent, child;
    Element item, temp;
    
    item = h->heap[1];
    temp = h->heap[(h->heap_size)--];

    parent = 1;
    child = 2;

    while (child <= h->heap_size) {
        // 자식 중 더 작은 자식 선택
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

int parent[MAX_VERTICES];  // 부모 노드
// 초기화
void set_init(int n) {
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

// curr가 속하는 집합을 반환한다.
int set_find(int curr) {
    if (parent[curr] == -1)
        return curr;  // 루트 
    while (parent[curr] != -1) curr = parent[curr];
    return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b) {
    int root1 = set_find(a);  // 노드 a의 루트를 찾는다. 
    int root2 = set_find(b);  // 노드 b의 루트를 찾는다. 
    if (root1 != root2)  // 합한다. 
        parent[root1] = root2;
}

// 그래프 초기화 
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  // 가중치 초기화
        }
    }
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
    g->edges[g->n].start = start;
    g->edges[g->n].end = end;
    g->edges[g->n].weight = w;
    g->n++;

    // 인접 행렬에 간선 추가
    g->weight[start][end] = w;
    g->weight[end][start] = w;  // 무방향 그래프
}

void FindPrimMST(GraphType* g) {
    int i, u, v;
    MinHeap h;
    init(&h);

    for (u = 0; u < g->n; u++) {
        distance[u] = INF;
        selected[u] = FALSE;
    }
    distance[1] = 0;
    insert_min_heap(&h, 1, 0);

    printf("Prim MST Algorithm\n");
    for (i = 0; i < g->n; i++) {
        Element min = delete_min_heap(&h);
        u = min.vertex;

        if (selected[u]) continue;
        selected[u] = TRUE;
        printf("정점 %d 추가\n", u);

        // 인접한 모든 정점에 대해 처리
        for (v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];
                insert_min_heap(&h, v, distance[v]);
            }
        }
    }
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

    FindPrimMST(g);  // 시작 정점을 1로 수정

    free(g);
    return 0;
}