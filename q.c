#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef TreeNode* element;

typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}QueueType;

void error(char* message){
    fprintf(stderr, "%s", message);
}

int is_full(QueueType* q){
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(QueueType* q){
    return (q->front == q->rear);
}

void init(QueueType* q){
    q->front = q->rear = 0;
}

void enqueue(QueueType* q, element item){
    if (is_full(q)){
        error("Full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
    printf("enqueue[%d]", q->data[q->rear]->data);
}

element dequeue(QueueType* q){
    if (is_empty(q)){
        error("Empty\n");
        return NULL;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    printf("dequeue[%d]", q->data[q->front]->data);
    return q->data[q->front];
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

void itr_preorder_traversal(TreeNode* root) {
    if (root == NULL) return;
    QueueType q;
    init(&q);
    enqueue(&q, root);

    while (!is_empty(&q)) {
        TreeNode* node = dequeue(&q);
        printf("visit(%d)\n", node->data);
        if (node->right) enqueue(&q, node->right);
        if (node->left) enqueue(&q, node->left);
    }
}

int main(){
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);
    itr_preorder_traversal(root);

    return 0;
}