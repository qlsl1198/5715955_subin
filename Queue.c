#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define MAX_QUEUE_SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct QueueNode {
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct {
    QueueNode* front, * rear;
} LinkedQueueType;

void init(LinkedQueueType* q) {
    q->front = q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
    return (q->front == NULL);
}

void enqueue(LinkedQueueType* q, element item) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    if (temp == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return;
    }
    temp->data = item;
    temp->link = NULL;
    if (is_empty(q)) {
        q->front = q->rear = temp;
    } else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(LinkedQueueType* q) {
    if (is_empty(q)) {
        fprintf(stderr, "Queue is empty\n");
        return NULL;
    }
    QueueNode* temp = q->front;
    element item = temp->data;
    q->front = q->front->link;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return item;
}

void level_order(TreeNode* ptr) {
    LinkedQueueType q;
    init(&q);
    if (ptr == NULL) return;
    enqueue(&q, ptr);
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf("[%d] ", ptr->data);
        if (ptr->left)
            enqueue(&q, ptr->left);
        if (ptr->right)
            enqueue(&q, ptr->right);
    }
}

int main() {
    TreeNode n1, n2, n3, n4, n5, n6;

    n1.data = 10, n1.left = &n2; n1.right = &n3;
	n2.data = 5, n2.left = &n4; n2.right = &n5;
	n3.data = 9, n3.left = NULL; n3.right = &n6;
	n4.data = 6, n4.left = NULL; n4.right = NULL;
	n5.data = 3, n5.left = NULL; n5.right = NULL;
	n6.data = 7, n6.left = NULL; n6.right = NULL;

    level_order(&n1);
    return 0;
}