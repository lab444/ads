#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

// Hash table structure
struct HashTable {
    int data;
    int status;  // 0: Empty, 1: Occupied, -1: Deleted
};

// Function to calculate the first hash index
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Function to calculate the second hash index for double hashing
int secondHashFunction(int key) {
    return 7 - (key % 7);  // A prime number less than TABLE_SIZE
}

// Function to insert data using Linear Probing
void linearProbingInsert(struct HashTable table[], int data) {
    int index = hashFunction(data);
    int i = index;

    while (table[i].status == 1) {
        i = (i + 1) % TABLE_SIZE;
    }

    table[i].data = data;
    table[i].status = 1;  // Mark as occupied
}

// Function to insert data using Quadratic Probing
void quadraticProbingInsert(struct HashTable table[], int data) {
    int index = hashFunction(data);
    int i = index;
    int count = 1;

    while (table[i].status == 1) {
        i = (index + count * count) % TABLE_SIZE;
        count++;
    }

    table[i].data = data;
    table[i].status = 1;  // Mark as occupied
}

// Function to insert data using Double Hashing
void doubleHashingInsert(struct HashTable table[], int data) {
    int index = hashFunction(data);
    int i = index;
    int step = secondHashFunction(data);

    while (table[i].status == 1) {
        i = (i + step) % TABLE_SIZE;
    }

    table[i].data = data;
    table[i].status = 1;  // Mark as occupied
}

// Function to print the hash table
void printHashTable(struct HashTable table[]) {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].status == 1) {
            printf("Index %d: %d\n", i, table[i].data);
        } else {
            printf("Index %d: Empty\n", i);
        }
    }
}

int main() {
    struct HashTable linearTable[TABLE_SIZE] = {{0, 0}};
    struct HashTable quadraticTable[TABLE_SIZE] = {{0, 0}};
    struct HashTable doubleHashTable[TABLE_SIZE] = {{0, 0}};

    int data[] = {19, 29, 33, 45, 56, 75, 89, 99, 62};

    printf("Inserting data using Linear Probing:\n");
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        linearProbingInsert(linearTable, data[i]);
    }
    printHashTable(linearTable);

    printf("\nInserting data using Quadratic Probing:\n");
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        quadraticProbingInsert(quadraticTable, data[i]);
    }
    printHashTable(quadraticTable);

    printf("\nInserting data using Double Hashing:\n");
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        doubleHashingInsert(doubleHashTable, data[i]);
    }
    printHashTable(doubleHashTable);

    return 0;
}
