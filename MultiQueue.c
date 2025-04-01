#include <stdio.h>

#define max 10

typedef struct {
    int pid, at, bt;
} Process;

void sortByArrival(Process p[], int n){

    for(int i=0; i<n-1; i++){
        for(int j=i+1; j<n; j++){
            if(p[i].at>p[j].at){
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void fcfs(Process p[], int n){
    int time=0;
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(int i =0; i<n; i++){
        if(time< p[i].at){
            time=p[i].at;
        }
        int ct = time+ p[i].bt;
        int tat = ct-p[i].at;
        int wt = tat - p[i].bt;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, ct, tat, wt);
        time = ct;
    }
}

int main() {
    int n, sys_count = 0, user_count = 0;
    Process sys_queue[max], user_queue[max];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        int type;
        printf("Enter PID, Arrival Time, Burst Time, Type (0=System, 1=User): ");
        scanf("%d %d %d %d", &p.pid, &p.at, &p.bt, &type);

        if (type == 0)
            sys_queue[sys_count++] = p;
        else
            user_queue[user_count++] = p;
    }

    // Sort both queues by arrival time
    sortByArrival(sys_queue, sys_count);
    sortByArrival(user_queue, user_count);

    // Execute system processes first
    printf("\nSystem Processes (Higher Priority)\n");
    fcfs(sys_queue, sys_count);

    // Execute user processes next
    printf("\nUser Processes (Lower Priority)\n");
    fcfs(user_queue, user_count);

    return 0;
}


