#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for Employee
typedef struct {
    char employee_name[50];
    int emp_no;
    float emp_salary;
} Employee;

// Function prototypes
void displayEmployees(Employee employees[], int n);
int partition(Employee employees[], int low, int high, int* swapCount);
void quickSort(Employee employees[], int low, int high, int* swapCount);
void merge(Employee employees[], int left, int mid, int right, int* swapCount);
void mergeSort(Employee employees[], int left, int right, int* swapCount);

int main() {
    int n, i;

    // Input: Number of employees
    printf("Enter the number of employees: ");
    scanf("%d", &n);

    // Allocate memory for array of employees
    Employee* employees = (Employee*)malloc(n * sizeof(Employee));

    // Input: Employee details
    for (i = 0; i < n; i++) {
        printf("\nEnter details for employee %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", employees[i].employee_name);
        printf("Employee Number: ");
        scanf("%d", &employees[i].emp_no);
        printf("Salary: ");
        scanf("%f", &employees[i].emp_salary);
    }

    // Copy the array for both sorting methods
    Employee* employeesQuickSort = (Employee*)malloc(n * sizeof(Employee));
    Employee* employeesMergeSort = (Employee*)malloc(n * sizeof(Employee));
    memcpy(employeesQuickSort, employees, n * sizeof(Employee));
    memcpy(employeesMergeSort, employees, n * sizeof(Employee));

    // Initialize swap counts
    int swapCountQuickSort = 0;
    int swapCountMergeSort = 0;

    // Perform Quick Sort
    quickSort(employeesQuickSort, 0, n - 1, &swapCountQuickSort);

    // Perform Merge Sort
    mergeSort(employeesMergeSort, 0, n - 1, &swapCountMergeSort);

    // Display the sorted arrays and swap counts
    printf("\nQuick Sorted Employees (by Employee Number):\n");
    displayEmployees(employeesQuickSort, n);
    printf("Quick Sort Swap Count: %d\n", swapCountQuickSort);

    printf("\nMerge Sorted Employees (by Employee Number):\n");
    displayEmployees(employeesMergeSort, n);
    printf("Merge Sort Swap Count: %d\n", swapCountMergeSort);

    // Free allocated memory
    free(employees);
    free(employeesQuickSort);
    free(employeesMergeSort);

    return 0;
}

// Function to display the details of employees
void displayEmployees(Employee employees[], int n) {
    printf("Emp No\tName\tSalary\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%.2f\n", employees[i].emp_no, employees[i].employee_name, employees[i].emp_salary);
    }
}

// Function to partition the array for Quick Sort
int partition(Employee employees[], int low, int high, int* swapCount) {
    Employee pivot = employees[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (employees[j].emp_no < pivot.emp_no) {
            i++;
            // Swap employees[i] and employees[j]
            Employee temp = employees[i];
            employees[i] = employees[j];
            employees[j] = temp;

            // Increment swap count
            (*swapCount)++;
        }
    }

    // Swap employees[i+1] and employees[high] (pivot)
    Employee temp = employees[i + 1];
    employees[i + 1] = employees[high];
    employees[high] = temp;

    // Increment swap count
    (*swapCount)++;

    return i + 1;
}

// Function to perform Quick Sort on employees based on employee number
void quickSort(Employee employees[], int low, int high, int* swapCount) {
    if (low < high) {
        // Find pivot element such that elements smaller than pivot are on the left,
        // and elements greater than pivot are on the right
        int pi = partition(employees, low, high, swapCount);

        // Recursively sort the subarrays
        quickSort(employees, low, pi - 1, swapCount);
        quickSort(employees, pi + 1, high, swapCount);
    }
}

// Function to perform Merge Sort on employees based on employee number
void mergeSort(Employee employees[], int left, int right, int* swapCount) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Recursively sort both halves
        mergeSort(employees, left, mid, swapCount);
        mergeSort(employees, mid + 1, right, swapCount);

        // Merge the sorted halves
        merge(employees, left, mid, right, swapCount);
    }
}

// Function to merge two halves of employees[]
void merge(Employee employees[], int left, int mid, int right, int* swapCount) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    Employee* L = (Employee*)malloc(n1 * sizeof(Employee));
    Employee* R = (Employee*)malloc(n2 * sizeof(Employee));

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++) {
        L[i] = employees[left + i];
    }
    for (j = 0; j < n2; j++) {
        R[j] = employees[mid + 1 + j];
    }

    // Merge the temporary arrays back into employees[left..right]
    i = 0;   // Initial index of first subarray
    j = 0;   // Initial index of second subarray
    k = left;  // Initial index of merged subarray

    while (i < n1 && j < n2) {
        if (L[i].emp_no <= R[j].emp_no) {
            employees[k] = L[i];
            i++;
        } else {
            employees[k] = R[j];
            j++;
        }
        k++;

        // Increment swap count
        (*swapCount)++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        employees[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        employees[k] = R[j];
        j++;
        k++;
    }

    // Free allocated memory
    free(L);
    free(R);
}
