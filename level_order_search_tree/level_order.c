#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

// ======== ROUND QUEUE============
#define MAX_QUEUE_SIZE 100
typedef TreeNode *element;
typedef struct {    //큐타입
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

// ERROR PRINT FUNCTION
void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// INITIALIZATION FUNCTION
void init_queue(QueueType *q)
{
    q->front = q->rear = 0;
}

// EMPTY STATE CHECK FUNCTION
int is_empty(QueueType *q)
{
    return (q->front == q->rear);
}

// FULL STATE CHECK FUNCTION
int is_full(QueueType *q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

// ENQUEUE FUNCTION
void enqueue(QueueType *q, element item)
{
    if (is_full(q))
        error("Queue is full");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
} 

// DEQUEUE FUNCTION
element dequeue(QueueType *q)
{
    if (is_empty(q))
        error("QUEUE is empty state");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void level_order(TreeNode *ptr)
{
    QueueType q;
    
    init_queue(&q); // init QUEUE

    if (ptr == NULL) return;
    enqueue(&q, ptr);
    while (!is_empty(&q)) {
        ptr = dequeue(&q);
        printf(" [%d] ", ptr->data);
        if (ptr->left)
            enqueue(&q, ptr->left);
        if (ptr->right)
            enqueue(&q, ptr->right);
    }
}

//      15
//  4       20
// 1      16  25

TreeNode n1 = {1, NULL, NULL};
TreeNode n2 = {4, &n1, NULL};
TreeNode n3 = {16, NULL, NULL};
TreeNode n4 = {25, NULL, NULL};
TreeNode n5 = {20, &n3, &n4};
TreeNode n6 = {15, &n2, &n5};
TreeNode *root = &n6;

int main(void)
{
    printf("level_order = ");
    level_order(root);
    printf("\n");
    return 0;
}
