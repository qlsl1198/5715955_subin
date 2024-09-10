#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 완전 이진 트리 노드 구조체 정의
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// 새 노드 생성 함수
TreeNode* createNode(int value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 완전 이진 트리에 노드 삽입 함수
void insertNode(TreeNode** root, int value) {
    if (*root == NULL) {
        *root = createNode(value);
        return;
    }

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = *root;

    while (front < rear) {
        TreeNode* node = queue[front++];
        if (node->left == NULL) {
            node->left = createNode(value);
            return;
        } else {
            queue[rear++] = node->left;
        }

        if (node->right == NULL) {
            node->right = createNode(value);
            return;
        } else {
            queue[rear++] = node->right;
        }
    }
}

// 전위 순회 함수 (루트 -> 왼쪽 -> 오른쪽)
void preorderTraversal(TreeNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// 중위 순회 함수 (왼쪽 -> 루트 -> 오른쪽)
void inorderTraversal(TreeNode* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// 후위 순회 함수 (왼쪽 -> 오른쪽 -> 루트)
void postorderTraversal(TreeNode* node) {
    if (node == NULL) return;
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->data);
}

// 레벨 순회 함수 (너비 우선 탐색)
void levelOrderTraversal(TreeNode* root) {
    if (root == NULL) return;

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* node = queue[front++];
        printf("%d ", node->data);

        if (node->left != NULL)
            queue[rear++] = node->left;
        if (node->right != NULL)
            queue[rear++] = node->right;
    }
}

// 트리의 높이를 계산하는 함수
int getHeight(TreeNode* node) {
    if (node == NULL)
        return 0;
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight) ? leftHeight + 1 : rightHeight + 1;
}

// 트리가 완전 이진 트리인지 확인하는 함수
int isCompleteBinaryTree(TreeNode* root) {
    if (root == NULL)
        return 1;

    TreeNode* queue[1000];
    int front = 0, rear = 0;
    int flag = 0;
    queue[rear++] = root;

    while (front < rear) {
        TreeNode* node = queue[front++];

        if (node->left) {
            if (flag)
                return 0;
            queue[rear++] = node->left;
        } else {
            flag = 1;
        }

        if (node->right) {
            if (flag)
                return 0;
            queue[rear++] = node->right;
        } else {
            flag = 1;
        }
    }
    return 1;
}

// 트리 메모리 해제 함수
void freeTree(TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// 트리의 모형을 출력하는 함수 (개선된 버전)
void printTree(TreeNode* root, int level) {
    if (root == NULL) return;

    printTree(root->right, level + 1);

    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%d\n", root->data);

    printTree(root->left, level + 1);
}

int main() {
    TreeNode* root = NULL;

    // 완전 이진 트리 생성
    for (int i = 1; i <= 10; i++) {
        insertNode(&root, i);
    }

    printf("완전 이진 트리 생성 완료\n\n");

    // 트리 순회 결과 출력
    printf("전위 순회 결과: ");
    preorderTraversal(root);
    printf("\n");

    printf("중위 순회 결과: ");
    inorderTraversal(root);
    printf("\n");

    printf("후위 순회 결과: ");
    postorderTraversal(root);
    printf("\n");

    printf("레벨 순회 결과: ");
    levelOrderTraversal(root);
    printf("\n\n");

    // 트리 정보 출력
    printf("트리의 높이: %d\n", getHeight(root));
    printf("완전 이진 트리 여부: %s\n", isCompleteBinaryTree(root) ? "예" : "아니오");

    // 트리 모형 출력 (개선된 버전)
    printf("\n트리 모형:\n");
    printTree(root, 0);

    // 메모리 해제
    freeTree(root);

    return 0;
}