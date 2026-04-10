#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "Node.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class DoubleLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;
    size_t size;

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void pushFront(T data) {
        auto newNode = std::make_shared<Node<T>>(data);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pushBack(T data) {
        auto newNode = std::make_shared<Node<T>>(data);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    void popFront() {
        if (!head) throw std::out_of_range("List is empty");
        head = head->next;
        if (head) head->prev.reset();
        else tail = nullptr;
        size--;
    }

    void popBack() {
        if (!tail) throw std::out_of_range("List is empty");
        tail = tail->prev.lock();
        if (tail) tail->next = nullptr;
        else head = nullptr;
        size--;
    }

    T& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        auto tmp = head;
        for (size_t i = 0; i < index; ++i) tmp = tmp->next;
        return tmp->data;
    }

    void insertAt(size_t index, T data) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (index == 0) return pushFront(data);
        if (index == size) return pushBack(data);

        auto newNode = std::make_shared<Node<T>>(data);
        auto tmp = head;
        for (size_t i = 0; i < index; ++i) tmp = tmp->next;

        auto prevNode = tmp->prev.lock();
        newNode->next = tmp;
        newNode->prev = prevNode;
        prevNode->next = newNode;
        tmp->prev = newNode;
        size++;
    }

    void removeAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        if (index == 0) return popFront();
        if (index == size - 1) return popBack();

        auto tmp = head;
        for (size_t i = 0; i < index; ++i) tmp = tmp->next;

        auto p = tmp->prev.lock();
        auto n = tmp->next;
        p->next = n;
        n->prev = p;
        size--;
    }

    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    int find(const T& value) const {
        auto tmp = head;
        for (size_t i = 0; i < size; ++i) {
            if (tmp->data == value) return static_cast<int>(i);
            tmp = tmp->next;
        }
        return -1;
    }


    friend std::ostream& operator<<(std::ostream& os, const DoubleLinkedList<T>& list) {
        auto curr = list.head;
        os << "{ ";
        while (curr) {
            os << curr->data << (curr->next ? " <-> " : " ");
            curr = curr->next;
        }
        os << " }";
        return os;
    }
};

#endif
