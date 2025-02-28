
#include <stdio.h>
#include <stdlib.h>

#define MEMORY_SIZE 100

typedef struct Block {
    int size;
    int is_free;
    struct Block* next;
} Block;

Block* head;

void init_memory() {
    head = (Block*)malloc(sizeof(Block));
    head->size = MEMORY_SIZE;
    head->is_free = 1;
    head->next = NULL;
}

Block* allocate(Block* (*fit)(int), int size) {
    Block* b = fit(size);
    if (b) b->is_free = 0;
    return b;
}

Block* first_fit(int size) {
    Block* b = head;
    while (b) {
        if (b->is_free && b->size >= size) return b;
        b = b->next;
    }
    return NULL;
}

Block* best_fit(int size) {
    Block* best = NULL;
    Block* b = head;
    while (b) {
        if (b->is_free && b->size >= size && (!best || b->size < best->size))
            best = b;
        b = b->next;
    }
    return best;
}

Block* worst_fit(int size) {
    Block* worst = NULL;
    Block* b = head;
    while (b) {
        if (b->is_free && b->size >= size && (!worst || b->size > worst->size))
            worst = b;
        b = b->next;
    }
    return worst;
}

void free_memory(Block* b) {
    if (b) b->is_free = 1;
}

void print_memory() {
    Block* b = head;
    while (b) {
        printf("Block size: %d, is_free: %d\n", b->size, b->is_free);
        b = b->next;
    }
}

int main() {
    init_memory();
    printf("First Fit Allocation:\n");
    Block* p1 = allocate(first_fit, 20);
    print_memory();
    printf("\nBest Fit Allocation:\n");
    Block* p2 = allocate(best_fit, 20);
    print_memory();
    printf("\nWorst Fit Allocation:\n");
    Block* p3 = allocate(worst_fit, 20);
    print_memory();
    printf("\nMemory after freeing:\n");
    free_memory(p1);
    free_memory(p2);
    free_memory(p3);
    print_memory();
    return 0;
}

