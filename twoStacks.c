#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

typedef struct {
    int items[MAX_SIZE];
    int top1;
    int top2;
} TwoStacks;

// Function prototypes
void initialize(TwoStacks *stacks);
void push(TwoStacks *stacks, int stackNumber, int value);
int pop(TwoStacks *stacks, int stackNumber);
int isStackFull(TwoStacks *stacks);
int isStackEmpty(TwoStacks *stacks, int stackNumber);
void displayStack(TwoStacks *stacks, int stackNumber);

int main() {
    TwoStacks stacks;
    initialize(&stacks);

    // Example operations
    push(&stacks, 1, 10); // Push 10 to stack 1
    push(&stacks, 2, 20); // Push 20 to stack 2
    push(&stacks, 1, 30); // Push 30 to stack 1

    displayStack(&stacks, 1); // Display stack 1
    displayStack(&stacks, 2); // Display stack 2

    printf("Popped from stack 1: %d\n", pop(&stacks, 1)); // Pop from stack 1
    printf("Popped from stack 2: %d\n", pop(&stacks, 2)); // Pop from stack 2

    displayStack(&stacks, 1); // Display stack 1
    displayStack(&stacks, 2); // Display stack 2

    return 0;
}

void initialize(TwoStacks *stacks) {
    stacks->top1 = -1;
    stacks->top2 = MAX_SIZE;
}

void push(TwoStacks *stacks, int stackNumber, int value) {
    if (isStackFull(stacks)) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    }

    if (stackNumber == 1) {
        stacks->items[++stacks->top1] = value;
    } else if (stackNumber == 2) {
        stacks->items[--stacks->top2] = value;
    }
}

int pop(TwoStacks *stacks, int stackNumber) {
    if (isStackEmpty(stacks, stackNumber)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    }

    int value;
    if (stackNumber == 1) {
        value = stacks->items[stacks->top1--];
    } else if (stackNumber == 2) {
        value = stacks->items[stacks->top2++];
    }

    return value;
}

int isStackFull(TwoStacks *stacks) {
    return stacks->top1 + 1 == stacks->top2;
}

int isStackEmpty(TwoStacks *stacks, int stackNumber) {
    return (stackNumber == 1 && stacks->top1 == -1) ||
           (stackNumber == 2 && stacks->top2 == MAX_SIZE);
}

void displayStack(TwoStacks *stacks, int stackNumber) {
    printf("Stack %d: ", stackNumber);
    if (stackNumber == 1) {
        for (int i = 0; i <= stacks->top1; ++i) {
            printf("%d ", stacks->items[i]);
        }
    } else if (stackNumber == 2) {
        for (int i = MAX_SIZE - 1; i >= stacks->top2; --i) {
            printf("%d ", stacks->items[i]);
        }
    }
    printf("\n");
}
