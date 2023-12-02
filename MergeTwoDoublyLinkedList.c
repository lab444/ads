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
void insertEnd(Node** head, int data);
void displayList(Node* head);
Node* mergeSortedLists(Node* list1, Node* list2);

int main() {
    Node* list1 = NULL;
    Node* list2 = NULL;

    // Insert nodes into the first sorted doubly linked list
    insertEnd(&list1, 2);
    insertEnd(&list1, 4);
    insertEnd(&list1, 6);

    printf("List 1: ");
    displayList(list1);

    // Insert nodes into the second sorted doubly linked list
    insertEnd(&list2, 1);
    insertEnd(&list2, 3);
    insertEnd(&list2, 5);

    printf("List 2: ");
    displayList(list2);

    // Merge the two sorted lists
    Node* mergedList = mergeSortedLists(list1, list2);

    printf("Merged List: ");
    displayList(mergedList);

    // Free memory
    Node* current = mergedList;
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

// Function to display the doubly linked list
void displayList(Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to merge two sorted doubly linked lists
Node* mergeSortedLists(Node* list1, Node* list2) {
    Node* mergedList = NULL;
    Node* current = NULL;

    while (list1 != NULL && list2 != NULL) {
        if (list1->data < list2->data) {
            if (mergedList == NULL) {
                mergedList = current = list1;
            } else {
                current->next = list1;
                list1->prev = current;
                current = list1;
            }
            list1 = list1->next;
        } else {
            if (mergedList == NULL) {
                mergedList = current = list2;
            } else {
                current->next = list2;
                list2->prev = current;
                current = list2;
            }
            list2 = list2->next;
        }
    }

    // If any elements are left in list1
    while (list1 != NULL) {
        current->next = list1;
        list1->prev = current;
        current = list1;
        list1 = list1->next;
    }

    // If any elements are left in list2
    while (list2 != NULL) {
        current->next = list2;
        list2->prev = current;
        current = list2;
        list2 = list2->next;
    }

    return mergedList;
}
