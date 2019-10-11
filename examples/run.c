#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "merge-sort.h"
// #include "quick-sort.h"
// #include "insert-sort.h"

void analysis(int len)
{
    struct timespec cur, end;
    clock_gettime(CLOCK_REALTIME, &cur);
    merge_run(len);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("%ld ", end.tv_nsec - cur.tv_nsec);
}

int main(int argc, char **argv)
{
    int iter = atoi(argv[1]);
    // for(int i=64;i<=iter;i<<=1){
    //   // analysis(i, &partition);
    //   analysis(i, &partition_first);
    //   // analysis(i, &partition_rand);
    //   printf("\n");
    // }
    analysis(256);
    return 0;
}