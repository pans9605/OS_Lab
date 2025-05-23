#include <stdio.h>

int find(int frames[], int n, int page) {
    for (int i = 0; i < n; i++)
        if (frames[i] == page)
            return 1;
    return 0;
}

int findLRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int findOptimal(int frames[], int nf, int future[], int index, int np) {
    int farthest = -1, pos = -1;
    for (int i = 0; i < nf; i++) {
        int j;
        for (j = index; j < np; j++) {
            if (frames[i] == future[j]) {
                if (j > farthest) {
                    farthest = j;
                    pos = i;
                }
                break;
            }
        }
        if (j == np) return i;  // Not found in future
    }
    return pos == -1 ? 0 : pos;
}

void printFrames(int frames[], int f) {
    for (int i = 0; i < f; i++) {
        if (frames[i] == -1)
            printf(" - ");
        else
            printf("%2d ", frames[i]);
    }
}

void FIFO(int pages[], int n, int f) {
    printf("\n--- FIFO ---\n");
    int frames[10], front = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        printf("Page %2d: ", pages[i]);
        if (!find(frames, f, pages[i])) {
            frames[front] = pages[i];
            front = (front + 1) % f;
            faults++;
            printFrames(frames, f);
            printf("  [Page Fault]\n");
        } else {
            printFrames(frames, f);
            printf("  [No Fault]\n");
        }
    }
    printf("Total Page Faults (FIFO): %d\n", faults);
}

void LRU(int pages[], int n, int f) {
    printf("\n--- LRU ---\n");
    int frames[10], time[10], clk = 0, faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        printf("Page %2d: ", pages[i]);
        int found = 0;
        for (int j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                clk++;
                time[j] = clk;
                found = 1;
                break;
            }
        }

        if (!found) {
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1) pos = findLRU(time, f);
            clk++;
            frames[pos] = pages[i];
            time[pos] = clk;
            faults++;
            printFrames(frames, f);
            printf("  [Page Fault]\n");
        } else {
            printFrames(frames, f);
            printf("  [No Fault]\n");
        }
    }
    printf("Total Page Faults (LRU): %d\n", faults);
}

void Optimal(int pages[], int n, int f) {
    printf("\n--- Optimal ---\n");
    int frames[10], faults = 0;
    for (int i = 0; i < f; i++) frames[i] = -1;

    for (int i = 0; i < n; i++) {
        printf("Page %2d: ", pages[i]);
        if (!find(frames, f, pages[i])) {
            int pos = -1;
            for (int j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }
            if (pos == -1)
                pos = findOptimal(frames, f, pages, i + 1, n);

            frames[pos] = pages[i];
            faults++;
            printFrames(frames, f);
            printf("  [Page Fault]\n");
        } else {
            printFrames(frames, f);
            printf("  [No Fault]\n");
        }
    }
    printf("Total Page Faults (Optimal): %d\n", faults);
}

int main() {
    int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(pages) / sizeof(pages[0]);
    int f = 3;

    FIFO(pages, n, f);
    LRU(pages, n, f);
    Optimal(pages, n, f);

    return 0;
}
