#include <stdio.h>
#include <stdbool.h>

#define P 5
#define R 3

int main(){
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    int avail[R] = {3, 3, 2};  // Available instances of resources

    int need[P][R];
    for(int i=0; i<P; i++){
        for(int j=0; j<R; j++){
            need[i][j]=max[i][j]-alloc[i][j];
        }
    }

    bool finish[P]={false};
    int safeSeq[P];
    int work[R];
    for(int i=0; i<R; i++){
        work[i]=avail[i];
    }

    int count =0;
    while(count<P){
        bool found = false;
        for(int p=0; p<P; p++){
            if(!finish[p]){
                bool canAllocate=true;
                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += alloc[p][j];  // Release resources
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }
    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) printf("%d ", safeSeq[i]);
    printf("\n");
    return 0;
}
