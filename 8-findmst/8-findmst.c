#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100
#define INF 1000

int parent[MAX_VERTICES];		// 부모 노드
							// 초기화
void set_init(int n)
{
	for (int i = 0; i<n; i++) 
		parent[i] = -1;
}
// curr가 속하는 집합을 반환한다.
int set_find(int curr)
{
	if (parent[curr] == -1)
		return curr; 			// 루트 
	while (parent[curr] != -1) curr = parent[curr];
	return curr;
}

// 두개의 원소가 속한 집합을 합친다.
void set_union(int a, int b)
{
	int root1 = set_find(a);	// 노드 a의 루트를 찾는다. 
	int root2 = set_find(b);	// 노드 b의 루트를 찾는다. 
	if (root1 != root2) 	// 합한다. 
		parent[root1] = root2;
}

struct Edge {			// 간선을 나타내는 구조체
	int start, end, weight;
};

typedef struct GraphType {
	int n;	// 간선의 개수
	struct Edge edges[2 * MAX_VERTICES];
} GraphType;

// 그래프 초기화 
void graph_init(GraphType* g)
{
	g->n = 0;
	for (int i = 0; i < 2 * MAX_VERTICES; i++) {
		g->edges[i].start = 0;
		g->edges[i].end = 0;
		g->edges[i].weight = INF;
	}
}
// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w)
{
	g->edges[g->n].start = start;
	g->edges[g->n].end = end;
	g->edges[g->n].weight = w;
	g->n++;
}
// qsort()에 사용되는 함수
int compare(const void* a, const void* b)
{
	struct Edge* x = (struct Edge*)a;
	struct Edge* y = (struct Edge*)b;
	return (x->weight - y->weight);
}

// kruskal의 최소 비용 신장 트리 프로그램
void QuickKruskal(GraphType *g)
{
	int edge_accepted = 0;	// 현재까지 선택된 간선의 수	
	int uset, vset;			// 정점 u와 정점 v의 집합 번호
	struct Edge e;

	set_init(g->n);				// 집합 초기화
	qsort(g->edges, g->n, sizeof(struct Edge), compare);

	printf("Qucik Based Kruskal \n");
	int i = 0;
	while (edge_accepted < (g->n - 1) && i < g->n)	// 간선의 수 < (n-1)
	{
		e = g->edges[i];
		uset = set_find(e.start);		// 정점 u의 집합 번호 
		vset = set_find(e.end);		// 정점 v의 집합 번호
		if (uset != vset) {			// 서로 속한 집합이 다르면
			printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
			edge_accepted++;
			set_union(uset, vset);	// 두개의 집합을 합친다.
		}
		i++;
	}
    printf("\n");
}

// MinHeap 구조체 정의
typedef struct {
    struct Edge* heap;
    int size;
    int capacity;
} MinHeap;

// MinHeap 초기화
void initMinHeap(MinHeap* h, int capacity) {
    h->heap = (struct Edge*)malloc(capacity * sizeof(struct Edge));
    h->size = 0;
    h->capacity = capacity;
}

// MinHeap에 원소 삽입
void insert(MinHeap* h, struct Edge item) {
    int i = h->size++;
    while (i > 0 && item.weight < h->heap[(i - 1) / 2].weight) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i] = item;
}

// MinHeap에서 최소 원소 추출
struct Edge extractMin(MinHeap* h) {
    struct Edge minItem = h->heap[0];
    struct Edge lastItem = h->heap[--h->size];
    int i = 0, j = 1;
    while (j < h->size) {
        if (j < h->size - 1 && h->heap[j].weight > h->heap[j + 1].weight)
            j++;
        if (lastItem.weight <= h->heap[j].weight)
            break;
        h->heap[i] = h->heap[j];
        i = j;
        j = 2 * i + 1;
    }
    h->heap[i] = lastItem;
    return minItem;
}

void MinHeapKruskal(GraphType* g) {
    int edge_accepted = 0;
    int uset, vset;
    struct Edge e;
    MinHeap minHeap;

    set_init(g->n);
    initMinHeap(&minHeap, g->n);

    // MinHeap에 모든 간선 삽입
    for (int i = 0; i < g->n; i++) {
        insert(&minHeap, g->edges[i]);
    }

    printf("MinHeap Based Kruskal \n");
    while (edge_accepted < (g->n - 1) && minHeap.size > 0) {
        e = extractMin(&minHeap);
        uset = set_find(e.start);
        vset = set_find(e.end);
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start, e.end, e.weight);
            edge_accepted++;
            set_union(uset, vset);
        }
    }

    free(minHeap.heap);
}

void GenerateGraph(GraphType* g){
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

int main(void)
{
	GraphType *g;
	g = (GraphType *)malloc(sizeof(GraphType));
	graph_init(g);

    GenerateGraph(g);
    
    QuickKruskal(g);
    MinHeapKruskal(g);
 
	free(g);
	return 0;
}
