#include "memory_management.h"

char memory[2000];      //Simulating a heap space
struct block *freeList;

void initialize()
{
    freeList = (void *)memory;
    freeList->size = 2000 - sizeof(struct block);   //available space
    freeList->free = 1;                             //1: free 0: occupied
    freeList->next = NULL;
}

void* _malloc(int size)
{
    struct block *curr;
    void *result;
    if(size <= 0)
    {
        return NULL;
    }
    if(freeList == NULL)
    {
        initialize();
    }
    curr = freeList;
    while((((curr->size)<size)||((curr->free)==0))&&(curr->next!=NULL))
    {
        curr = curr->next;
    }
    if((curr->size)==size)
    {
        curr->free = 0;
        result = (void *)(++curr);
        return result;
    }
    else if((curr->size)>(size+sizeof(struct block)))
    {
        split(curr, size);
        result = (void *)(++curr);
        return result;
    }
    else
    {
        result = NULL;
        return result;
    }
}

void split(struct block *fitting_slot, int size)
{
    struct block *new = (void *)((void *)fitting_slot+size+sizeof(struct block));
    new->size = (fitting_slot->size) - size - sizeof(struct block);
    new->free = 1;
    new->next = fitting_slot->next;
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;
}

void merge()
{
    struct block *curr;
    curr = freeList;
    while((curr->next)!=NULL)
    {
        if((curr->free) && (curr->next->free))
        {
            curr->size += (curr->next->size)+sizeof(struct block);
            curr->next = curr->next->next;
        }
//        curr = curr->next;
    }
}

void _free(void *ptr)
{
    if(((void *)memory<=ptr)&&(ptr<=(void *)(memory+2000)))
    {
        struct block* curr = ptr;
        --curr;
        curr->free = 1;
        merge();
    }
    else
        return;
}