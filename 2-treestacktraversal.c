#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* data;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

void initStack(Stack* s) {
    s->top = NULL;
}

int isEmpty(Stack* s) {
    return s->top == NULL;
}

void push(Stack* s, TreeNode* data) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
    printf("push(%d) ", data->data);
}

TreeNode* pop(Stack* s) {
    if (isEmpty(s)) return NULL;
    StackNode* temp = s->top;
    TreeNode* data = temp->data;
    s->top = s->top->next;
    free(temp);
    printf("pop(%d) ", data->data);
    return data;
}

void placeNode(TreeNode* np, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
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

void itr_preorder_traversar(TreeNode* root) {
    if (root == NULL) return;
    Stack s;
    initStack(&s);
    push(&s, root);

    while (!isEmpty(&s)) {
        TreeNode* node = pop(&s);
        printf("visit(%d)\n", node->data);
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
}

void itr_inorder_traversar(TreeNode* root) {
    if (root == NULL) return;
    Stack s;
    initStack(&s);
    TreeNode* current = root;

    while (current != NULL || !isEmpty(&s)) {
        while (current != NULL) {
            push(&s, current);
            current = current->left;
        }
        current = pop(&s);
        printf("visit(%d)\n", current->data);
        current = current->right;
    }
}

void itr_postorder_traversar(TreeNode* root) {
    if (root == NULL) return;
    Stack s1, s2;
    initStack(&s1);
    initStack(&s2);
    push(&s1, root);

    while (!isEmpty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);
        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    while (!isEmpty(&s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d)\n", node->data);
    }
}

void LinkPreOrder(TreeNode* np) {
    itr_preorder_traversar(np);
}

void LinkInOrder(TreeNode* np) {
    itr_inorder_traversar(np);
}

void LinkPostOrder(TreeNode* np) {
    itr_postorder_traversar(np);
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

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);
    
    LinkOrders(root);

    return 0;
}