#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000L

// 인접 리스트의 노드 구조체
typedef struct EdgeNode {
    int vertex;
    int weight;
    struct EdgeNode* next;
} EdgeNode;

// 그래프 구조체
typedef struct GraphType {
    int n;
    EdgeNode* adj_list[MAX_VERTICES];
} GraphType;

// 최소 힙에 저장할 요소
typedef struct {
    int vertex;
    int key;
} Element;

// 최소 힙 구조체
typedef struct {
    Element heap[MAX_VERTICES];
    int heap_size;
} MinHeap;

// 힙 초기화
void init_min_heap(MinHeap* h) {
    h->heap_size = 0;
}

// 힙에 요소 삽입
void insert_min_heap(MinHeap* h, int vertex, int key) {
    int i = ++(h->heap_size);
    while ((i != 1) && (key < h->heap[i / 2].key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].key = key;
}

// 힙에서 최소값 삭제
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

// 그래프 초기화
void graph_init(GraphType* g) {
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj_list[i] = NULL;
    }
}

// 간선 추가 (연결 리스트 사용)
void insert_edge(GraphType* g, int start, int end, int weight) {
    EdgeNode* node = (EdgeNode*)malloc(sizeof(EdgeNode));
    node->vertex = end;
    node->weight = weight;
    node->next = g->adj_list[start];
    g->adj_list[start] = node;

    // 무방향 그래프이므로 반대 방향도 추가
    node = (EdgeNode*)malloc(sizeof(EdgeNode));
    node->vertex = start;
    node->weight = weight;
    node->next = g->adj_list[end];
    g->adj_list[end] = node;
}

// 다익스트라 알고리즘
void Dijkstra(GraphType* g, int start) {
    MinHeap h;
    init_min_heap(&h);
    int distance[MAX_VERTICES];
    int selected[MAX_VERTICES] = { FALSE };
    int order[MAX_VERTICES];
    int count = 0;

    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;
    insert_min_heap(&h, start, 0);

    while (h.heap_size > 0) {
        Element min = delete_min_heap(&h);
        int u = min.vertex;

        if (selected[u]) continue;
        selected[u] = TRUE;
        order[count++] = u;  // 발견 순서 저장

        printf("Distance: ");
        for (int j = 1; j <= g->n; j++) {
            if (distance[j] == INF)
                printf(" *");
            else
                printf(" %d", distance[j]);
        }
        printf("\n");

        printf("Found: ");
        for (int j = 1; j <= g->n; j++) {
            printf(" %d", selected[j]);
        }
        printf("\n\n");

        // 인접 리스트 탐색
        for (EdgeNode* node = g->adj_list[u]; node != NULL; node = node->next) {
            int v = node->vertex;
            int weight = node->weight;

            if (!selected[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                insert_min_heap(&h, v, distance[v]);
            }
        }
    }

    printf("Found Order: ");
    for (int k = 0; k < count; k++) {
        printf("%d ", order[k]);
    }
    printf("\n");
}

// 그래프 데이터 추가
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
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);
    g->n = 10;  // 그래프의 정점 수 설정 (1부터 10까지 사용)

    Dijkstra(g, 1);  // 1번 정점을 시작으로 다익스트라 수행

    free(g);
    return 0;
}