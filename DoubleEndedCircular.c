#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 5

typedef struct {
    int items[MAX_SIZE];
    int front, rear;
} CDeque;

void initialize(CDeque* deque) {
    deque->front = -1;
    deque->rear = -1;
}

int isFull(CDeque* deque) {
    return (deque->front == 0 && deque->rear == MAX_SIZE - 1) || (deque->front == deque->rear + 1);
}

int isEmpty(CDeque* deque) {
    return deque->front == -1;
}

void insertFront(CDeque* deque, int value) {
    if (isFull(deque)) {
        printf("Queue is full. Cannot insert at the front.\n");
        return;
    }

    if (isEmpty(deque)) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->front == 0) {
        deque->front = MAX_SIZE - 1;
    } else {
        deque->front--;
    }

    deque->items[deque->front] = value;
    printf("Inserted %d at the front.\n", value);
}

void insertRear(CDeque* deque, int value) {
    if (isFull(deque)) {
        printf("Queue is full. Cannot insert at the rear.\n");
        return;
    }

    if (isEmpty(deque)) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->rear == MAX_SIZE - 1) {
        deque->rear = 0;
    } else {
        deque->rear++;
    }

    deque->items[deque->rear] = value;
    printf("Inserted %d at the rear.\n", value);
}

int deleteFront(CDeque* deque) {
    if (isEmpty(deque)) {
        printf("Queue is empty. Cannot delete from the front.\n");
        exit(EXIT_FAILURE);
    }

    int deletedValue = deque->items[deque->front];

    if (deque->front == deque->rear) {
        // Last element is being removed
        initialize(deque);
    } else if (deque->front == MAX_SIZE - 1) {
        deque->front = 0;
    } else {
        deque->front++;
    }

    printf("Deleted %d from the front.\n", deletedValue);
    return deletedValue;
}

int deleteRear(CDeque* deque) {
    if (isEmpty(deque)) {
        printf("Queue is empty. Cannot delete from the rear.\n");
        exit(EXIT_FAILURE);
    }

    int deletedValue = deque->items[deque->rear];

    if (deque->front == deque->rear) {
        // Last element is being removed
        initialize(deque);
    } else if (deque->rear == 0) {
        deque->rear = MAX_SIZE - 1;
    } else {
        deque->rear--;
    }

    printf("Deleted %d from the rear.\n", deletedValue);
    return deletedValue;
}

void display(CDeque* deque) {
    if (isEmpty(deque)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Circular Double Ended Queue: ");
    int i = deque->front;
    do {
        printf("%d ", deque->items[i]);
        if (i == deque->rear && i != deque->front) {
            break;
        }
        i = (i + 1) % MAX_SIZE;
    } while (i != (deque->rear + 1) % MAX_SIZE);
    printf("\n");
}

int main() {
    CDeque deque;
    initialize(&deque);

    insertRear(&deque, 10);
    insertFront(&deque, 20);
    insertRear(&deque, 30);
    display(&deque);

    deleteFront(&deque);
    display(&deque);

    insertFront(&deque, 40);
    insertRear(&deque, 50);
    display(&deque);

    deleteRear(&deque);
    display(&deque);

    return 0;
}
