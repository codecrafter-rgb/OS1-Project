//
// Created by os on 7/22/23.
//

#ifndef PROJEKAT_MEMORYALLOCATOR_H
#define PROJEKAT_MEMORYALLOCATOR_H

#include "../lib/hw.h"

//using size_t = decltype(sizeof(0));//moze iz hw.h

class MemoryAllocator {
private:
    MemoryAllocator() {
        FREE_SPACE = (size_t) HEAP_END_ADDR - (size_t) HEAP_START_ADDR - sizeof(FreeBlock);//u svakom trenutku ima makar jedan FreeBlock header

        freeMemHead = (FreeBlock*) HEAP_START_ADDR;
        freeMemHead->size = FREE_SPACE;
        freeMemHead->next = freeMemHead->prev = nullptr;
    };

    struct FreeBlock {
        FreeBlock* next, *prev;
        size_t size;//ukazuje na velicinu
        FreeBlock() : next(nullptr), prev(nullptr), size(0) { }
    };

    FreeBlock* freeMemHead; //razlicito od 0(nullptr)

    //treba static
     size_t FREE_SPACE;

    //Pokusa da spoji jedan slobodni blok sa narednim slobodnim blokom
    int tryToJoin(FreeBlock* cur);
    
public:
    //MemoryAllocator() = delete;//privatni konstruktor?
    void* mem_alloc (size_t size);
    int mem_free (void*);
    static MemoryAllocator* getInstance();
};


#endif //PROJEKAT_MEMORYALLOCATOR_H
