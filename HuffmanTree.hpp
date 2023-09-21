#ifndef HUFFMANTREE_H
#define HUFFMANTREE_H

#include <map>
#include <vector>
#include <string>
#include <stack>
#include "HeapQueue.hpp"
#include "HuffmanBase.hpp"


class HuffmanTree{
    public:
    HuffmanTree();
    std::string compress(const std::string inputStr);// gives each character a binary value and returns the compressed string 
    std::string serializeTree();//turns tree into a postorder serialized string
    std::string decompress(const std::string inputCode, const std::string serializedTree);// returns the original string given the compressed form and the serialized tree
};
#endif