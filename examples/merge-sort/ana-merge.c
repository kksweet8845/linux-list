#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "common.h"
#include "list.h"
#include "merge-sort.h"

void analysis(int len, partPointer(fn))
{
    struct timespec cur, end;
    clock_gettime(CLOCK_REALTIME, &cur);
    merge_run(len, fn);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("%ld ", end.tv_nsec - cur.tv_nsec);
}


int main()
{
    for (uint16_t i = 256; i <= 2048; i = i + 128) {
        printf("%d ", i);
        analysis(i, &partition);
        analysis(i, &partition_first);
        analysis(i, &partition_rand);
        printf("\n");
    }
    return 0;
}