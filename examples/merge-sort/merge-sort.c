#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#include "common.h"
#include "merge-sort.h"


void merge(struct list_head *left_head, struct list_head *right_head)
{
    struct listitem *leftitem, *rightitem, *lisafe, *risafe, *item;

    LIST_HEAD(merge_h);
    leftitem = list_first_entry(left_head, struct listitem, list);
    lisafe = list_entry(leftitem->list.next, struct listitem, list);
    rightitem = list_first_entry(right_head, struct listitem, list);
    risafe = list_entry(rightitem->list.next, struct listitem, list);
    for (; &leftitem->list != left_head && &rightitem->list != right_head;) {
        if (cmpint(&leftitem->i, &rightitem->i) < 0) {
            list_move_tail(&leftitem->list, &merge_h);
            leftitem = lisafe;
            lisafe = list_entry((lisafe->list.next), struct listitem, list);
        } else {
            list_move_tail(&rightitem->list, &merge_h);
            rightitem = risafe;
            risafe = list_entry((risafe->list.next), struct listitem, list);
        }
    }
    if (&leftitem->list == left_head) {
        list_splice_tail(right_head, &merge_h);
    }
    if (&rightitem->list == right_head) {
        list_splice_tail(left_head, &merge_h);
    }
    list_cut_position(left_head, &merge_h, merge_h.prev);
}

void partition(struct list_head *left_head,
               struct list_head *right_head,
               struct list_head *head)
{
    struct list_head *node = NULL;
    struct list_head *pivot = NULL;
    int len = 0, mean, i;
    list_for_each (node, head)
        len++;
    mean = len / 2;

    for (node = head->next, i = 1; i < mean; i++, node = node->next)
        ;
    list_cut_position(left_head, head, node);
    list_cut_position(right_head, head, head->prev);
}

void partition_first(struct list_head *left_head,
                     struct list_head *right_head,
                     struct list_head *head)
{
    struct list_head *node = NULL;
    int len = 0, mean, i;
    list_for_each (node, head)
        len++;
    if (len == 2) {
        list_cut_position(left_head, head, head->next);
        list_cut_position(right_head, head, head->prev);
        return;
    }

    list_cut_position(left_head, head, head->next->next);
    list_cut_position(right_head, head, head->prev);
}

void partition_rand(struct list_head *left_head,
                    struct list_head *right_head,
                    struct list_head *head)
{
    struct list_head *node = NULL;
    struct list_head *pivot = NULL;
    uint16_t rand;
    int len = 0, mean, i;
    list_for_each (node, head)
        len++;
    if (len > 2)
        rand = get_unsigned16() % (len - 2) + 1;
    else {
        list_cut_position(left_head, head, head->next);
        list_cut_position(right_head, head, head->prev);
        return;
    }
    for (node = head->next, i = 0; i < rand; i++, node = node->next)
        ;
    list_cut_position(left_head, head, node);
    list_cut_position(right_head, head, head->prev);
}

void merge_sort(struct list_head *head, partPointer(fn))
{
    struct list_head left_head, right_head, *node;
    struct listitem *item;
    int len = 0;
    list_for_each (node, head)
        len++;
    if (list_is_singular(head))
        return;
    (*fn)(&left_head, &right_head, head);
    merge_sort(&left_head, fn);
    merge_sort(&right_head, fn);
    merge(&left_head, &right_head);
    list_cut_position(head, &left_head, left_head.prev);
}


int merge_run(int len, partPointer(fn))
{
    struct list_head testlist;
    struct listitem *item, *is = NULL;
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
    merge_sort(&testlist, fn);
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
}
