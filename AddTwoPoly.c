#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the linked list
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

// Function prototypes
Node* createNode(int coefficient, int exponent);
void insertTerm(Node** poly, int coefficient, int exponent);
void displayPolynomial(Node* poly);
Node* addPolynomials(Node* poly1, Node* poly2);

int main() {
    // Polynomial 1: 3x^2 + 4x + 2
    Node* poly1 = NULL;
    insertTerm(&poly1, 3, 2);
    insertTerm(&poly1, 4, 1);
    insertTerm(&poly1, 2, 0);

    printf("Polynomial 1: ");
    displayPolynomial(poly1);

    // Polynomial 2: 5x^3 + 2x + 1
    Node* poly2 = NULL;
    insertTerm(&poly2, 5, 3);
    insertTerm(&poly2, 2, 1);
    insertTerm(&poly2, 1, 0);

    printf("Polynomial 2: ");
    displayPolynomial(poly2);

    // Addition of polynomials
    Node* sum = addPolynomials(poly1, poly2);

    printf("Sum of Polynomials: ");
    displayPolynomial(sum);

    // Free memory
    free(poly1);
    free(poly2);
    free(sum);

    return 0;
}

// Function to create a new node for a polynomial term
Node* createNode(int coefficient, int exponent) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    newNode->coefficient = coefficient;
    newNode->exponent = exponent;
    newNode->next = NULL;

    return newNode;
}

// Function to insert a term into a polynomial
void insertTerm(Node** poly, int coefficient, int exponent) {
    Node* newNode = createNode(coefficient, exponent);

    if (*poly == NULL) {
        *poly = newNode;
    } else {
        Node* current = *poly;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display a polynomial
void displayPolynomial(Node* poly) {
    while (poly != NULL) {
        printf("%dx^%d ", poly->coefficient, poly->exponent);
        if (poly->next != NULL) {
            printf("+ ");
        }
        poly = poly->next;
    }
    printf("\n");
}

// Function to add two polynomials
Node* addPolynomials(Node* poly1, Node* poly2) {
    Node* sum = NULL;
    Node* currentSum = NULL;

    while (poly1 != NULL || poly2 != NULL) {
        int coef1 = (poly1 != NULL) ? poly1->coefficient : 0;
        int exp1 = (poly1 != NULL) ? poly1->exponent : 0;

        int coef2 = (poly2 != NULL) ? poly2->coefficient : 0;
        int exp2 = (poly2 != NULL) ? poly2->exponent : 0;

        int sumCoef = coef1 + coef2;
        int sumExp = exp1;

        insertTerm(&sum, sumCoef, sumExp);

        if (poly1 != NULL) {
            poly1 = poly1->next;
        }

        if (poly2 != NULL) {
            poly2 = poly2->next;
        }
    }

    return sum;
}
