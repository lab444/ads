#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Student
typedef struct {
    char student_name[50];
    int student_roll_no;
    int total_marks;
} Student;

// Function prototypes
void displayStudents(Student students[], int n);
void heapify(Student students[], int n, int i, int* swapCount);
void heapSort(Student students[], int n, int* swapCount);
int partition(Student students[], int low, int high, int* swapCount);
void quickSort(Student students[], int low, int high, int* swapCount);

int main() {
    int n, i;

    // Input: Number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Allocate memory for array of students
    Student* students = (Student*)malloc(n * sizeof(Student));

    // Input: Student details
    for (i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].student_name);
        printf("Roll Number: ");
        scanf("%d", &students[i].student_roll_no);
        printf("Total Marks: ");
        scanf("%d", &students[i].total_marks);
    }

    // Copy the array for both sorting methods
    Student* studentsHeapSort = (Student*)malloc(n * sizeof(Student));
    Student* studentsQuickSort = (Student*)malloc(n * sizeof(Student));
    memcpy(studentsHeapSort, students, n * sizeof(Student));
    memcpy(studentsQuickSort, students, n * sizeof(Student));

    // Initialize swap counts
    int swapCountHeapSort = 0;
    int swapCountQuickSort = 0;

    // Perform Heap Sort
    heapSort(studentsHeapSort, n, &swapCountHeapSort);

    // Perform Quick Sort
    quickSort(studentsQuickSort, 0, n - 1, &swapCountQuickSort);

    // Display the sorted arrays and swap counts
    printf("\nHeap Sorted Students (by Roll Number):\n");
    displayStudents(studentsHeapSort, n);
    printf("Heap Sort Swap Count: %d\n", swapCountHeapSort);

    printf("\nQuick Sorted Students (by Roll Number):\n");
    displayStudents(studentsQuickSort, n);
    printf("Quick Sort Swap Count: %d\n", swapCountQuickSort);

    // Free allocated memory
    free(students);
    free(studentsHeapSort);
    free(studentsQuickSort);

    return 0;
}

// Function to display the details of students
void displayStudents(Student students[], int n) {
    printf("Roll No\tName\tTotal Marks\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\n", students[i].student_roll_no, students[i].student_name, students[i].total_marks);
    }
}

// Function to perform Heap Sort on students based on roll number
void heapSort(Student students[], int n, int* swapCount) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(students, n, i, swapCount);
    }

    // One by one extract an element from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to the end
        Student temp = students[0];
        students[0] = students[i];
        students[i] = temp;

        // call max heapify on the reduced heap
        heapify(students, i, 0, swapCount);
    }
}

// To heapify a subtree rooted with node i which is an index in students[]
void heapify(Student students[], int n, int i, int* swapCount) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // left = 2*i + 1
    int right = 2 * i + 2;  // right = 2*i + 2

    // If left child is larger than root
    if (left < n && students[left].student_roll_no > students[largest].student_roll_no) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && students[right].student_roll_no > students[largest].student_roll_no) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        // Swap students[i] and students[largest]
        Student temp = students[i];
        students[i] = students[largest];
        students[largest] = temp;

        // Recursive heapify the affected sub-tree
        heapify(students, n, largest, swapCount);

        // Increment swap count
        (*swapCount)++;
    }
}

// Function to perform Quick Sort on students based on roll number
void quickSort(Student students[], int low, int high, int* swapCount) {
    if (low < high) {
        // Partition the array
        int pi = partition(students, low, high, swapCount);

        // Recursively sort elements before and after the partition
        quickSort(students, low, pi - 1, swapCount);
        quickSort(students, pi + 1, high, swapCount);
    }
}

// Function to partition the array and return the pivot index
int partition(Student students[], int low, int high, int* swapCount) {
    Student pivot = students[high];  // Choose the rightmost element as pivot
    int i = low - 1;                 // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or equal to pivot
        if (students[j].student_roll_no <= pivot.student_roll_no) {
            i++;

            // Swap students[i] and students[j]
            Student temp = students[i];
            students[i] = students[j];
            students[j] = temp;

            // Increment swap count
            (*swapCount)++;
        }
    }

    // Swap students[i + 1] and students[high] (pivot)
    Student temp = students[i + 1];
    students[i + 1] = students[high];
    students[high] = temp;

    // Increment swap count
    (*swapCount)++;

    return i + 1;

