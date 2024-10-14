#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    bool leftThread;
    bool rightThread;
} ThreadNode;

TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL) return createNode(data);
    
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    
    return root;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert(root, inputData[i]);
    }
    return root;
}

void BinaryTreeInorder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInorder(root->left);
        printf("%d ", root->data);
        BinaryTreeInorder(root->right);
    }
}

ThreadNode* createThreadNode(int data) {
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->leftThread = true;
    newNode->rightThread = true;
    return newNode;
}

ThreadNode* insertThread(ThreadNode* root, int data) {
    ThreadNode* ptr = root;
    ThreadNode* par = NULL;
    while (ptr != NULL) {
        if (data == ptr->data) {
            return root;
        }
        par = ptr;
        if (data < ptr->data) {
            if (ptr->leftThread == false)
                ptr = ptr->left;
            else
                break;
        }
        else {
            if (ptr->rightThread == false)
                ptr = ptr->right;
            else
                break;
        }
    }

    ThreadNode* tmp = createThreadNode(data);
    if (par == NULL) {
        root = tmp;
        tmp->leftThread = tmp->rightThread = false;
    }
    else if (data < par->data) {
        tmp->left = par->left;
        tmp->right = par;
        par->leftThread = false;
        par->left = tmp;
    }
    else {
        tmp->left = par;
        tmp->right = par->right;
        par->rightThread = false;
        par->right = tmp;
    }

    return root;
}

ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insertThread(root, inputData[i]);
    }
    return root;
}

ThreadNode* inorderSuccessor(ThreadNode* ptr) {
    if (ptr->rightThread == true)
        return ptr->right;
    ptr = ptr->right;
    while (ptr->leftThread == false)
        ptr = ptr->left;
    return ptr;
}

void ThreadTreeInOrder(ThreadNode* root) {
    if (root == NULL) return;

    ThreadNode* ptr = root;
    while (ptr->leftThread == false)
        ptr = ptr->left;
    
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = inorderSuccessor(ptr);
    }
 }

void freeBinaryTree(TreeNode* root) {
    if (root != NULL) {
        freeBinaryTree(root->left);
        freeBinaryTree(root->right);
        free(root);
    }
}

void freeThreadTree(ThreadNode* root) {
    if (root == NULL) return;
    if (!root->leftThread) freeThreadTree(root->left);
    if (!root->rightThread) freeThreadTree(root->right);
    free(root);
}

int main() {
    int inputData[] = {4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11};
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
     printf("Binary Tree Inorder: ");
    BinaryTreeInorder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread Tree Inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    freeBinaryTree(root);
    freeThreadTree(troot);

    return 0;
}
