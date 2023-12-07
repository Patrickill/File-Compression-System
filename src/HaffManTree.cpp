//
// Created by 13223 on 2023/12/6.
//
#include "HaffManTree.h"
#include "my_prior_queue.h"
#include <iostream>
//TODO: 步骤成功与否的信息显示 动态内存的管理和内存泄露的注意
//TODO: 要写就一次性好好写好，情况都好好考虑好，要看就从头到位一行一行看
//FIXME: 多次运行会报错 一次运行大文件也会报错退出
HaffManTree::HaffManTree(int w[], int re[], int leafLen) {
    my_prior_queue que(w, re, leafLen);
    std::cout << que.top()->getCode() << std::endl;
    while (que.size() > 1) {
        Node *l = que.top();
        que.pop();
        Node *r = que.top();
        que.pop();
        que.push(new Node(l, r, l->getW() + r->getW(), -1));
    }
    root = que.top();
    std::cout << root->getCode() << std::endl;
    std::cout << root->getW() << std::endl;

    getCode();
}
HaffManTree::~HaffManTree() {
    delete[] code;
}

Node *HaffManTree::getRoot() const {
    return root;
}

void HaffManTree::dfs(Node *p, std::string s) {
    if (p->getCode() != -1) {
        code[p->getCode()] = s;
    }
    if (p->getL() == nullptr && p->getR() == nullptr) {
        return;
    }
    if (p->getL() != nullptr)
        dfs(p->getL(), s + "0");
    if (p->getR() != nullptr)
        dfs(p->getR(), s + "1");
}

void HaffManTree::getCode() {
    Node *p = root;
    dfs(p, "");
}

std::string *HaffManTree::getCodeArr() const {
    return code;
}
