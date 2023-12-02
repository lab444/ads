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
void merge(Student students[], int left, int mid, int right, int* swapCount);
void mergeSort(Student students[], int left, int right, int* swapCount);

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
    Student* studentsMergeSort = (Student*)malloc(n * sizeof(Student));
    memcpy(studentsHeapSort, students, n * sizeof(Student));
    memcpy(studentsMergeSort, students, n * sizeof(Student));

    // Initialize swap counts
    int swapCountHeapSort = 0;
    int swapCountMergeSort = 0;

    // Perform Heap Sort
    heapSort(studentsHeapSort, n, &swapCountHeapSort);

    // Perform Merge Sort
    mergeSort(studentsMergeSort, 0, n - 1, &swapCountMergeSort);

    // Display the sorted arrays and swap counts
    printf("\nHeap Sorted Students (by Roll Number):\n");
    displayStudents(studentsHeapSort, n);
    printf("Heap Sort Swap Count: %d\n", swapCountHeapSort);

    printf("\nMerge Sorted Students (by Roll Number):\n");
    displayStudents(studentsMergeSort, n);
    printf("Merge Sort Swap Count: %d\n", swapCountMergeSort);

    // Free allocated memory
    free(students);
    free(studentsHeapSort);
    free(studentsMergeSort);

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

// Function to perform Merge Sort on students based on roll number
void mergeSort(Student students[], int left, int right, int* swapCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort both halves
        mergeSort(students, left, mid, swapCount);
        mergeSort(students, mid + 1, right, swapCount);

        // Merge the sorted halves
        merge(students, left, mid, right, swapCount);
    }
}

// Function to merge two halves of students[]
void merge(Student students[], int left, int mid, int right, int* swapCount) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Student* L = (Student*)malloc(n1 * sizeof(Student));
    Student* R = (Student*)malloc(n2 * sizeof(Student));

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i] = students[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = students[mid + 1 + j];
    }

    // Merge the temporary arrays back into students[left..right]
    i = 0;   // Initial index of first subarray
    j = 0;   // Initial index of second subarray
    k = left;  // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i].student_roll_no <= R[j].student_roll_no) {
            students[k] = L[i];
            i++;
        } else {
            students[k] = R[j];
            j++;
        }
        k++;

        // Increment swap count
        (*swapCount)++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        students[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        students[k] = R[j];
        j++;
        k++;
    }

    // Free allocated memory
    free(L);
    free(R);
}
