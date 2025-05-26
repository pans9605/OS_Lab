#include <stdio.h>

struct Process {
    int id, at, bt, rt, ct, tat, wt, st;
};

void preemptiveSJF(struct Process p[], int n) {
    int complete = 0, time = 0, shortest = -1, min_rt = 1e9;
    int gantt[1000], gi = 0;

    for (int i = 0; i < n; i++) p[i].rt = p[i].bt;

    while (complete < n) {
        shortest = -1;
        min_rt = 1e9;

        // Select process with smallest remaining time among those that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= time && p[i].rt > 0 && p[i].rt < min_rt) {
                min_rt = p[i].rt;
                shortest = i;
            }
        }

        if (shortest == -1) {
            gantt[gi++] = -1; // CPU idle
            time++;
            continue;
        }

        if (p[shortest].rt == p[shortest].bt)
            p[shortest].st = time; // response time start

        gantt[gi++] = p[shortest].id;
        p[shortest].rt--;
        time++;

        if (p[shortest].rt == 0) {
            p[shortest].ct = time;
            p[shortest].tat = p[shortest].ct - p[shortest].at;
            p[shortest].wt = p[shortest].tat - p[shortest].bt;
            complete++;
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart:\n|");
    for (int i = 0; i < gi; i++)
        if (i == 0 || gantt[i] != gantt[i - 1])
            gantt[i] == -1 ? printf(" IDLE |") : printf(" P%d |", gantt[i]);

    printf("\n0");
    for (int i = 0, t = 0; i < gi; i++) {
        if (i == 0 || gantt[i] != gantt[i - 1]) printf("   %d", t);
        t++;
    }
    printf("   %d\n", time);
}

void printTable(struct Process p[], int n) {
    printf("\nID | AT | BT | CT | TAT | WT | RT\n");
    for (int i = 0; i < n; i++) {
        int rt = p[i].st - p[i].at;
        printf(" %d | %2d | %2d | %2d |  %2d | %2d | %2d\n",
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, rt);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter Burst Time and Arrival Time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].bt, &p[i].at);
    }

    preemptiveSJF(p, n);
    printTable(p, n);
    return 0;
}
