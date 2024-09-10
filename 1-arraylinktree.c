#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode{
    int data;
    struct TreeNode* left, * right;
} TreeNode;

void GenerateArrayTree(int* Tree){
    int list[] = {1, 2, 9, 3, 5, 10, 13, 4, 6, 7, 8, 11, 12, 14, 15};
    
    for (int i = 1; i <= 15; i++){
        Tree[i] = list[i-1];
    }

    for (int i = 1; i <= 15; i++){
        printf("%d ", Tree[i]);
    }
    printf("\n\n");
}

void ArrayPreOrder(int* Tree, int index){
    if (index <= 15 && Tree[index] != -1){
        printf("%d ", Tree[index]);
        ArrayPreOrder(Tree, index*2);
        ArrayPreOrder(Tree, index*2+1);
    }
}

void ArrayInOrder(int* Tree, int index){
    if (index <= 15 && Tree[index] != -1){
        ArrayInOrder(Tree, index*2);
        printf("%d ", Tree[index]);
        ArrayInOrder(Tree, index*2+1);
    }
}

void ArrayPostOrder(int* Tree, int index){
    if (index <= 15 && Tree[index] != -1){
        ArrayPostOrder(Tree, index*2);
        ArrayPostOrder(Tree, index*2+1);
        printf("%d ", Tree[index]);
    }
}

void ArrayOrders(int* Tree){
    ArrayPreOrder(Tree, 1);
    printf("\n");
    ArrayInOrder(Tree, 1);
    printf("\n");
    ArrayPostOrder(Tree, 1);
    printf("\n\n");
}

void placeNode(TreeNode* np, int direction, int data){
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0){
        np->left = newNode;
    } else if (direction == 1) {
        np->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* np) {
    if (np == NULL) return;
    placeNode(np, 0, 2);
    placeNode(np, 1, 9);
    placeNode(np->left, 0, 3);
    placeNode(np->left, 1, 5);
    placeNode(np->right, 0, 10);
    placeNode(np->right, 1, 13);
    placeNode(np->left->left, 0, 4);
    placeNode(np->left->left, 1, 6);
    placeNode(np->left->right, 0, 7);
    placeNode(np->left->right, 1, 8);
    placeNode(np->right->left, 0, 11);
    placeNode(np->right->left, 1, 12);
    placeNode(np->right->right, 0, 14);
    placeNode(np->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* np) {
    if (np != NULL) {
        printf("%d ", np->data);
        LinkPreOrder(np->left);
        LinkPreOrder(np->right);
    }
}

void LinkInOrder(TreeNode* np) {
    if (np != NULL) {
        LinkInOrder(np->left);
        printf("%d ", np->data);
        LinkInOrder(np->right);
    }
}

void LinkPostOrder(TreeNode* np) {
    if (np != NULL) {
        LinkPostOrder(np->left);
        LinkPostOrder(np->right);
        printf("%d ", np->data);
    }
}

void LinkOrders(TreeNode* np) {
    if (np == NULL) return;
    LinkPreOrder(np);
    printf("\n");
    LinkInOrder(np);
    printf("\n");
    LinkPostOrder(np);
    printf("\n");
}

int main(){
    int arr[15];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);
    
    ArrayOrders(arr);
    LinkOrders(root);


    return 0;
}
