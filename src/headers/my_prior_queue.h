//
// Created by 13223 on 2023/12/6.
//
#ifndef FILE_COMPRESSION_SYSTEM_MY_PRIOR_QUEUE_H
#define FILE_COMPRESSION_SYSTEM_MY_PRIOR_QUEUE_H
#include "Node.h"
class my_prior_queue {
public:
    my_prior_queue(int w[], int re[], int leafLen);
    ~my_prior_queue();
    void push(Node *node);
    void pop();
    Node *top();
    [[nodiscard]] bool empty() const;
    [[nodiscard]] int size() const;
    void sort(int l, int r);

private:
    Node **que = new Node *[3000];
    int head = 0, tail = 0;
};

#endif//FILE_COMPRESSION_SYSTEM_MY_PRIOR_QUEUE_H
