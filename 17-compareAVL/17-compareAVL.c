#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000
#define VALUE 1000

typedef struct Node {
    int key;
    struct Node* left, *right;
    int height;
} Node;

int compareCount = 0;
int searchCount = 0;

// 노드의 높이를 반환하는 함수
int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// 두 정수 중 큰 값을 반환하는 함수
int max(int a, int b) {
    return (a > b) ? a : b;
}

// 새 노드를 생성하는 함수
Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;  // 새 노드는 리프 노드이므로 높이는 1
    return(node);
}

// 오른쪽으로 회전
Node* rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// 왼쪽으로 회전
static Node* leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// 균형 인수를 구하는 함수
int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// AVL 트리에 노드를 삽입하는 함수
Node* insertAVL(Node* node, int key) {
    if (node == NULL)
        return(newNode(key));

    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else  // 중복된 키는 허용하지 않음
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // 왼쪽-왼쪽 케이스
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // 오른쪽-오른쪽 케이스
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // 왼쪽-오른쪽 케이스
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // 오른쪽-왼쪽 케이스
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// 최소값 노드를 찾는 함수
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// 이진 탐색 트리에 노드를 삽입하는 함수
Node* insertBST(Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->key)
        node->left = insertBST(node->left, data);
    else if (data > node->key)
        node->right = insertBST(node->right, data);

    return node;
}

// 트리에서 노드를 삭제하는 함수
Node* deleteNode(Node* root, int data) {
    if (root == NULL)
        return root;

    if (data < root->key)
        root->left = deleteNode(root->left, data);
    else if (data > root->key)
        root->right = deleteNode(root->right, data);
    else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;

    // 노드의 높이 업데이트
    root->height = 1 + max(height(root->left), height(root->right));

    // 균형 인수 구하기
    int balance = getBalance(root);

    // 왼쪽-왼쪽 케이스
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // 왼쪽-오른쪽 케이스
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // 오른쪽-오른쪽 케이스
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // 오른쪽-왼쪽 케이스
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 트리에서 노드를 탐색하는 함수
Node* search(Node* root, int data, int* compareCount) {
    (*compareCount)++;
    if (root == NULL || root->key == data) {
        return root;
    }

    (*compareCount)++;
    if (data < root->key)
        return search(root->left, data, compareCount);
    return search(root->right, data, compareCount);
}

// 트리의 메모리를 해제하는 함수
void freeTree(Node* root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

void doAVLBatch(Node* root) {
    int A, B;
    int localCompareCount = 0, localSearchCount = 0;

    for (int i = 0; i < SIZE; i++) {
        A = rand() % 3;
        B = rand() % VALUE;

        if (A == 0) {
            root = insertAVL(root, B);
        } else if (A == 1) {
            root = deleteNode(root, B);
        } else {
            localSearchCount++;
            search(root, B, &localCompareCount);
        }
    }

    compareCount = localCompareCount;
    searchCount = localSearchCount;
}

void doBinaryBatch(Node* root) {
    int A, B;
    int localCompareCount = 0, localSearchCount = 0;

    for (int i = 0; i < SIZE; i++) {
        A = rand() % 3;
        B = rand() % VALUE;

        if (A == 0) {
            root = insertBST(root, B);
        } else if (A == 1) {
            root = deleteNode(root, B);
        } else {
            localSearchCount++;
            search(root, B, &localCompareCount);
        }
    }

    compareCount = localCompareCount;
    searchCount = localSearchCount;
}

int main(int argc, char *argv[]) {
    Node *root = NULL;
    srand(time(NULL));
    float allCount = 0.0;
    
    // AVL 트리에 대한 2000회 Batch 작업 수행
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);
    
    // AVL 트리 메모리 해제
    freeTree(root);
    root = NULL;
    compareCount = allCount = 0;
    
    // 이진 탐색 트리에 대한 Batch 작업 수행
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);
    
    freeTree(root);
    return 0;
}
