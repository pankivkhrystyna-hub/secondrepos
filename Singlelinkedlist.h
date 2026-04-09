#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

#include "Node.h"
#include <memory>

template<typename T>
class SingleLinkedList {
private:
    std::shared_ptr<Node<T>> head;
    int size;

public:
    SingleLinkedList() : head(nullptr), size(0) {}
};

#endif