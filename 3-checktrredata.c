#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

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
        exit(1);
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

void placeNode(TreeNode* np, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
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

int GetHeightIterative(TreeNode* root) {
    if (root == NULL) return 0;

    LinkedQueueType queue;
    init(&queue);
    enqueue(&queue, root);
    
    int height = 0;

    while (!is_empty(&queue)) {
        int nodeCount = size(&queue);
        if (nodeCount == 0) return height;

        height++;

        while (nodeCount > 0) {
            TreeNode* node = dequeue(&queue);
            if (node->left)
                enqueue(&queue, node->left);
            if (node->right)
                enqueue(&queue, node->right);
            nodeCount--;
        }
    }

    return height;
}

int CountLeafNodesIterative(TreeNode* root) {
    if (root == NULL) return 0;

    LinkedQueueType queue;
    init(&queue);
    enqueue(&queue, root);
    
    int leafCount = 0;

    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);

        if (node->left == NULL && node->right == NULL) {
            leafCount++;
        }

        if (node->left)
            enqueue(&queue, node->left);
        if (node->right)
            enqueue(&queue, node->right);
    }

    return leafCount;
}

void GetSumOfNodes(TreeNode* np) {
    int sum = 0, nodeCount = 0;
    LinkedQueueType queue;
    init(&queue);
    enqueue(&queue, np);

    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);
        sum += node->data;
        nodeCount++;

        if (node->left)
            enqueue(&queue, node->left);
        if (node->right)
            enqueue(&queue, node->right);
    }

    printf("Sum of Nodes : %d\n", sum);
}

void GetNumberOfNodes(TreeNode* np) {
    int nodeCount = 0;
    LinkedQueueType queue;
    init(&queue);
    enqueue(&queue, np);

    while (!is_empty(&queue)) {
        TreeNode* node = dequeue(&queue);
        nodeCount++;

        if (node->left)
            enqueue(&queue, node->left);
        if (node->right)
            enqueue(&queue, node->right);
    }

    printf("Number of Nodes : %d\n", nodeCount);
}

void GetHeightOfTree(TreeNode* np) {
    int height = GetHeightIterative(np);
    printf("Height of Tree : %d\n", height);
}

void GetNumberOfLeafNodes(TreeNode* np) {
    int leafCount = CountLeafNodesIterative(np);
    printf("Number of Leaf Nodes : %d\n", leafCount);
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    if (root == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }
    
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);

    GetSumOfNodes(root);
    GetNumberOfNodes(root);
    GetHeightOfTree(root);
    GetNumberOfLeafNodes(root);

    return 0;
}