#ifndef MEMORY_MANAGEMENT_H_
#define MEMORY_MANAGEMENT_H_

#include <stddef.h>

struct block{
    size_t size;
    int free;
    struct block *next;
};

void initialize();
void* _malloc(int size);
void split(struct block *fitting_slot, int size);
void merge();
void _free(void *ptr);

#endif
