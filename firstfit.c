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

//function to allocate memory using first fit algorithm
void *firstFit(int size) {
    struct block *temp = head;
    while(temp != NULL) {
        if(temp->free == 1 && temp->size >= size) {
            temp->free = 0;
            return (void*)(temp+1);
        }
        temp = temp->next;
    }
    return NULL;
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
        temp = temp->next;
    }
}

//driver function
int main() {
    initialize(100);
    void *p1 = firstFit(20);
    void *p2 = firstFit(30);
    void *p3 = firstFit(10);
    display();
    deallocate(p2);
    display();
    return 0;
}
