#include <stdio.h>
#include <stdlib.h>

// 트리 노드 구조체 정의
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

// 전위 순회 함수
void preorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    printf("%d ", node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// 중위 순회 함수
void inorderTraversal(struct TreeNode* node) {
    if (node == NULL) return;
    inorderTraversal(node->left);
    printf("%d ", node->data);
    inorderTraversal(node->right);
}

// 후위 순회 함수
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
        printf("%d ", node->left->data);
    if (node->right)
        printf("%d ", node->right->data);
    printf("\n");
}

// 형제 노드 출력 함수
void printSiblings(struct TreeNode* root, int target) {
    if (root == NULL || (root->left == NULL && root->right == NULL)) return;
    if ((root->left && root->left->data == target) || (root->right && root->right->data == target)) {
        printf("%d의 형제 노드: ", target);
        if (root->left && root->left->data != target)
            printf("%d ", root->left->data);
        if (root->right && root->right->data != target)
            printf("%d ", root->right->data);
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
    // 트리 예시 생성
    struct TreeNode* root = NULL;
    root = createNode(1);
    if (root != NULL) {
        root->left = createNode(2);
        root->right = createNode(3);
        if (root->left != NULL) {
            root->left->left = createNode(4);
            root->left->right = createNode(5);
        }
    }

    // 트리 순회 결과 출력
    printf("전위 순회 결과: ");
    preorderTraversal(root);
    printf("\n");

    printf("중위 순회 결과: ");
    inorderTraversal(root);
    printf("\n");

    printf("후위 순회 결과: ");
    postorderTraversal(root);
    printf("\n\n");

    // 조상, 자식, 형제 노드 출력
    printAncestors(root, 4);
    printf("\n");
    printChildren(root);
    printChildren(root->left);
    printSiblings(root, 2);
    printSiblings(root, 4);

    // 메모리 해제
    freeTree(root);

    return 0;
}