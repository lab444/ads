#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Define a structure for the doubly linked list-based stack
typedef struct {
    Node* top;
} Stack;

// Function prototypes
Node* createNode(int data);
void push(Stack* stack, int data);
int pop(Stack* stack);
int isEmpty(Stack* stack);

int main() {
    Stack stack;
    stack.top = NULL;

    // Push elements onto the stack
    push(&stack, 1);
    push(&stack, 2);
    push(&stack, 3);

    printf("Stack after Push operations: ");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    return 0;
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

// Function to push an element onto the stack
void push(Stack* stack, int data) {
    Node* newNode = createNode(data);

    if (stack->top == NULL) {
        stack->top = newNode;
    } else {
        newNode->next = stack->top;
        stack->top->prev = newNode;
        stack->top = newNode;
    }
}

// Function to pop an element from the stack
int pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. Cannot pop.\n");
        exit(EXIT_FAILURE);
    }

    int poppedValue = stack->top->data;
    Node* temp = stack->top;

    if (stack->top->prev != NULL) {
        stack->top = stack->top->prev;
        stack->top->next = NULL;
    } else {
        stack->top = NULL;
    }

    free(temp);
    return poppedValue;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == NULL;
}
