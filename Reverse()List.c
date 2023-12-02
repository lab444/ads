#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int data);
Node* insertNode(Node* head, int data);
void displayList(Node* head);
Node* reverseList(Node* head);

int main() {
    Node* head = NULL;

    // Insert nodes into the linked list
    head = insertNode(head, 1);
    head = insertNode(head, 2);
    head = insertNode(head, 3);
    head = insertNode(head, 4);
    head = insertNode(head, 5);

    printf("Original List: ");
    displayList(head);

    // Reverse the linked list
    head = reverseList(head);

    printf("Reversed List: ");
    displayList(head);

    // Free memory
    Node* current = head;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

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
    newNode->next = NULL;

    return newNode;
}

// Function to insert a node at the beginning of the list
Node* insertNode(Node* head, int data) {
    Node* newNode = createNode(data);
    newNode->next = head;
    return newNode;
}

// Function to display the linked list
void displayList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to reverse the linked list iteratively
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* current = head;
    Node* next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}
