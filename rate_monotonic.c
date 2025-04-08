#include <stdio.h>

#define MAX 10

struct Process {
    int id;
    int burst;
    int period;
    int remaining;
    int next_start;
};

// Function to calculate GCD
int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to calculate LCM
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}

int main() {
    int n, hyper_period = 1;
    struct Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter burst time and period for P%d: ", p[i].id);
        scanf("%d%d", &p[i].burst, &p[i].period);
        p[i].remaining = 0;
        p[i].next_start = 0;

        hyper_period = lcm(hyper_period, p[i].period); // Proper LCM
    }

    printf("\n--- Rate Monotonic Scheduling ---\n");

    for (int time = 0; time < hyper_period; time++) {
        // Release new instances
        for (int i = 0; i < n; i++) {
            if (time == p[i].next_start) {
                if (p[i].remaining > 0) {
                    printf("Time %d: P%d missed its deadline!\n", time, p[i].id);
                }
                p[i].remaining = p[i].burst;
                p[i].next_start += p[i].period;
            }
        }

        // Pick highest priority process (smallest period)
        int current = -1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0) {
                if (current == -1 || p[i].period < p[current].period)
                    current = i;
            }
        }

        if (current != -1) {
            printf("Time %d: P%d is running\n", time, p[current].id);
            p[current].remaining--;
        } else {
            printf("Time %d: CPU is idle\n", time);
        }
    }

    return 0;
}


