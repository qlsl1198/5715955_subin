#include <stdio.h>
#include <stdlib.h>

// 허프만 트리의 노드 구조체 정의
typedef struct TreeNode {
    char character;
    int frequency;
    struct TreeNode *left, *right;
} TreeNode;

// 우선순위 큐(최소 힙)의 구조체 정의
typedef struct MinHeap {
    int size;
    int capacity;
    TreeNode** array;
} MinHeap;

// 새로운 트리 노드를 생성하는 함수
TreeNode* createTreeNode(char character, int frequency) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->character = character;
    newNode->frequency = frequency;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// 우선순위 큐를 초기화하는 함수
MinHeap* createMinHeap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (TreeNode**)malloc(capacity * sizeof(TreeNode*));
    return minHeap;
}

// 두 노드를 교환하는 함수
void swap(TreeNode** a, TreeNode** b) {
    TreeNode* temp = *a;
    *a = *b;
    *b = temp;
}

// 우선순위 큐 상태를 출력하는 함수
void printMinHeap(MinHeap* minHeap) {
    for (int i = 0; i < minHeap->size; i++) {
        printf("%d ", minHeap->array[i]->frequency);
    }
    printf("\n");
}

// 힙 속성을 유지하며 노드를 위로 올리는 함수
void heapifyUp(MinHeap* minHeap, int index) {
    int parent = (index - 1) / 2;
    while (index > 0 && minHeap->array[index]->frequency < minHeap->array[parent]->frequency) {
        swap(&minHeap->array[index], &minHeap->array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}

// 우선순위 큐에 노드를 삽입하는 함수
void insertMinHeap(MinHeap* minHeap, TreeNode* treeNode) {
    if (minHeap->size == minHeap->capacity) {
        printf("Heap is full\n");
        return;
    }

    minHeap->size++;
    int i = minHeap->size - 1;
    minHeap->array[i] = treeNode;

    heapifyUp(minHeap, i);

    // 삽입 후 현재 우선순위 큐 상태 출력
    printMinHeap(minHeap);
}

// 힙 속성을 유지하며 노드를 아래로 내리는 함수
void heapifyDown(MinHeap* minHeap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swap(&minHeap->array[index], &minHeap->array[smallest]);
        heapifyDown(minHeap, smallest);
    }
}

// 우선순위 큐에서 최소값을 제거하고 반환하는 함수
TreeNode* extractMin(MinHeap* minHeap) {
    if (minHeap->size <= 0) return NULL;
    if (minHeap->size == 1) {
        minHeap->size--;
        return minHeap->array[0];
    }

    TreeNode* root = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    heapifyDown(minHeap, 0);

    return root;
}

// 허프만 트리를 생성하는 함수
TreeNode* buildHuffmanTree(char characters[], int frequencies[], int size) {
    MinHeap* minHeap = createMinHeap(size);

    // 각 문자에 대해 트리 노드를 생성하고 우선순위 큐에 삽입
    for (int i = 0; i < size; i++) {
        insertMinHeap(minHeap, createTreeNode(characters[i], frequencies[i]));
    }

    // 큐에 하나의 노드가 남을 때까지 반복하여 허프만 트리 빌드
    while (minHeap->size > 1) {
        // 가장 작은 두 개의 노드를 꺼냄
        TreeNode* left = extractMin(minHeap);
        TreeNode* right = extractMin(minHeap);

        // 부모 노드를 생성하여 트리를 결합하고 빈도 출력
        TreeNode* parent = createTreeNode('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        printf("///%d + %d -> %d\n", left->frequency, right->frequency, parent->frequency);

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
