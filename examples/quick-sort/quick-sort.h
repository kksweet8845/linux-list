#include <stdint.h>
#include "../include/list.h"
#include "../private/common.h"

void list_qsort(struct list_head *head);

int list_random_qsort(struct list_head *head, uint16_t k);

int quick_run(int);