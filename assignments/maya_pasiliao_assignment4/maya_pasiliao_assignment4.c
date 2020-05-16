#include <stdio.h>
#include <stdlib.h>
int difference(int x, int y) {
    int z;
    z = x - y;

    if(z < 0)
        return -z;
    else
        return z;
}

int main() {
    int cylinders = 10000;
    int n = 1000;
    int fcfs_count = 0;
    int sstf_count = 0;
    int scan_count = 0;
    int cscan_count = 0;
    int look_count = 0;
    int x, start, i, j, pos, min, a[1000];

    printf("\nEnter initial position: ");
    scanf("%d", &start);

    for(i = 0; i < n; i++) {
        a[i] = rand() % 1000;
    }

    x = start;

    // FCFS
    for(i = 0; i < n; i++) {
        x -= a[i];
        if(x < 0) {
            x = -x;
        }

        fcfs_count += x;
        x = a[i];
    }

    // SSTF
    for(i = 0; i < n; i++) {
        min = difference(a[i], x);
        pos = i;

        for(j = i; j < n; j++) {
            if(min > difference(x, a[j])) {
                pos = j;
                min = difference(x, a[j]);
            }
        }

        sstf_count += difference(x, a[pos]);
        x = a[pos];
        a[pos] = a[i];
        a[i] = x;
    }

    // SCAN
    scan_count = 0;
    pos = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    for(i = 0; i < n; i++) {
        if(a[i] < start) {
            pos++;
        }
    }

    for(i = 0; i < pos; i++) {
        for(j = 0; j < pos - i - 1; j++) {
            if(a[j] < a[j + 1]) {
                x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    x = start;

    for(i = 0; i < pos; i++) {
        scan_count += difference(a[i], x);
        x = a[i];
    }

    scan_count += difference(x, 0);
    x = 0;

    for(i = pos; i < n; i++) {
        scan_count += difference(a[i], x);
        x = a[i];
    }

    // C-SCAN
    cscan_count = 0;
    pos = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < n - i - 1; j++) {
            if(a[j] > a[j + 1]) {
                x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    for(i = 0; i < n; i++) {
        if(a[i] < start) {
            pos++;
        }
    }

    x = start;
    for(i = pos; i < n; i++) {
        cscan_count += difference(x, a[i]);
        x = a[i];
    }

    cscan_count += difference(cylinders - 1, x);
    x = 0;
    for(i = 0; i < pos; i++) {
        cscan_count += difference(x, a[i]);
        x = a[i];
    }

    // LOOK
    look_count = 0;
    pos = 0;

    for(i = 0; i < n; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (a[i] < start) {
            pos++;
        }
    }

    for (i = 0; i < pos; i++) {
        for (j = 0; j < pos - i - 1; j++) {
            if (a[j] < a[j + 1]) {
                x = a[j];
                a[j] = a[j + 1];
                a[j + 1] = x;
            }
        }
    }

    x = start;
    for(i = 0; i < pos; i++) {
        look_count += difference(a[i], x);
        x = a[i];
    }

    for(i = pos; i < n; i++) {
        look_count += difference(a[i], x);
        x = a[i];
    }

    printf("\n ALGORITHM \t HEAD MOVEMENTS ");
    printf("\n FCFS \t\t %d", fcfs_count);
    printf("\n SSTF \t\t %d", sstf_count);
    printf("\n SCAN \t\t %d", scan_count);
    printf("\n C-SCAN \t %d", cscan_count);
    printf("\n LOOK \t\t %d", look_count);
}