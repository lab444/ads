#include <stdio.h>
#include <stdlib.h>

// Simple stack structure
typedef struct
{
    int items[100];
    int top;
} Stack;

// Function to initialize the stack
void initialize(Stack *stack)
{
    stack->top = -1;
}

// Function to push an item onto the stack
void push(Stack *stack, int value)
{
    stack->items[++stack->top] = value;
}

// Function to pop an item from the stack
int pop(Stack *stack)
{
    return stack->items[stack->top--];
}

// Function to check if the stack is empty
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

// Function to calculate factorial using a stack
unsigned long long factorial(int n)
{
    Stack stack;
    initialize(&stack);
    unsigned long long result = 1;

    for (int i = 1; i <= n; ++i)
    {
        push(&stack, i);
    }

    while (!isEmpty(&stack))
    {
        result *= pop(&stack);
    }

    return result;
}

// Function to generate Fibonacci series using a stack
void generateFibonacci(int n)
{
    Stack stack;
    initialize(&stack);
    int a = 0, b = 1;

    for (int i = 0; i < n; ++i)
    {
        printf("%d ", a);
        push(&stack, a);
        int next = a + b;
        a = b;
        b = next;
    }

    printf("\n");
}

int main()
{
    int num;

    // Calculate factorial
    printf("Enter a number to calculate its factorial: ");
    scanf("%d", &num);
    printf("Factorial of %d is %llu\n", num, factorial(num));

    // Generate Fibonacci series
    printf("Enter the number of terms in Fibonacci series: ");
    scanf("%d", &num);
    printf("Fibonacci Series: ");
    generateFibonacci(num);

    return 0;
}
