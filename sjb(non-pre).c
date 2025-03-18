#include <stdio.h>

struct Process {
    int pid, burst_time, arrival_time, completion_time, waiting_time, turnaround_time;
};

void sjfNonPreemptive(struct Process proc[], int n) {
    int time = 0, total_wt = 0, total_tat = 0;

    // Sort processes by burst time (Shortest Job First)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].arrival_time > proc[j].arrival_time ||
                (proc[i].arrival_time == proc[j].arrival_time && proc[i].burst_time > proc[j].burst_time)) {
                struct Process temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }

    // Gantt chart display
    printf("Gantt Chart: |");
    for (int i = 0; i < n; i++) {
        proc[i].waiting_time = (i == 0) ? 0 : proc[i-1].completion_time - proc[i].arrival_time;
        proc[i].waiting_time = (proc[i].waiting_time < 0) ? 0 : proc[i].waiting_time;
        proc[i].turnaround_time = proc[i].waiting_time + proc[i].burst_time;
        proc[i].completion_time = time + proc[i].burst_time;
        time = proc[i].completion_time;

        printf(" P%d |", proc[i].pid);
        total_wt += proc[i].waiting_time;
        total_tat += proc[i].turnaround_time;
    }

    // Gantt chart timeline
    printf("\n0");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < proc[i].burst_time; j++) printf("----");
    }
    printf("\n");

    // Average waiting and turnaround times
    printf("\nAvg Waiting Time: %.2f\n", (float)total_wt / n);
    printf("Avg Turnaround Time: %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];
    for (int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", proc[i].pid);
        scanf("%d %d", &proc[i].arrival_time, &proc[i].burst_time);
    }

    sjfNonPreemptive(proc, n);
    return 0;
}
