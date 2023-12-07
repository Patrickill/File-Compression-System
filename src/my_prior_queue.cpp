//
// Created by 13223 on 2023/12/6.
//
#include "my_prior_queue.h"
#include <algorithm>

my_prior_queue::my_prior_queue(int w[], int re[], int leafLen) {
    tail = leafLen, head = 0;
    for (int i = 0; i < leafLen; i++) {
        que[i] = new Node(nullptr, nullptr, w[re[i]], re[i]);
    }
    sort(0, tail - 1);
}
//FIXME: 第一种写法就会报错
my_prior_queue::~my_prior_queue() {
    //    for (int i = 0; i < 3000; i++) {
    //        delete que[i];
    //    }
    delete[] que;
}

bool my_prior_queue::empty() const {
    return tail - head == 0;
}

int my_prior_queue::size() const {
    return tail - head;
}

void my_prior_queue::push(Node *node) {
    que[tail++] = node;
    sort(head, tail - 1);
}

void my_prior_queue::pop() {
    head++;
}

Node *my_prior_queue::top() {
    return que[head];
}
void my_prior_queue::sort(int l, int r) {
    //用快排维护队列的有序性
    if (l >= r) return;
    Node *tmp = que[(l + r) / 2];
    int i = l - 1, j = r + 1;
    while (i < j) {
        do i++;
        while (que[i]->getW() < tmp->getW());
        do j--;
        while (que[j]->getW() > tmp->getW());
        if (i < j) std::swap(que[i], que[j]);
    }
    sort(l, j), sort(j + 1, r);
}
