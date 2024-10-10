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
    if (newNode == NULL) {  // 메모리 할당 실패 시 에러 출력
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    newNode->data = data;  // 노드 데이터 설정
    newNode->left = newNode->right = newNode->parent = NULL;  // 자식과 부모 포인터 NULL로 초기화
    return newNode;
}

// 두 값을 교환하는 함수
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 트리를 레벨 순서로 출력하는 함수 (큐를 이용한 순회)
void printTree(TreeNode* root) {
    if (!root) return;

    TreeNode* queue[1000];
    int front = 0, rear = 0;

    queue[rear++] = root;

    // 큐를 사용하여 레벨 순서로 노드를 순회하며 출력
    while (front < rear) {
        TreeNode* current = queue[front++];
        printf("%d ", current->data);

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
    printf("\n");
}

// 삽입된 노드를 최대 힙 특성을 유지하도록 부모와 교환하는 함수
void heapifyUp(TreeNode* node, int* movements) {
    while (node->parent && node->data > node->parent->data) {
        swap(&node->data, &node->parent->data);  // 부모와 자식 노드의 데이터 교환
        (*movements)++;  // 교환 횟수 증가
        printTree(node);  // 트리 출력
        node = node->parent;  // 부모 노드로 이동
    }
}

// 최대 힙 트리에 노드를 삽입하는 함수
void InsertMaxHeapTree(TreeNode** root, int data, int* movements) {
    if (*root == NULL) {  // 루트가 비어있으면 새 노드를 루트로 설정
        *root = createNode(data);
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    
    queue[rear++] = *root;

    // 레벨 순서로 트리를 순회하며 빈 자리를 찾아서 노드를 삽입
    while (front < rear) {
        TreeNode* current = queue[front++];
        
        if (current->left == NULL) {
            current->left = createNode(data);
            current->left->parent = current;
            heapifyUp(current->left, movements);  // 삽입된 노드를 힙 정렬
            break;
        } else {
            queue[rear++] = current->left;
        }

        if (current->right == NULL) {
            current->right = createNode(data);
            current->right->parent = current;
            heapifyUp(current->right, movements);  // 삽입된 노드를 힙 정렬
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

    // 레벨 순서로 순회하며 마지막 노드를 찾음
    while (front < rear) {
        last = queue[front++];
        
        if (last->left) queue[rear++] = last->left;
        if (last->right) queue[rear++] = last->right;
    }

    return last;
}

// 삭제 후 최대 힙 특성을 유지하도록 자식과 교환하는 함수
void heapifyDown(TreeNode* node, int* movements) {
    while (true) {
        TreeNode* largest = node;
        TreeNode* left = node->left;
        TreeNode* right = node->right;

        // 자식 중에서 더 큰 값을 가진 노드를 찾음
        if (left && left->data > largest->data)
            largest = left;
        if (right && right->data > largest->data)
            largest = right;

        if (largest != node) {
            swap(&node->data, &largest->data);  // 큰 값과 교환
            (*movements)++;
            printTree(node);  // 트리 출력
            node = largest;
        } else {
            break;
        }
    }
}

// 최대 힙 트리에서 루트 노드를 삭제하는 함수
void deleteRoot(TreeNode** root, int* movements) {
    if (*root == NULL) {
        printf("트리가 비어 있습니다.\n");
        return;
    }

    TreeNode* lastNode = findLastNode(*root);  // 마지막 노드를 찾음

    if (lastNode == *root) {  // 루트 노드가 유일한 노드일 경우
        free(*root);
        *root = NULL;
        return;
    }

    // 루트와 마지막 노드를 교환하고 마지막 노드를 삭제
    swap(&(*root)->data, &lastNode->data);

    if (lastNode->parent->left == lastNode)
        lastNode->parent->left = NULL;
    else
        lastNode->parent->right = NULL;

    free(lastNode);
    
    heapifyDown(*root, movements);  // 힙 정렬
}

// 트리의 모든 노드를 재귀적으로 해제하는 함수
void freeTree(TreeNode* root) {
    if(root == NULL) return;
    freeTree(root -> left);
    freeTree(root -> right);
    free(root);
}

// 트리의 레벨별로 노드를 출력하는 함수
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
    bool exit = false;
    while(!exit){
        char choice;
        int data, movements;
        printf("---------------------\n");
        printf("| i : 노드 추가     |\n");
        printf("| d : 노드 삭제     |\n");
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
                InsertMaxHeapTree(root, data, &movements);
                printf("노드가 이동된 횟수: %d\n", movements);
                break;
            case 'd':  // 루트 노드 삭제
                movements = 0;
                deleteRoot(root, &movements);
                printf("노드가 이동된 횟수: %d\n", movements);
                break;
            case 'p':  // 트리 레벨별 출력
                printf("트리 레벨별 출력\n");
                printLevelOrder(*root);
                break;
            case 'c':  // 프로그램 종료
                exit = true;
                break;
            default:
                printf("잘못된 선택입니다.\n");
        }
    }
}

// 메인 함수
int main(){
    // 초기 데이터를 이용해 트리 생성
    int inputData[] = {90, 89, 70, 36, 75, 63, 65, 21, 18, 15};
    int size = sizeof(inputData) / sizeof(inputData[0]);
    
    TreeNode* root = NULL;
    for(int i = 0; i < size; i++){
        int movements = 0;
        InsertMaxHeapTree(&root, inputData[i], &movements);  // 데이터 삽입
    }
    runUserInterface(&root);  // 사용자 인터페이스 실행

    freeTree(root);  // 메모리 해제

    return 0;
}
