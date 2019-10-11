#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"

#include "../private/common.h"
#include "quick-sort.h"



void list_qsort(struct list_head *head)
{
    struct list_head list_less, list_greater;
    struct listitem *pivot;
    struct listitem *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, struct listitem, list);
    list_del(&pivot->list);

    list_for_each_entry_safe (item, is, head, list) {
        if (cmpint(&item->i, &pivot->i) < 0)
            list_move_tail(&item->list, &list_less);
        else
            list_move(&item->list, &list_greater);
    }

    list_qsort(&list_less);
    list_qsort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

int list_random_qsort(struct list_head *head, uint16_t k)
{
    struct list_head list_less, list_greater;
    struct listitem *pivot;
    struct listitem *item = NULL, *is = NULL;

    if (list_empty(head) || list_is_singular(head))
        return -1;

    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    pivot = list_first_entry(head, struct listitem, list);
    list_del(&pivot->list);

    uint16_t less_num = 0;
    list_for_each_entry_safe (item, is, head, list) {
        if (cmpint(&item->i, &pivot->i) < 0) {
            list_move_tail(&item->list, &list_less);
            less_num++;
        } else
            list_move(&item->list, &list_greater);
    }
    if (less_num + 1 == k)
        return pivot->i;
    else if (less_num + 1 > k)
        return list_random_qsort(&list_less, k);
    else
        return list_random_qsort(&list_greater, k - less_num - 1);
}

int quick_run(int len)
{
    struct list_head testlist;
    struct listitem *item, *is = NULL;
    uint16_t test_ans = 35;
    size_t i;

    static uint16_t *values;
    values = malloc(sizeof(uint16_t) * len);
    random_shuffle_array(values, (uint16_t) len);

    INIT_LIST_HEAD(&testlist);

    assert(list_empty(&testlist));

    for (i = 0; i < len; i++) {
        item = (struct listitem *) malloc(sizeof(*item));
        assert(item);
        item->i = values[i];
        list_add_tail(&item->list, &testlist);
    }

    assert(!list_empty(&testlist));

    qsort(values, len, sizeof(values[0]), cmpint);
    list_qsort(&testlist);
    // find k smallest element
    // uint16_t ans = list_random_qsort(&testlist, test_ans);
    i = 0;
    list_for_each_entry_safe (item, is, &testlist, list) {
        assert(item->i == values[i]);
        list_del(&item->list);
        free(item);
        i++;
    }

    assert(i == len);
    assert(list_empty(&testlist));
    free(values);
    return 0;
}
