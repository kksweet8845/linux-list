#include <assert.h>
#include <stdlib.h>
#include "../include/list.h"

#include "../private/common.h"


void list_insert_sorted(struct listitem *entry, struct list_head *head)
{
    struct listitem *item = NULL;

    if (list_empty(head)) {
        list_add(&entry->list, head);
        return;
    }

    list_for_each_entry (item, head, list) {
        if (cmpint(&entry->i, &item->i) < 0) {
            list_add_tail(&entry->list, &item->list);
            return;
        }
    }

    list_add_tail(&entry->list, head);
}

void list_insertsort(struct list_head *head)
{
    struct list_head list_unsorted;
    struct listitem *item = NULL, *is = NULL;

    INIT_LIST_HEAD(&list_unsorted);
    list_splice_init(head, &list_unsorted);

    list_for_each_entry_safe (item, is, &list_unsorted, list) {
        list_del(&item->list);
        list_insert_sorted(item, head);
    }
}

int insert_run(int len)
{
    struct list_head testlist;
    struct listitem *item = NULL, *is = NULL;
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
    list_insertsort(&testlist);

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
