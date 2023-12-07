//
// Created by 13223 on 2023/12/6.
//

#ifndef FILE_COMPRESSION_SYSTEM_NODE_H
#define FILE_COMPRESSION_SYSTEM_NODE_H

class Node {
public:
    Node(Node *l, Node *r, int w = -1, int code = -1);
    ~Node();
    Node *getL() const;
    Node *getR() const;
    int getW() const;
    int getCode() const;

private:
    Node *l;
    Node *r;
    int w;
    int code;
};

#endif//FILE_COMPRESSION_SYSTEM_NODE_H
