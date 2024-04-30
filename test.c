#include <stdio.h>

// Function prototypes
void fcfs(int n, int burst_time[], int arrival_time[]);
void round_robin(int n, int burst_time[], int arrival_time[], int quantum);
void sjf(int n, int burst_time[], int arrival_time[]);
void priorityq(int n, int burst_time[], int arrival_time[], int priority[]);

int main() {
    int choice, n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burst_time[n], arrival_time[n], priority[n];

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
    }

    printf("Enter arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
    }

    printf("Enter priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &priority[i]);
    }

    printf("Enter time quantum for Round Robin: ");
    scanf("%d", &quantum);

    printf("\nChoose scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. Round Robin\n");
    printf("3. SJF\n");
    printf("4. Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            fcfs(n, burst_time, arrival_time);
            break;
        case 2:
            round_robin(n, burst_time, arrival_time, quantum);
            break;
        case 3:
            sjf(n, burst_time, arrival_time);
            break;
        case 4:
            priorityq(n, burst_time, arrival_time, priority);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

void fcfs(int n, int burst_time[], int arrival_time[]) {
    // Implement FCFS scheduling algorithm here
    int waiting_time[n], turnaround_time[n];
    float total_waiting_time = 0, total_turnaround_time = 0;

    waiting_time[0] = 0; // First process has 0 waiting time
    turnaround_time[0] = burst_time[0]; // Turnaround time for first process is its burst time

    for (int i = 1; i < n; i++) {
        waiting_time[i] = turnaround_time[i - 1];
        turnaround_time[i] = waiting_time[i] + burst_time[i];
    }

    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void round_robin(int n, int burst_time[], int arrival_time[], int quantum) {
    // Implement Round Robin scheduling algorithm here
    int remaining_time[n], waiting_time[n], turnaround_time[n];
    int time = 0, remaining_processes = n;
    float total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = 0; // There are still remaining processes
                if (remaining_time[i] > quantum) {
                    time += quantum;
                    remaining_time[i] -= quantum;
                } else {
                    time += remaining_time[i];
                    waiting_time[i] = time - burst_time[i] - arrival_time[i];
                    remaining_time[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = burst_time[i] + waiting_time[i];
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);
}

void sjf(int n, int burst_time[], int arrival_time[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int min, min_index;
    int time = 0;
    int completed = 0;

    while (completed != n) {
        min = 99999; // Initialize min with a large value
        min_index = -1;
        
        // Finding the process with the minimum remaining time at current time
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] < min && remaining_time[i] > 0) {
                min = remaining_time[i];
                min_index = i;
            }
        }

        if (min_index == -1) {
            time++; // If no process is available, move to the next time unit
            continue;
        }

        // Execute the chosen process for one time unit
        remaining_time[min_index]--;
        
        // If the process is completed
        if (remaining_time[min_index] == 0) {
            completed++;
            completion_time[min_index] = time + 1;
            turnaround_time[min_index] = completion_time[min_index] - arrival_time[min_index];
            waiting_time[min_index] = turnaround_time[min_index] - burst_time[min_index];
            total_waiting_time += waiting_time[min_index];
            total_turnaround_time += turnaround_time[min_index];
        }
        time++; // Move to the next time unit
    }

    // Print the results
    printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

void priority(int n, int burst_time[], int arrival_time[], int priority[]) {
    int waiting_time[n], turnaround_time[n], completion_time[n];
    int total_waiting_time = 0, total_turnaround_time = 0;

    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = burst_time[i];
    }

    int time = 0;
    int completed = 0;

    while (completed != n) {
        int highest_priority = -1;
        int highest_priority_index = -1;

        // Find the process with the highest priority among arrived processes
        for (int i = 0; i < n; i++) {
            if (arrival_time[i] <= time && remaining_time[i] > 0 && priority[i] > highest_priority) {
                highest_priority = priority[i];
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            time++; // If no process is available, move to the next time unit
            continue;
        }

        // Execute the process with the highest priority for one time unit
        remaining_time[highest_priority_index]--;

        // If the process is completed
        if (remaining_time[highest_priority_index] == 0) {
            completed++;
            completion_time[highest_priority_index] = time + 1;
            turnaround_time[highest_priority_index] = completion_time[highest_priority_index] - arrival_time[highest_priority_index];
            waiting_time[highest_priority_index] = turnaround_time[highest_priority_index] - burst_time[highest_priority_index];
            total_waiting_time += waiting_time[highest_priority_index];
            total_turnaround_time += turnaround_time[highest_priority_index];
        }
        time++; // Move to the next time unit
    }

    // Print the results
    printf("\nProcess\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", i + 1, burst_time[i], arrival_time[i], priority[i], waiting_time[i], turnaround_time[i]);
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}
