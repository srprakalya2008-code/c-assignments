/* Q1 - Student B: experimental investigation.
 * Compares linear search vs binary search on sorted accession-number arrays
 * of sizes 1000, 10000 and 100000. Records comparisons for successful
 * searches (beginning / middle / end) and unsuccessful searches.
 * Compile: gcc -Wall -Wextra -O2 -o q1_experiments q1_experiments.c
 */
#include <stdio.h>
#include <stdlib.h>

static long linear_steps, binary_steps;

static int linear_search(const int a[], int n, int key)
{
    linear_steps = 0;
    for (int i = 0; i < n; i++) {
        linear_steps++;
        if (a[i] == key)
            return i;
    }
    return -1;
}

static int binary_search_c(const int a[], int n, int key)
{
    binary_steps = 0;
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        binary_steps++;
        if (a[mid] == key)
            return mid;
        else if (a[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int main(void)
{
    int sizes[] = {1000, 10000, 100000};
    printf("size,case,linear_cmps,binary_cmps\n");
    for (int s = 0; s < 3; s++) {
        int n = sizes[s];
        int *a = malloc((size_t)n * sizeof *a);
        if (!a) {
            printf("out of memory\n");
            return 1;
        }
        /* sorted accession numbers: 1000, 1001, ... */
        for (int i = 0; i < n; i++)
            a[i] = 1000 + i;
        int keys[4] = {a[0], a[n / 2], a[n - 1], 1000 + n + 500 /* missing */};
        const char *names[4] = {"first", "middle", "last", "missing"};
        for (int k = 0; k < 4; k++) {
            linear_search(a, n, keys[k]);
            binary_search_c(a, n, keys[k]);
            printf("%d,%s,%ld,%ld\n", n, names[k], linear_steps, binary_steps);
        }
        free(a);
    }
    return 0;
}
