#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 10

typedef struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process;

// Function prototypes
void FCFS(Process processes[], int n);
void roundRobin(Process processes[], int n, int time_quantum);
void SJF(Process processes[], int n);
void priority(Process processes[], int n);
void calculateTurnaroundTime(Process processes[], int n);
void calculateWaitingTime(Process processes[], int n);
void displayGanttChart(Process processes[], int n);
void table(Process p[], int n);

int main()
{
    int n, choice, time_quantum;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n > MAX_PROCESSES || n <= 0)
    {
        printf("Invalid number of processes.\n");
        return 1;
    }

    // Input process details
    for (int i = 0; i < n; i++)
    {
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &processes[i].priority);
        processes[i].id = i + 1;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time=0;
        processes[i].waiting_time=0;
printf("\n\n");
    }

    printf("Select the scheduling algorithm:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. Round Robin\n");
    printf("3. SJF (Shortest Job First)\n");
    printf("4. Priority\n");
    printf("5. Exit\n");
    while (1)
    {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            FCFS(processes, n);
            break;
        case 2:
            printf("Enter time quantum for Round Robin: ");
            scanf("%d", &time_quantum);
            roundRobin(processes, n, time_quantum);
            break;
        case 3:
            SJF(processes, n);
            break;
        case 4:
            priority(processes, n);
            break;
        case 5:
            exit(0);
            break;
        default:
            printf("Invalid choice.\n");
            return 1;
        }
    }

    return 0;
}

void FCFS(Process processes[], int n)
{
    // Sort processes based on arrival time
    int current_time = 0;

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(processes[j].arrival_time>processes[j+1].arrival_time){
                Process p=processes[j];
                processes[j]=processes[j+1];
                processes[j+1]=p;
            }
        }
    }

    for(int i=0;i<n;i++){
        processes[i].turnaround_time=current_time+processes[i].burst_time-processes[i].arrival_time;
        processes[i].waiting_time=current_time-processes[i].arrival_time;
        current_time+=processes[i].burst_time;
    }



    displayGanttChart(processes, n);
    table(processes,n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
}

void roundRobin(Process processes[], int n, int time_quantum)
{
    int remaining_processes = n;
    int current_time = 0;
    int completed[MAX_PROCESSES] = {0}; // Array to track completed processes
    Process p[100];
    int num=0;
    while (remaining_processes > 0)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
            p[num].id=processes[i].id;
            p[num].arrival_time=current_time;

                if (processes[i].remaining_time <= time_quantum)
                {
                    current_time += processes[i].remaining_time;
                    p[num].turnaround_time=processes[i].remaining_time;

                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    processes[i].remaining_time = 0;
                    completed[i] = 1;
                    remaining_processes--;


                    p[num].burst_time=p[num].turnaround_time;
                   
                }
                else
                {
                p[num].turnaround_time=time_quantum;
                p[num].burst_time=p[num].turnaround_time;
                    current_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                }


                num++;
            }
        }
    }


    displayGanttChart(p, num);
    table(processes,n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
}

void SJF(Process processes[], int n)
{
    // Sort processes based on burst time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burst_time > processes[j + 1].burst_time && processes[j].arrival_time >= processes[j+1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    for(int i = 0;i < n;i++){
   printf("%d ", processes[i].id);
    }

   
    displayGanttChart(processes, n);
    table(processes,n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
}

void priority(Process processes[], int n)
{
    // Sort processes based on priority
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority && processes[j].arrival_time >= processes[j+1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

   
    displayGanttChart(processes, n);
    table(processes,n);
    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
}

void calculateTurnaroundTime(Process processes[], int n)
{
int sum=0;
    for (int i = 0; i < n; i++)
    {
        processes[i].turnaround_time = processes[i].burst_time + processes[i].waiting_time;
        sum+=processes[i].turnaround_time;
    }
    float avg=(sum+0.0)/n;
    printf("\nAverage TT = %f\n",avg);
}

void calculateWaitingTime(Process processes[], int n)
{
    processes[0].waiting_time = 0;
    int sum=0;
    for (int i = 1; i < n; i++)
    {
        processes[i].waiting_time = processes[i - 1].burst_time + processes[i - 1].waiting_time - processes[i].arrival_time;
        sum+=processes[i].waiting_time;
    }
    float wt=(sum+0.0)/n;
    printf("\nAverage WT=%f\n",wt);
}

void displayGanttChart(Process p[], int n)
{
    int i,j;
    char topLeft[]="\u250c", topRight[]="\u2510";
    char bottomLeft[]="\u2514" , bottomRight[]="\u2518";
    char horizontal[]="\u2500", vertical[]="\u2502";
    char horiDown[]="\u252c" , horiUp[]="\u2534" ;

    printf("\n\n");
    printf("%s",topLeft );
    for(i=0;i<n;i++){
        for(j=0;j<p[i].burst_time;j++)
            printf("%s%s",horizontal,horizontal );
        if(i<n-1)
            printf("%s",horiDown);
        else
            printf("%s",topRight);
    }

    printf("\n%s",vertical);
    for(i=0;i<n;i++){
        for(j=0;j<p[i].burst_time-1;j++)
            printf(" ");
        printf("P%d",p[i].id);
        for(j=0;j<p[i].burst_time-1;j++)
            printf(" ");
        printf("%s",vertical);
    }


    printf("\n");
    printf("%s",bottomLeft);
    for(i=0;i<n;i++){
        for(j=0;j<p[i].burst_time;j++)
            printf("%s%s",horizontal,horizontal);
        if(i<n-1)
            printf("%s",horiUp);
        else
            printf("%s",bottomRight);
    }

    printf("\n%d",p[0].arrival_time);
    for(i=0;i<n;i++){
        for(j=0;j<p[i].burst_time;j++)
            printf("  ");
        if(p[i].turnaround_time + p[i].arrival_time>9)
            printf("\b");
        printf("%d",p[i].turnaround_time+p[i].arrival_time);
    }

    printf("\n\n\n");
}


void table(Process p[], int n){
    printf("PID\tPrio\tArr\tBurst\tTT\tWT \n ");
    for(int i=0;i<n;i++){
        printf("%d \t %d \t %d \t %d \t %d \t %d \n",p[i].id , p[i].priority , p[i].arrival_time, p[i].burst_time, p[i].turnaround_time, p[i].waiting_time);
    }
}






/* typedef struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
} Process; */