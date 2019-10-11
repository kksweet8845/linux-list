#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../merge-sort.h"
#include "common.h"
#include "list.h"


#define MAXLEN 7

void list_malloc(struct list_head *list, size_t from, size_t to)
{
    size_t i;
    struct listitem *item = NULL;
    for (i = from; i <= to; i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = i;
        list_add_tail(&item->list, list);
    }
}

void list_malloc_rand(struct list_head *list, uint16_t *arr, uint16_t len)
{
    size_t i;
    struct listitem *item;
    for (i = 0; i < len; i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = arr[i];
        list_add_tail(&item->list, list);
    }
}

void show_list(struct list_head *list)
{
    struct listitem *item = NULL;
    list_for_each_entry (item, list, list) {
        printf("%d ", item->i);
    }
    printf("\n");
}

int main()
{
    struct list_head testlist1, left_head, right_head;
    INIT_LIST_HEAD(&testlist1);

    list_malloc(&testlist1, [ 63, 22 ]);
    show_list(&testlist1);
    partition_first(&left_head, &right_head, &testlist1);
    show_list(&left_head);
    show_list(&right_head);
    return 0;
}