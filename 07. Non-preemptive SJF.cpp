#include <stdio.h>
struct Process {
    int pid;
    int arrival_time;
    int burst_time; 
    int waiting_time; 
    int turnaround_time;
    int completion_time;
};
void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time ||
                (processes[j].arrival_time == processes[j + 1].arrival_time &&
                 processes[j].burst_time > processes[j + 1].burst_time)) {
                struct Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}
void nonPreemptiveSJF(struct Process processes[], int n) {
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        int shortest_burst_index = i;
        for (int j = i + 1; j < n; j++) {
            if (processes[j].arrival_time <= current_time &&
                processes[j].burst_time < processes[shortest_burst_index].burst_time) {
                shortest_burst_index = j;
            }
        }
        struct Process temp = processes[i];
        processes[i] = processes[shortest_burst_index];
        processes[shortest_burst_index] = temp;

        if (processes[i].arrival_time > current_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        current_time = processes[i].completion_time;
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
    printf("PID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               processes[i].pid, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].waiting_time, processes[i].turnaround_time);
    }
}
int main() {
    int n = 5;
    struct Process processes[] = {
        {1, 0, 6, 0, 0, 0},
        {2, 1, 4, 0, 0, 0},
        {3, 2, 8, 0, 0, 0},
        {4, 3, 5, 0, 0, 0},
        {5, 4, 3, 0, 0, 0}
    };
    sortProcesses(processes, n);
    nonPreemptiveSJF(processes, n);
    displayProcesses(processes, n);
    calculateAverages(processes, n);
    return 0;
}
