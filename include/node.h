#ifndef NODE_H
#define NODE_H

#include "util.h"

class Node
{
    int freq;
    char letter;
    Node *left;
    Node *right;

 public:
    Node() {}

    Node(int frequencie, Node *lchild = nullptr, Node *rchild = nullptr)
         : freq(frequencie), left(lchild), right(rchild) {}

    Node(const Node &node) : freq(node.getFreq()), letter(getLetter()),
         left(node.getLChild()), right(node.getRChild()) {}

    Node(int fre, char ch, Node *lchild = nullptr, Node *rchild = nullptr)
        : freq(fre), letter(ch), left(lchild), right(rchild) {}

    ~Node();

    int getFreq() const{ return freq; }
    char getLetter() const{ return letter; }
    bool isLeafNode() 
    {
        return left == nullptr and right == nullptr;
    }
    Node *getLChild() const{
        return left ; 
    }
    Node *getRChild() const{
        return right;
    }
};

using Compare  = bool (const Node *n1, const Node *n2);

bool pred(const Node *n1, const Node *n2);

template <typename T>
typename std::vector<T>::iterator insertOrd(std::vector<T> & vec, T item, Compare pred){

    auto i = vec.begin();
    for (; i != vec.end(); ++i)
    {
        if(pred(item,*i)){
            return vec.insert(i,item);
        }
    }
    return vec.insert(i,item);

}

#endif
