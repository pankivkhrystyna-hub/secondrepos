#ifndef LINKED_LISTS_HPP
#define LINKED_LISTS_HPP

#include "Node.h"
#include <iostream>
#include <stdexcept>

template<typename T>
class SingleLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    size_t size;

public:
    SingleLinkedList() : head(nullptr), size(0) {}

    void pushFront(T data) {
        auto newNode = std::make_shared<Node<T>>(data);
        newNode->next = head;
        head = newNode;
        size++;
    }

    void pushBack(T data) {
        auto newNode = std::make_shared<Node<T>>(data);
        if (!head) { head = newNode; }
        else {
            auto tmp = head;
            while (tmp->next) tmp = tmp->next;
            tmp->next = newNode;
        }
        size++;
    }

    void popFront() {
        if (!head) throw std::out_of_range("List is empty");
        head = head->next;
        size--;
    }

    T& at(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        auto tmp = head;
        for (size_t i = 0; i < index; ++i) tmp = tmp->next;
        return tmp->data;
    }

    void removeAt(size_t index) {
        if (index >= size) throw std::out_of_range("Index out of range");
        if (index == 0) return popFront();

        auto tmp = head;
        for (size_t i = 0; i < index - 1; ++i) tmp = tmp->next;
        tmp->next = tmp->next->next;
        size--;
    }

    size_t getSize() const { return size; }
    bool isEmpty() const { return size == 0; }

    friend std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T>& list) {
        auto curr = list.head;
        os << "[ ";
        while (curr) {
            os << curr->data << (curr->next ? " " : " ");
            curr = curr->next;
        }
        os << "]";
        return os;
    }

    void popBack() {
        if (!head) throw std::out_of_range("List is empty");
        if (size == 1) {
            head = nullptr;
        } else {
            auto tmp = head;
            while (tmp->next->next) tmp = tmp->next;
            tmp->next = nullptr;
        }
        size--;
    }


    void insertAt(size_t index, T data) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (index == 0) return pushFront(data);
        if (index == size) return pushBack(data);

        auto newNode = std::make_shared<Node<T>>(data);
        auto tmp = head;
        for (size_t i = 0; i < index - 1; ++i) tmp = tmp->next;

        newNode->next = tmp->next;
        tmp->next = newNode;
        size++;
    }


    int find(const T& value) const {
        auto tmp = head;
        for (size_t i = 0; i < size; ++i) {
            if (tmp->data == value) return static_cast<int>(i);
            tmp = tmp->next;
        }
        return -1;
    }

};

#endif