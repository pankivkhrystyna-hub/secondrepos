#ifndef SECONDREPOS_NODE_H
#define SECONDREPOS_NODE_H
#include <memory>

template<typename T>
struct Node {
    T data;

    std::shared_ptr<Node<T>> next;

    Node(T value) : data(value), next(nullptr) {}
};

#endif //SECONDREPOS_NODE_H