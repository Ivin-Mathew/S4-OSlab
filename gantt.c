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
    int done;
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
    int n=5, choice, time_quantum;
    Process processes[MAX_PROCESSES];

    /* printf("Enter the number of processes: ");
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
    } */

    //temporary hardcode
    processes[0].arrival_time=0;
    processes[0].burst_time=3;
    processes[0].priority=1;
    processes[0].id=1;
    processes[0].turnaround_time=0;
    processes[0].remaining_time=processes[0].burst_time;
    processes[0].waiting_time=0;
    processes[0].done=0;
    
    processes[1].arrival_time=2;
    processes[1].burst_time=6;
    processes[1].priority=3;
    processes[1].id=2;
    processes[1].turnaround_time=0;
    processes[1].remaining_time=processes[0].burst_time;
    processes[1].waiting_time=0;
    processes[1].done=0;


    processes[2].arrival_time=1;
    processes[2].burst_time=5;
    processes[2].priority=1;
    processes[2].id=3;
    processes[2].turnaround_time=0;
    processes[2].remaining_time=processes[0].burst_time;
    processes[2].waiting_time=0;
    processes[2].done=0;

    processes[3].arrival_time=5;
    processes[3].burst_time=5;
    processes[3].priority=5;
    processes[3].id=4;
    processes[3].turnaround_time=0;
    processes[3].remaining_time=processes[0].burst_time;
    processes[3].waiting_time=0;
    processes[3].done=0;

    processes[4].arrival_time=2;
    processes[4].burst_time=6;
    processes[4].priority=1;
    processes[4].id=5;
    processes[4].turnaround_time=0;
    processes[4].remaining_time=processes[0].burst_time;
    processes[4].waiting_time=0;
    processes[4].done=0;



    printf("Select the scheduling algorithm:\n");
    printf("1. FCFS (First Come First Serve)\n");
    printf("2. Round Robin\n");
    printf("3. SJF (Shortest Job First)\n");
    printf("4. Priority\n");
    printf("5. Exit\n");
    while (1)
    {
        printf("\n\nEnter your choice: ");
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
        processes[i].waiting_time=current_time-processes[i].arrival_time;
        current_time+=processes[i].burst_time;
    }


    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
    displayGanttChart(processes, n);
    table(processes,n);
    
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

    calculateWaitingTime(processes, n);
    calculateTurnaroundTime(processes, n);
    displayGanttChart(p, num);
    table(processes,n);
    
}

void SJF(Process processes[], int n)
{
    Process temp[10];
    int time=0;
    for(int i=0;i<n;i++){
        int index=-1;
        for(int j=0;j<n;j++){
            if(processes[j].done==1)
                continue;
            else{
                if(index==-1) index=j;
                if(processes[j].arrival_time<=time && processes[j].burst_time<=processes[index].burst_time){
                    index=j;
                }
            }
        }
        processes[index].done=1;
        time+=processes[index].burst_time;
        temp[i]=processes[index];
    }



    calculateWaitingTime(temp, n);
    calculateTurnaroundTime(temp, n);
    displayGanttChart(temp, n);
    table(temp,n);
    
}

void priority(Process processes[], int n)
{
    Process temp[10];
    int time=0;
    for(int i=0;i<n;i++)
        processes[i].done=0;


    for(int i=0;i<n;i++){
        int high=-1;
        for(int j=0;j<n;j++){
            if(processes[j].arrival_time<=time && processes[j].done==0){
                if(high==-1) high=j;
                else if(processes[j].priority>processes[high].priority)
                    high=j;
            }
        }
        processes[high].done=1;
        time+=processes[high].burst_time;
        temp[i]=processes[high];
    }

    calculateWaitingTime(temp, n);
    calculateTurnaroundTime(temp, n);
    displayGanttChart(temp, n);
    table(temp,n);
    
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
    int sum=0;
    for (int i = 1; i < n; i++)
    {
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