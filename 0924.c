#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;

int sum_of_tree_nodes(TreeNode* root){
    int sum;

    if (root == NULL) return 0;

    sum = root->data + sum_of_tree_nodes(root->left) 
    + sum_of_tree_nodes(root->right); 
    return sum;

}

int get_node_count(TreeNode* root){
    int count;

    if (root == NULL) return 0;
    count = 1 + get_node_count(root->left)
            + get_node_count(root->right);

    return count;
}

int get_height(TreeNode* root){
    int height;

    if (root == NULL) return 0;
    height = 1 + (get_height(root->left) > get_height(root->right) ? get_height(root->left) : get_height(root->right));

    return height;
}

typedef struct QueueNode {
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct {
    QueueNode* front, * rear;
    int size;
} LinkedQueueType;

void init(LinkedQueueType* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

int is_empty(LinkedQueueType* q) {
    return (q->size == 0);
}

int size(LinkedQueueType* q) {
    return q->size;
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
    q->size++;
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
    q->size--;
    return item;
}

void level_order(TreeNode* ptr) {
    int nodes_sum = 0;

    LinkedQueueType q;
    int hight = 1;
    init(&q);
    if (ptr == NULL) return;
    enqueue(&q, ptr);
    int current_size = 1;
    int next_size = 0;
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf("%d[%d] ", ptr->data, hight);
        current_size--;
        if (ptr->left) {
            enqueue(&q, ptr->left);
            next_size++;
        }
        if (ptr->right) {
            enqueue(&q, ptr->right);
            next_size++;
        }
        if (current_size == 0) {
            printf("\n");
            hight++;
            current_size = next_size;
            next_size = 0;
        }
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

    printf("Total sum of tree node = %d\n\n", sum_of_tree_nodes(&n1));
    level_order(&n1);
    printf("\n");
    printf("Node Count = %d\n\n", get_node_count(&n1));
    printf("height = %d\n", get_height(&n1));
    return 0;
}