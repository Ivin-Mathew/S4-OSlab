#include <stdio.h>

struct Process {
    int id, At, Bt, rBt, Ct, TAt, Wt, cat; // cat is temp arrival time
} P[20];

void main() {
    int i, n, initial = 0;
    int tq;
    float TotalTAt = 0, TotalWt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the arrival and burst time of processes\n");
    for (i = 0; i < n; i++) {
        P[i].id = i + 1;
        printf("Arrival and burst times of process P%d: ", i + 1);
        scanf("%d%d", &P[i].At, &P[i].Bt);
        if (i == 0 || P[i].At < initial)
            initial = P[i].At;

        P[i].rBt = P[i].Bt;
        P[i].cat = P[i].At;
        P[i].Wt = 0;
    }

    printf("Enter the time quantum: ");
    scanf("%d", &tq);

    int completed = 0, current_time = initial;
    printf("\nGantt Chart\n|");

    int time[100]; // to keep track of completion times
    int tc = 0;
    time[tc] = initial;

    while (completed != n) {
        int min = -1;
        for (i = 0; i < n; i++) { // find earliest process, i.e., with lowest arrival time
            if (P[i].cat <= current_time) {
                if (min == -1 && P[i].rBt != 0)
                    min = i;
                else if (P[i].rBt != 0 && P[i].cat < P[min].cat)
                    min = i;
            }
        }

        if (min == -1) { // No process is ready to execute, increment time
            current_time++;
            continue;
        }

        if (P[min].rBt <= tq) { // Process will complete in this cycle
            tc++;
            time[tc] = current_time + P[min].rBt;

            P[min].Wt = time[tc] - P[min].At - P[min].Bt; // Calculate waiting time
            TotalWt += P[min].Wt;

            P[min].TAt = time[tc] - P[min].At; // Calculate turnaround time
            TotalTAt += P[min].TAt;

            P[min].Ct = time[tc]; // Save completion time

            P[min].rBt = 0;
            completed++;
        } else { // Process will not complete in this cycle
            tc++;
            time[tc] = current_time + tq;
            P[min].rBt -= tq;
            P[min].cat = time[tc]; // Update current arrival time to next cycle start time
        }

        printf("  P%d   |", P[min].id);
        current_time = time[tc];
    }

    printf("\n");
    for (int i = 0; i <= tc; i++)
        printf("%d\t", time[i]);

    // Table printing logic
    printf("\nProcess\tArrive\tBurst\tComplete\tTT\tWT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\n", P[i].id, P[i].At, P[i].Bt, P[i].Ct, P[i].TAt, P[i].Wt);
    }

    printf("\nAverage turnaround time = %.2f\n", TotalTAt / n);
    printf("Average waiting time = %.2f\n",TotalWt / n);
}