// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 public:
    TPQueue() : head(nullptr), tail(nullptr) { }
    ~TPQueue();
    void push(const T&);
    T pop();
    void print() const;

 private:
    struct Item {
        T data;
        Item* next;
        Item* prev;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);
};

template <typename T>
void TPQueue<T>::push(const T& itm) {
    if (head == nullptr) {
       head = create(itm);
       tail = head;
    } else if (tail->data.prior >= itm.prior) {
        if (tail->data.ch == itm.ch) {
            tail->data = itm;
        } else {
            tail->next = create(itm);
            tail->next->prev = tail;
            tail = tail->next;
        }
    } else if (head == tail) {
        tail->prev = create(itm);
        head = tail->prev;
        head->next = tail;
    } else {
        Item* temp = tail;
        while (temp != head && temp->data.prior < itm.prior) {
        temp = temp->prev;
        }
        if (temp->data.prior > itm.prior) {
            Item* cage = new Item;
            cage->next = temp->next;
            cage->prev = temp;
            cage->data = itm;
            temp->next->prev = cage;
            temp->next = cage;
        }
        if (temp == head && temp->data.prior < itm.prior) {
            head->prev = create(itm);
            head = head->prev;
            head->next = temp;
        }
    }
}

template <typename T>
TPQueue<T>::~TPQueue() {
    while (head) {
        pop();
    }
}

template <typename T>
T TPQueue<T>::pop() {
    if (!head) {
        throw std::string("EMPTY!");
    } else {
        Item* temp = head->next;
        T data = head->data;
        delete head;
        head = temp;
        return data;
    }
}

template <typename T>
void TPQueue<T>::print() const {
    Item* temp = head;
    while (temp) {
        std::cout << temp->data << " ";
        temp = temp->next;
    }
    std::cout << std::endl;
}

template <typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& data) {
    Item* item = new Item;
    item->data = data;
    item->next = nullptr;
    item->prev = nullptr;
    return item;
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
