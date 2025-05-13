//
// Created by os on 7/27/23.
//
// Preuzeto sa vezbi

#ifndef PROJEKAT_LIST_HPP
#define PROJEKAT_LIST_HPP


#include "../lib/mem.h"
#include "syscallHandler.hpp"


template<typename T>
class List {
private:
    struct Elem {
        T* data;
        Elem* next;
        Elem(T* data, Elem* next) : data(data), next(next) { };
        void* operator new(size_t size) { return SysCallHandler::memAlloc(size); } //da bi sprecilo ugnjezdeni sistemski poziv
        void operator delete(void* p) { SysCallHandler::memFree(p); }
    };

    Elem *head, *tail;

public:
    List() : head(0), tail(0) { }

    List(const List<T> &) = delete;//zabranjuje kopiranje

    List<T> &operator=(const List<T>&) = delete;//brise operator dodele kopiranjem

    void addFirst(T* data) {
        Elem *elem = new Elem(data, head);
        head = elem;//stavlja ga na pocetak
        if(!tail) tail = head;
    }

    void addLast(T* data) {
        Elem *elem = new Elem(data, 0);

        if(tail) {
            tail->next = elem;
            tail = elem;
        }
        else
            head = tail = elem;//ako tail==0, onda ni head ne postoji
    }

    T* removeFirst() {
        if(!head) return 0;

        Elem* elem = head;
        head = head->next;
        if(!head) tail = 0;//u svakom koraku se proverava da li je br. elem > 0

        T *ret = elem->data;
        delete elem;
        return ret;
    }

    T* peekFirst() {//vraca element bez uklanjanja
        if(!head) return 0;
        return head->data;
    }

    T* removeLast() {
        if(!head) return 0;

        Elem* prev = 0; //element koji prethodi tail-u
        for(prev = head; prev && prev->next != tail; prev=prev->next);//razlicita for petlja

        Elem* elem = tail;
        if(prev) prev->next = 0;
        else
            head=0; //samo je moglo da izadje ako nema nijednog elem. u listi
        tail = prev;

        T* ret = elem->data;
        delete elem;
        return ret;
    }

    T* peekLast() {
        if(!tail) return 0;
        return tail->data;
    }

};



#endif //PROJEKAT_LIST_HPP
