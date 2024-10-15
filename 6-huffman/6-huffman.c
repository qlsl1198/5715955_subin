#include <stdio.h>
#include <stdlib.h>

// 허프만 트리의 노드 구조체 정의
typedef struct TreeNode {
    char character;
    int frequency;
    struct TreeNode *left, *right;
} TreeNode;

// 우선순위 큐를 관리할 노드 구조체
typedef struct MinHeapNode {
    TreeNode* treeNode;
    struct MinHeapNode* next;
} MinHeapNode;

// 우선순위 큐의 헤더 구조체
typedef struct MinHeap {
    MinHeapNode* head;
} MinHeap;

// 새로운 트리 노드를 생성하는 함수
TreeNode* createTreeNode(char character, int frequency) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 새로운 우선순위 큐 노드를 생성하는 함수
MinHeapNode* createMinHeapNode(TreeNode* treeNode) {
    MinHeapNode* newNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    return newNode;
}

// 우선순위 큐를 초기화하는 함수
MinHeap* createMinHeap() {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->head = NULL;
    return minHeap;
}

// 우선순위 큐 상태를 출력하는 함수
void printMinHeap(MinHeap* minHeap) {
    MinHeapNode* current = minHeap->head;
    while (current != NULL) {
        printf("%d ", current->treeNode->frequency);
        current = current->next;
    }
    printf("\n");
}

// 우선순위 큐에 노드를 삽입하는 함수
void insertMinHeap(MinHeap* minHeap, TreeNode* treeNode) {
    MinHeapNode* newNode = createMinHeapNode(treeNode);

    if (!minHeap->head || treeNode->frequency < minHeap->head->treeNode->frequency) {
        newNode->next = minHeap->head;
        minHeap->head = newNode;
    } else {
        MinHeapNode* current = minHeap->head;
        while (current->next && current->next->treeNode->frequency <= treeNode->frequency) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    // 삽입 후 현재 우선순위 큐 상태 출력
    printMinHeap(minHeap);
}

// 우선순위 큐에서 최소값을 제거하고 반환하는 함수
TreeNode* extractMin(MinHeap* minHeap) {
    if (!minHeap->head) return NULL;
    MinHeapNode* temp = minHeap->head;
    minHeap->head = minHeap->head->next;
    TreeNode* treeNode = temp->treeNode;
    free(temp);
    return treeNode;
}

// 허프만 트리를 생성하는 함수
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap();

    // 각 문자에 대해 트리 노드를 생성하고 우선순위 큐에 삽입
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createTreeNode(characters[i], frequencies[i]));
    }

    // 큐에 하나의 노드가 남을 때까지 반복하여 허프만 트리 빌드
    while (minHeap->head && minHeap->head->next) {
        // 가장 작은 두 개의 노드를 꺼냄
        TreeNode* left = extractMin(minHeap);
        TreeNode* right = extractMin(minHeap);

        // 부모 노드를 생성하여 트리를 결합하고 빈도 출력
        TreeNode* parent = createTreeNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        printf("/// %d + %d = %d\n", left->frequency, right->frequency, parent->frequency);

        // 새로운 부모 노드를 다시 우선순위 큐에 삽입
        insertMinHeap(minHeap, parent);
    }

    // 마지막에 남은 노드가 허프만 트리의 루트 노드가 됨
    return extractMin(minHeap);
}

// 허프만 코드를 출력하는 재귀 함수
void printCodes(TreeNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 1;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 0;
        printCodes(root->right, arr, top + 1);
    }

    // 리프 노드에 도달하면 허프만 코드 출력
    if (!root->left && !root->right) {
        printf("%c : ", root->character);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// 허프만 코드를 생성하는 함수
void GenerateHuffmanCodes(char characters[], int frequencies[], int size) {
    // 허프만 트리를 빌드
    TreeNode* root = buildHuffmanTree(characters, frequencies, size);

    // 허프만 코드 저장용 배열 및 상위 인덱스 초기화
    int arr[100], top = 0;

    // 트리를 순회하면서 허프만 코드 출력
    printCodes(root, arr, top);
}

int main() {
    char characters[] = {'a', 'e', 'i', 'o', 'u', 's', 't'};
    int frequencies[] = {10, 15, 12, 3, 4, 13, 1};

    int size = sizeof(characters) / sizeof(characters[0]);

    // 허프만 코드를 생성하고 출력
    GenerateHuffmanCodes(characters, frequencies, size);

    return 0;
}
