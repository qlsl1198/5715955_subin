#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct GraphMatType {
    int n;
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphMatType;

GraphMatType* create_mat_graph(){
    return (GraphMatType*)malloc(sizeof(GraphMatType));
}

void destroy_mat_graph(GraphMatType* g){
    free(g);
}

void init_mat_graph(GraphMatType* g){
    g->n = 0;
    for (int i = 0; i < MAX_VERTICES; i++){
        for (int j = 0; j < MAX_VERTICES; j++){
            g->adj_mat[i][j] = 0;
        }
    }
}

void insert_vertex_mat_graph(GraphMatType* g, int v){
    if ((g->n) >= (MAX_VERTICES - 1)){
        fprintf(stderr, "Over number of vertex\n");
        return;
    }
    (g->n)++;
}

void insert_edge_mat_graph(GraphMatType* g, int s, int e){
    if (g->n <= s || g->n <= e){
        fprintf(stderr, "Vertex number error\n");
        return;
    }
    g->adj_mat[s][e] = 1;
    g->adj_mat[e][s] = 1;
}

void print_adj_mat(GraphMatType* g){
    printf("      ");
    for (int i = 0; i < g->n; i++){
        printf("%02d ", i);
    }
    printf("\n");

    for (int i = 0; i < g->n; i++){
        printf(" [%02d] ", i);
        for(int j = 0; j < g->n; j++){
            printf("%02d ", g->adj_mat[i][j]);
        }
        printf("\n");
    }
}

void GenerateGraph(GraphMatType* g){
    for (int i = 0; i <= 10; i++){
        insert_vertex_mat_graph(g, i);
    }

    insert_edge_mat_graph(g, 0, 5);
    insert_edge_mat_graph(g, 0, 2);
    insert_edge_mat_graph(g, 0, 4);
    insert_edge_mat_graph(g, 0, 6);
    insert_edge_mat_graph(g, 0, 9);
    insert_edge_mat_graph(g, 1, 4);
    insert_edge_mat_graph(g, 1, 5);
    insert_edge_mat_graph(g, 1, 7);
    insert_edge_mat_graph(g, 1, 10);
    insert_edge_mat_graph(g, 2, 3);
    insert_edge_mat_graph(g, 2, 4);
    insert_edge_mat_graph(g, 3, 4);
    insert_edge_mat_graph(g, 3, 5);
    insert_edge_mat_graph(g, 4, 5);
    insert_edge_mat_graph(g, 4, 6);
    insert_edge_mat_graph(g, 4, 7);
    insert_edge_mat_graph(g, 6, 7);
    insert_edge_mat_graph(g, 6, 8);
    insert_edge_mat_graph(g, 7, 10);
    insert_edge_mat_graph(g, 8, 9);
    insert_edge_mat_graph(g, 8, 10);
}

void print_menu(){
    printf("-------------------------\n");
    printf("1   :  깊이 우선 탐색     |\n");
    printf("2   :  너비 우선 탐색	  |\n");
    printf("3   :  종료	          |\n");
    printf("-------------------------\n");
}

void DFS(GraphMatType* g, int start, int end) {
    int stack[MAX_VERTICES];
    int top = -1;
    int visited[MAX_VERTICES] = {0};
    int count = 0;

    stack[++top] = start;
    printf("%d ", start);
    visited[start] = 1;

    while (top != -1) {
        int v = stack[top];
        
        if (v == end) {
            printf("\n탐색 성공: %d\n", end);
            printf("방문한 노드의 수: %d\n", count);
            return;
        }

        int found = 0;
        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1) {
                if (!visited[i] || i == end) {
                    stack[++top] = i;
                    printf("%d ", i);
                    if (!visited[i]) {
                        visited[i] = 1;
                        count++;
                    }
                    found = 1;
                    break;
                }
            }
        }

        if (!found) {
            top--;
            if (top >= 0) {
                printf("%d ", stack[top]);
                count++;
            }
        }
    }

    printf("\n탐색 실패\n");
    printf("방문한 노드의 수: %d\n", count);
}


void BFS(GraphMatType* g, int start, int end) {
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;
    int visited[MAX_VERTICES] = {0};
    int q = 0;

    queue[rear++] = start;
    visited[start] = 1;

    while (front != rear) {
        int v = queue[front++];
        printf("%d ", v);
        if (v == end) {
            printf("\n");
            printf("탐색 성공: %d\n", end);
            printf("방문한 노드의 수 %d\n", q);
            return;
        }

        for (int i = 0; i < g->n; i++) {
            if (g->adj_mat[v][i] == 1 && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
                q++;
            }
        }
    }
}

int main(){
    GraphMatType* g = create_mat_graph();
    init_mat_graph(g);
    GenerateGraph(g);

    int start, end;
    print_menu();

    while (1) {
        int a;
        printf("\n메뉴입력 : ");
        scanf("%d", &a);

        switch (a) {
            case 1:  // DFS
    printf("시작 정점과 목표 정점을 입력하세요: ");
    scanf("%d %d", &start, &end);
    DFS(g, start, end);
    break;
            
            case 2:  // BFS
                printf("시작 정점과 탐색 값: ");
                scanf("%d %d", &start, &end);
                BFS(g, start, end);
                printf("\n");
                break;

            case 3:  // 종료
                destroy_mat_graph(g);
                exit(0);
                break;

            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}