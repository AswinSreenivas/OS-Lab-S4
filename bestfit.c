#include<stdio.h>
#include<stdlib.h>

//structure to represent a block of memory
struct block {
    int size;
    int free;
    struct block *next;
};

//global variable
struct block *head;

//function to initialize a block of memory
void initialize(int size) {
    head = (struct block*)malloc(sizeof(struct block));
    head->size = size;
    head->free = 1;
    head->next = NULL;
}

//function to allocate memory using best fit algorithm
void *bestFit(int size) {
    struct block *temp = head;
    struct block *bestBlock = NULL;
    while(temp != NULL) {
        if(temp->free == 1 && temp->size >= size) {
            if(bestBlock == NULL || temp->size < bestBlock->size) {
                bestBlock = temp;
            }
        }
        temp = temp->next;
    }
    if(bestBlock == NULL) {
        return NULL;
    } else {
        bestBlock->free = 0;
        return (void*)(bestBlock+1);
    }
}

//function to free allocated memory
void deallocate(void *p) {
    struct block *temp = (struct block*)p - 1;
    temp->free = 1;
}

//function to display the memory status
void display() {
    struct block *temp = head;
    printf("Memory Status:\n");
    while(temp != NULL) {
        printf("%d %d %d\n", (int)temp, temp->size, temp->free);
