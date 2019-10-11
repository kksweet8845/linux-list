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
    struct listitem *item;
    for (i = from; i <= to; i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = i;
        list_add_tail(&item->list, list);
    }
}
void list_malloc_rand(struct list_head *list, int *arr, int len)
{
    int i;
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
    struct list_head testlist1, testlist2;
    size_t i;
    struct listitem *item = NULL, *is = NULL;
    INIT_LIST_HEAD(&testlist1);
    INIT_LIST_HEAD(&testlist2);
    int arr1[] = {0};
    int arr2[] = {1, 10, 99, 100};
    // list_malloc_rand(&testlist1, arr1, ARRAY_SIZE(arr1));
    show_list(&testlist1);
    // list_malloc_rand(&testlist2, arr2, ARRAY_SIZE(arr2));
    show_list(&testlist2);
    merge(&(testlist1), &(testlist2));
    i = 0;
    show_list(&testlist1);
    list_for_each_entry (item, &testlist1, list) {
        assert(item->i == (i + 1));
        i++;
    }
    // 0 + 7
    return 0;
}