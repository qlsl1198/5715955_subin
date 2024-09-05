#include <stdio.h>
#include <stdlib.h>

// 이진 트리 노드 구조체 정의
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// 새 노드 생성 함수
struct TreeNode* createNode(int value) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(1);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 전위 순회 함수 (루트 -> 왼쪽 -> 오른쪽)
void preorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// 중위 순회 함수 (왼쪽 -> 루트 -> 오른쪽)
void inorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// 후위 순회 함수 (왼쪽 -> 오른쪽 -> 루트)
void postorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    postorderTraversal(node->left);
    postorderTraversal(node->right);
    printf("%d ", node->data);
}

// 조상 노드 출력 함수
void printAncestors(struct TreeNode* root, int target) {
    if (root == NULL) return;
    if (root->data == target) {
        printf("%d의 조상 노드: ", target);
        return;
    }
    printf("%d ", root->data);
    if (target < root->data)
        printAncestors(root->left, target);
    else
        printAncestors(root->right, target);
}

// 자식 노드 출력 함수
void printChildren(struct TreeNode* node) {
    if (node == NULL) return;
    printf("%d의 자식 노드: ", node->data);
    if (node->left)
        printf("왼쪽 자식 = %d ", node->left->data);
    if (node->right)
        printf("오른쪽 자식 = %d ", node->right->data);
    if (!node->left && !node->right)
        printf("자식 노드 없음");
    printf("\n");
}

// 형제 노드 출력 함수
void printSiblings(struct TreeNode* root, int target) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return;
    if ((root->left && root->left->data == target) || (root->right && root->right->data == target)) {
        printf("%d의 형제 노드: ", target);
        if (root->left && root->left->data != target)
            printf("왼쪽 형제 = %d ", root->left->data);
        if (root->right && root->right->data != target)
            printf("오른쪽 형제 = %d ", root->right->data);
        if ((root->left && root->left->data == target && root->right == NULL) ||
            (root->right && root->right->data == target && root->left == NULL))
            printf("형제 노드 없음");
        printf("\n");
        return;
    }
    printSiblings(root->left, target);
    printSiblings(root->right, target);
}

// 트리 메모리 해제 함수
void freeTree(struct TreeNode* node) {
    if (node == NULL) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    // 이진 트리 예시 생성
    struct TreeNode* root = NULL;
    root = createNode(8);
    if (root != NULL) {
        root->left = createNode(3);
        root->right = createNode(10);
        if (root->left != NULL) {
            root->left->left = createNode(1);
            root->left->right = createNode(6);
            if (root->left->right != NULL) {
                root->left->right->left = createNode(4);
                root->left->right->right = createNode(7);
            }
        }
        if (root->right != NULL) {
            root->right->right = createNode(14);
            if (root->right->right != NULL) {
                root->right->right->left = createNode(13);
            }
        }
    }

    // 트리 순회 결과 출력
    printf("전위 순회 결과 (루트 -> 왼쪽 -> 오른쪽): ");
    preorderTraversal(root);
    printf("\n");

    printf("중위 순회 결과 (왼쪽 -> 루트 -> 오른쪽): ");
    inorderTraversal(root);
    printf("\n");

    printf("후위 순회 결과 (왼쪽 -> 오른쪽 -> 루트): ");
    postorderTraversal(root);
    printf("\n\n");

    // 조상, 자식, 형제 노드 출력
    printAncestors(root, 4);
    printf("\n");
    printChildren(root);
    printChildren(root->left);
    printChildren(root->right);
    printSiblings(root, 3);
    printSiblings(root, 1);
    printSiblings(root, 13);

    // 메모리 해제
    freeTree(root);

    return 0;
}