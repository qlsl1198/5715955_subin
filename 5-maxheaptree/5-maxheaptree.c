#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
    struct TreeNode* parent;
} TreeNode;

// 새로운 노드를 생성하고 초기화하는 함수
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

// 두 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 트리를 레벨 순서로 출력하는 함수
void printTree(TreeNode* root) {
    if (!root) return;

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    printf("\n");
}

// 삽입된 노드를 최대 힙 특성을 유지하도록 부모와 교환하는 함수
void heapifyUp(TreeNode* node, int* movements, TreeNode* root) {
    while (node->parent && node->data > node->parent->data) {
        swap(&node->data, &node->parent->data);
        (*movements)++;
        printTree(root);  // 트리 전체를 출력
        node = node->parent;
    }
}

// 두 자식 노드를 비교하여 힙을 재정렬하는 함수
void heapifyDown(TreeNode* node, int* movements, TreeNode* root) {
    while (true) {
        TreeNode* largest = node;
        TreeNode* left = node->left;
        TreeNode* right = node->right;

        // 왼쪽 자식과 비교하여 더 큰 자식 선택
        if (left && left->data > largest->data)
            largest = left;

        // 오른쪽 자식과 비교하여 더 큰 자식 선택
        if (right && right->data > largest->data)
            largest = right;

        // 더 큰 자식과 현재 노드를 교환
        if (largest != node) {
            swap(&node->data, &largest->data);  // 값 교환
            (*movements)++;  // 이동 횟수 증가
            printTree(root);  // 트리 상태 출력
            node = largest;   // 현재 노드를 갱신하여 계속 힙 재정렬
        } else {
            break;  // 더 이상 교환이 필요 없으면 종료
        }
    }
}// 최대 힙 트리에 노드를 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int data, int* movements, bool showOutput) {
    if (*root == NULL) {
        *root = createNode(data);
        if (showOutput) printTree(*root);
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = *root;

    while (front < rear) {
        TreeNode* current = queue[front++];
        
        if (current->left == NULL) {
            current->left = createNode(data);
            current->left->parent = current;
            if (showOutput) printTree(*root);
            heapifyUp(current->left, movements, *root);
            break;
        } else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = createNode(data);
            current->right->parent = current;
            if (showOutput) printTree(*root);
            heapifyUp(current->right, movements, *root);
            break;
        } else {
            queue[rear++] = current->right;
        }
    }
}

// 트리에서 마지막 노드를 찾는 함수
TreeNode* findLastNode(TreeNode* root) {
    if (root == NULL) return NULL;

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;
    TreeNode* last = NULL;

    while (front < rear) {
        last = queue[front++];

        if (last->left) queue[rear++] = last->left;
        if (last->right) queue[rear++] = last->right;
    }

    return last;
}

// 최대 힙 트리에서 루트 노드를 삭제하는 함수
void deleteRoot(TreeNode** root, int* movements) {
    if (*root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }

    TreeNode* lastNode = findLastNode(*root);  // 마지막 노드를 찾음
    if (lastNode == *root) {  // 트리에 노드가 하나밖에 없으면
        free(*root);
        *root = NULL;
        return;
    }

    // 마지막 노드와 루트 노드를 교환한 후 마지막 노드를 삭제
    swap(&(*root)->data, &lastNode->data);
    (*movements)++;  // 루트와 마지막 노드의 값 교환 시 이동 횟수 증가

    if (lastNode->parent->left == lastNode)
        lastNode->parent->left = NULL;
    else
        lastNode->parent->right = NULL;

    free(lastNode);

    // 루트에서부터 힙 재정렬
    heapifyDown(*root, movements, *root);
}

void printLevelOrder(TreeNode* root){
  if(root == NULL){
      printf("트리가 비어 있습니다.\n");
      return;
  }

  TreeNode* queue[1000];
  int level[1000];
  int front = 0, rear = 0;

  queue[rear] = root;
  level[rear++] = 1;

  int currentLevel = 1;

  printf("[%d] ", currentLevel);

  // 큐를 사용하여 레벨별로 트리를 출력
  while(front < rear){
      TreeNode* current = queue[front];
      int nodeLevel = level[front++];

      if(nodeLevel > currentLevel){
          currentLevel = nodeLevel;
          printf("\n[%d] ", currentLevel);
      }

      printf("%d ", current -> data);

      if(current -> left != NULL){
          queue[rear] = current -> left;
          level[rear++] = nodeLevel + 1;
      }
      if(current -> right != NULL){
          queue[rear] = current -> right;
          level[rear++] = nodeLevel + 1;
      }
  }
  printf("\n");
}

// 사용자 인터페이스 실행 함수
void runUserInterface(TreeNode** root){
    while(true){
        char choice;
        int data, movements;
        printf("---------------------\n");
        printf("| i : 노드 추가     |\n");
        printf("| d : 루트 삭제     |\n");
        printf("| p : 레벨별 출력   |\n");
        printf("| c : 종료          |\n");
        printf("---------------------\n\n");
        printf("메뉴 입력: ");
        scanf(" %c", &choice);
        
        switch(choice){
            case 'i':  // 노드 추가
                printf("추가할 값 입력: ");
                scanf("%d", &data);
                movements = 0;
                InsertMaxHeapTree(root, data, &movements, true);
                printf("노드가 이동된 횟수: %d\n", movements);
                break;
            case 'd':  // 루트 노드 삭제
                movements = 0;
                deleteRoot(root, &movements);
                printTree(*root);  // 트리 상태 출력
                printf("노드가 이동된 횟수: %d\n", movements);
                break;
            case 'p':  // 트리 레벨별 출력
                printf("트리 레벨별 출력\n");
                printLevelOrder(*root);
                break;
            case 'c':  // 프로그램 종료
                exit(1);
                break;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

// 트리 생성 함수
TreeNode *GenerateMaxHeapTree(int inputData[], int size, int* movements){
    TreeNode* root = NULL;

     for(int i = 0; i < size; i++){
        InsertMaxHeapTree(&root, inputData[i], movements, false);
    }

    return root;
}

// 메인 함수
int main(){
    // 초기 데이터를 이용해 트리 생성
    int inputData[] = {90, 89, 70, 36, 75, 63, 65, 21, 18, 53};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    int movements = 0;
    
    TreeNode* root = GenerateMaxHeapTree(inputData, size, &movements);

    // 사용자 인터페이스 실행
    runUserInterface(&root);

    free(root);
    
    return 0;
}
