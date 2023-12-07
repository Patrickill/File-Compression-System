//
// Created by 13223 on 2023/12/6.
//

#ifndef FILE_COMPRESSION_SYSTEM_HAFFMANTREE_H
#define FILE_COMPRESSION_SYSTEM_HAFFMANTREE_H
#include "Node.h"
#include <string>
class HaffManTree {
public:
    HaffManTree(int w[], int re[], int leafLen);
    ~HaffManTree();
    //获取哈夫曼的根节点
    [[nodiscard]] Node *getRoot() const;
    //TODO: 获取哈夫曼的编码
    void getCode();
    void dfs(Node *p, std::string s);
    [[nodiscard]] std::string *getCodeArr() const;

private:
    Node *root;
    std::string *code = new std::string[300]();
};
#endif//FILE_COMPRESSION_SYSTEM_HAFFMANTREE_H
