#include <stdio.h>

// Structure to hold process details
struct process {
    int pid;            // Process ID
    int at;             // Arrival Time
    int bt;             // Burst Time
    int ct;             // Completion Time
    int tat;            // Turnaround Time
    int wt;             // Waiting Time
    int priority;       // Priority (lower number = higher priority)
    int remaining_time; // Time left to execute
    int completed;      // Flag to check if completed
};

// Function to sort processes by arrival time (and by priority if same AT)
void sortByArrivalAndPriority(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // First sort by arrival time, then by priority
            if (p[j].at > p[j + 1].at || 
               (p[j].at == p[j + 1].at && p[j].priority > p[j + 1].priority)) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

// Main scheduling function
void priorityScheduling(struct process p[], int n) {
    sortByArrivalAndPriority(p, n); // Sort before starting

    int time = 0, completed = 0;

    // Initialize process state
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].bt;
        p[i].completed = 0;
    }

    // Scheduler runs until all processes are complete
    while (completed < n) {
        int highestPriority = 9999;
        int currentProcess = -1;

        // Find the highest priority process that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && !p[i].completed && p[i].priority < highestPriority) {
                highestPriority = p[i].priority;
                currentProcess = i;
            }
        }

        if (currentProcess != -1) {
            // Execute the process for 1 unit of time
            p[currentProcess].remaining_time--;
            time++;

            // If process finishes
            if (p[currentProcess].remaining_time == 0) {
                p[currentProcess].ct = time;
                p[currentProcess].tat = p[currentProcess].ct - p[currentProcess].at;
                p[currentProcess].wt = p[currentProcess].tat - p[currentProcess].bt;
                p[currentProcess].completed = 1;
                completed++;

                // Print details for this process
                printf("\nProcess P%d", p[currentProcess].pid);
                printf(" | AT: %d", p[currentProcess].at);
                printf(" | BT: %d", p[currentProcess].bt);
                printf(" | Priority: %d", p[currentProcess].priority);
                printf(" | CT: %d", p[currentProcess].ct);
                printf(" | TAT: %d", p[currentProcess].tat);
                printf(" | WT: %d", p[currentProcess].wt);
            }
        } else {
            // No process available to run at this time
            time++;
        }
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("\nEnter Arrival Time, Burst Time, and Priority for Process %d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
    }

    // Run the priority preemptive scheduling
    priorityScheduling(p, n);

    return 0;
}
