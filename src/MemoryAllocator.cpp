//
// Created by os on 8/19/23.
//

#include "../h/MemoryAllocator.h"
#include "../lib/hw.h"

//size_t MemoryAllocator::FREE_SPACE = (size_t) HEAP_START_ADDR - (size_t) HEAP_END_ADDR; //kolicina dostupnog prostora


//DELIMICNO PREUZETO SA KOLOKVIJUMA
void* MemoryAllocator::mem_alloc(size_t size) {
        ///Pokusa da nadje slobodan blok, ako ga ne nadje, a ima dovoljno prostora pokusava kompakciju. Ako ga je naslo, azurira ulancanu listu slobodnih blokova
        ///ostavlja zaglavlje na pocetku bloka radi buduceg mem_free i metoda vraca pokazivac na pocetak alociranog bloka.

        // Pokusa da nadje slobodan blok u listi (first fit)
        FreeBlock *blk = freeMemHead, *prev = nullptr;
        for (; blk!=nullptr; prev=blk, blk=blk->next)
            if (blk->size>=size) break;

        if(blk == nullptr && FREE_SPACE < size)
            return 0;

        // Alocira taj blok
        FREE_SPACE = FREE_SPACE - size - sizeof(FreeBlock);//totalna dostupna memorija za thread-ove //ne uracunava header-e, nije precizno
        size_t remainingSize = blk->size - size;//oduzima se dole sizeof(FreeBlock)
        if (remainingSize >= sizeof(FreeBlock) + MEM_BLOCK_SIZE) {//MIN_BLOCK_SIZE i sizeof(FreeBlock) jer ostaje header radi evidencije
            //Ostao je jedan fragment
            blk->size = size;
            size_t offset = sizeof(FreeBlock) + size;//nov preostali prostor je nakon header+size
            FreeBlock* newBlk = (FreeBlock*)((char*)blk + offset);
            if (prev) prev->next = newBlk;
            else freeMemHead = newBlk;
            newBlk->next = blk->next;
            newBlk->size = remainingSize - sizeof(FreeBlock);
        } else {
            // Nema preostalih fragmenata, alocira ceo FreeElem
            if (prev) prev->next = blk->next;
            else freeMemHead = blk->next;
        }
        blk->next = blk->prev = nullptr;//jer vise nije ulancan u listu

        return (void*)( (char*)blk + sizeof(FreeBlock));
}

int MemoryAllocator::tryToJoin(FreeBlock *cur) {
    ///Pokusava da spoji blok cur sa narednim slobodnim blokom. Vraca 1 u slucaju uspeha, a 0 u slucaju neuspeha
    if (!cur) return 0;
    if (cur->next && (char *) cur + cur->size + sizeof(FreeBlock) == (char *) (cur->next)) { //pocetak bloka + velicina + velicina header-a za freeblock
        //Brise cur->next segment
        cur->size += cur->next->size + sizeof(FreeBlock);//kada se spoje dva bloka, i header-i se spajaju
        cur->next = cur->next->next;
        if (cur->next) cur->next->prev = cur;
        return 1;
    } else
        return 0;
}

int MemoryAllocator::mem_free(void *p) { //char* addr, size_t size
    ///Pokusa da oslobodi dati blok iz memorije. Neregularna situacija kada se prosledi blok koji nije u evidenciji. Vraca 0 u slucaju uspeha
    //Neregularna situacija kada se brise blok koji metoda nije sama alocirala?
    
	//actualPointer pokazuje na header bloka, radi lakseg brisanja
    void * actualPointer = (void*)((size_t) p - (size_t) sizeof(FreeBlock));//ulazi u header datog bloka

	// Pronalazi mesto gde treba ubaciti slobodni segment
    FreeBlock* cur=0;
    if (!freeMemHead || (char*) actualPointer<(char*)freeMemHead)
        cur = 0; // ubaca kao prvi u listi
    else
        for (cur=freeMemHead; cur->next!=0 && actualPointer>(char*)(cur->next);
             cur=cur->next);


	//Ubaca novi element posle cur
    FreeBlock* newSeg = (FreeBlock*)actualPointer;
    //newSeg->size = size;
    newSeg->prev = cur;
    if (cur) newSeg->next = cur->next;
    else newSeg->next = freeMemHead;
    if (newSeg->next) newSeg->next->prev = newSeg;
    if (cur) cur->next = newSeg;
    else freeMemHead = newSeg;

    //Pokusa spajanje prethodnog i narednog FreeBlock-a
    tryToJoin(newSeg);
    tryToJoin(cur);

    return 0;
}


MemoryAllocator *MemoryAllocator::getInstance() {
    static MemoryAllocator memoryAlloc;//zove default-ni konstruktor prikikom inicijalizacije klase
    return &memoryAlloc;
}

