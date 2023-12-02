#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int data);
void insertFront(Node** head, int data);
void insertEnd(Node** head, int data);
void insertAfter(Node* prevNode, int data);
void deleteFront(Node** head);
void deleteEnd(Node** head);
void deleteNode(Node** head, Node* delNode);
void displayList(Node* head);

int main() {
    Node* head = NULL;

    // Insert nodes into the doubly linked list
    insertFront(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);
    insertAfter(head->next, 4);

    printf("Original List: ");
    displayList(head);

    // Delete nodes from the doubly linked list
    deleteFront(&head);
    deleteEnd(&head);
    deleteNode(&head, head->next);

    printf("List after Deletions: ");
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
    newNode->prev = NULL;
    newNode->next = NULL;

    return newNode;
}

// Function to insert a node at the front of the doubly linked list
void insertFront(Node** head, int data) {
    Node* newNode = createNode(data);
    newNode->next = *head;

    if (*head != NULL) {
        (*head)->prev = newNode;
    }

    *head = newNode;
}

// Function to insert a node at the end of the doubly linked list
void insertEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    Node* last = *head;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (last->next != NULL) {
        last = last->next;
    }

    last->next = newNode;
    newNode->prev = last;
}

// Function to insert a node after a given node in the doubly linked list
void insertAfter(Node* prevNode, int data) {
    if (prevNode == NULL) {
        printf("Previous node cannot be NULL\n");
        return;
    }

    Node* newNode = createNode(data);

    newNode->next = prevNode->next;
    if (prevNode->next != NULL) {
        prevNode->next->prev = newNode;
    }

    prevNode->next = newNode;
    newNode->prev = prevNode;
}

// Function to delete the front node of the doubly linked list
void deleteFront(Node** head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    Node* temp = *head;
    *head = (*head)->next;

    if (*head != NULL) {
        (*head)->prev = NULL;
    }

    free(temp);
}

// Function to delete the end node of the doubly linked list
void deleteEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return;
    }

    Node* last = *head;

    while (last->next != NULL) {
        last = last->next;
    }

    if (last->prev != NULL) {
        last->prev->next = NULL;
    } else {
        *head = NULL;
    }

    free(last);
}

// Function to delete a given node from the doubly linked list
void deleteNode(Node** head, Node* delNode) {
    if (*head == NULL || delNode == NULL) {
        printf("List or node is empty. Cannot delete.\n");
        return;
    }

    if (*head == delNode) {
        *head = delNode->next;
    }

    if (delNode->next != NULL) {
        delNode->next->prev = delNode->prev;
    }

    if (delNode->prev != NULL) {
        delNode->prev->next = delNode->next;
    }

    free(delNode);
}

// Function to display the doubly linked list
void displayList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
