#include <stdint.h>
#include "common.h"
#include "list.h"

#define partPointer(fn)                                                     \
    void (*fn)(struct list_head * left_head, struct list_head * right_head, \
               struct list_head * head)

void merge(struct list_head *left_head, struct list_head *right_head);

void partition(struct list_head *left_head,
               struct list_head *right_head,
               struct list_head *head);

void partition_first(struct list_head *left_head,
                     struct list_head *right,
                     struct list_head *head);

void partition_rand(struct list_head *left_head,
                    struct list_head *right,
                    struct list_head *head);
void merge_sort(struct list_head *head, partPointer(fn));

int merge_run(int, partPointer(fn));