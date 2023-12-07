//
// Created by 13223 on 2023/12/6.
//
#include "Node.h"

Node::Node(Node *l, Node *r, int w, int code) {
    this->l = l;
    this->r = r;
    this->w = w;
    this->code = code;
}
Node::~Node() {
    delete this->l;
    delete this->r;
}

Node *Node::getL() const {
    return l;
}

Node *Node::getR() const {
    return r;
}

int Node::getW() const {
    return w;
}

int Node::getCode() const {
    return code;
}