#include <stdio.h>
#include <stdbool.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time; 
    int priority;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};
int findHighestPriorityProcess(struct Process processes[], int n, int current_time) {
    int highest_priority = 9999;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
            if (processes[i].priority < highest_priority) {
                highest_priority = processes[i].priority;
                index = i;
            }
        }
    }

    return index;
}
void preemptivePriorityScheduling(struct Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < n) {
        int index = findHighestPriorityProcess(processes, n, current_time);
        if (index == -1) {
            current_time++;
        } else {
            processes[index].remaining_time--;
            current_time++;
            if (processes[index].remaining_time == 0) {
                completed_processes++;
                processes[index].completion_time = current_time;
                processes[index].turnaround_time = processes[index].completion_time - processes[index].arrival_time;
                processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
            }
        }
    }
}
void calculateAverages(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}
void displayProcesses(struct Process processes[], int n) {
    printf("PID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].priority, processes[i].completion_time, processes[i].waiting_time,
               processes[i].turnaround_time);
    }
}
int main() {
    int n = 5;
    struct Process processes[] = {
        {1, 0, 6, 2, 6, 0, 0, 0},
        {2, 1, 4, 1, 4, 0, 0, 0},
        {3, 2, 8, 3, 8, 0, 0, 0},
        {4, 3, 5, 4, 5, 0, 0, 0},
        {5, 4, 3, 5, 3, 0, 0, 0}
    };
    preemptivePriorityScheduling(processes, n);
    displayProcesses(processes, n);
    calculateAverages(processes, n);
    return 0;
}
