#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "../private/common.h"

static uint16_t values[256];

void max_heapify(uint16_t **arr, uint16_t ri, uint16_t arr_len)
{
    uint16_t left = (ri) *2 + 1, largest;
    uint16_t right = (ri + 1) * 2;
    if (left <= arr_len && (*arr)[left] > (*arr)[ri]) {
        largest = left;
    } else {
        largest = ri;
    }

    if (right <= arr_len && (*arr)[right] > (*arr)[largest])
        largest = right;
    if (largest != ri) {
        (*arr)[ri] = (*arr)[largest] ^ (*arr)[ri];
        (*arr)[largest] = (*arr)[ri] ^ (*arr)[largest];
        (*arr)[ri] = (*arr)[ri] ^ (*arr)[largest];
        max_heapify(arr, largest, arr_len);
    }
}


void build_max_heap(uint16_t **arr, uint16_t arr_len)
{
    for (int i = (arr_len - 2) / 2; i >= 0; i--) {
        max_heapify(arr, i, arr_len);
    }
}

void heap_sort(uint16_t **arr, uint16_t arr_len)
{
    for (int i = arr_len - 1; i >= 1; i--) {
        (*arr)[0] = (*arr)[i] ^ (*arr)[0];
        (*arr)[i] = (*arr)[0] ^ (*arr)[i];
        (*arr)[0] = (*arr)[0] ^ (*arr)[i];
        max_heapify(arr, 0, i - 1);
    }
}

int main(void)
{
    random_shuffle_array(values, (uint16_t) ARRAY_SIZE(values));

    uint16_t *max_h = malloc(sizeof(uint16_t) * (256));
    for (int i = 0; i < 256; i++) {
        max_h[i] = values[i];
    }

    build_max_heap(&max_h, 256);
    heap_sort(&max_h, 256);

    qsort(values, ARRAY_SIZE(values), sizeof(values[0]), cmpint);


    for (size_t i = 0; i < ARRAY_SIZE(values); i++) {
        assert(max_h[i] == values[i]);
    }

    return 0;
}
