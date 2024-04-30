#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES] = {false};

// Function to check if the system is in a safe state
bool isSafeState(int processes, int resources) {
    int work[MAX_RESOURCES];

    // Initialize work array
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    // Process i can complete
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

// Function to request resources by a process
bool requestResources(int process, int request[], int resources) {
    for (int i = 0; i < resources; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            return false;
        }
    }

    // Try allocating resources temporarily to see if the system remains in a safe state
    for (int i = 0; i < resources; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    if (!isSafeState(MAX_PROCESSES, MAX_RESOURCES)) {
        for (int i = 0; i < resources; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }

    return true;
}

// Function to find and print the safe sequence
void printSafeSequence(int processes, int resources) {
    int work[MAX_RESOURCES];

    // Initialize work array
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int count = 0;
    printf("Safe sequence: ");
    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canExecute = true;
                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        canExecute = false;
                        break;
                    }
                }
                if (canExecute) {
                    printf("P%d ", i);
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    count++;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nNo safe sequence exists.\n");
            return;
        }
    }
    printf("\n");
}

// Function to print the need matrix
void printNeedMatrix(int processes, int resources) {
    printf("Need Matrix:\n");
    for (int i = 0; i < processes; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resource types: ");
    scanf("%d", &resources);

    printf("Enter the available resources for each type:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter maximum demand matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
            need[i][j] = max[i][j];
        }
    }

    printf("Enter current allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
            need[i][j] -= allocation[i][j];
        }
    }

    printNeedMatrix(processes, resources);
    printf("\n");
    printSafeSequence(processes, resources);

    return 0;
}
