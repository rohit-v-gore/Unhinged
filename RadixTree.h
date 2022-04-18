
#ifndef RADIXTREE_H
#define RADIXTREE_H

#include <iostream>
#include <string>
#include <list>
using namespace std;

const int NUM_MAX_CHILDREN = 128;

template <typename ValueType>
struct RadTreeNode
{
struct RadTreeNode* childNodes[NUM_MAX_CHILDREN];
ValueType val;
bool hasVal;
};

template <typename ValueType>
class RadixTree {
public:
 RadixTree();
 ~RadixTree();
 void insert(std::string key, const ValueType& value);
 ValueType* search(std::string key) const;

private:
 struct RadTreeNode<ValueType>* insertStep(struct RadTreeNode<ValueType>* currnode, char ch);
 struct RadTreeNode<ValueType>* rootNode;
};

template <typename ValueType>
RadixTree<ValueType>::RadixTree() {
rootNode = new (nothrow) RadTreeNode<ValueType>;
if (rootNode == nullptr) {cerr << "Could not create root node" << endl; exit(1);}
for (int i = 0; i < NUM_MAX_CHILDREN; i++) rootNode->childNodes[i] = nullptr;
rootNode->hasVal = false;
}

template <typename ValueType>
RadixTree<ValueType>::~RadixTree() {}

template <typename ValueType>
struct RadTreeNode<ValueType>* RadixTree<ValueType>::insertStep(struct RadTreeNode<ValueType>* currnode, char ch) {
// one step of the string being inserted
int i = ch; // convert to int

//struct RadTreeNode<ValueType>* nextnode = currnode->childNodes[i];
if (currnode->childNodes[i] != nullptr) return currnode->childNodes[i];
else { // create new node
   struct RadTreeNode<ValueType>* newnode = new (nothrow) RadTreeNode<ValueType>;
   if (newnode == nullptr) {cerr << "Could not create new radix tree node" << endl; exit(1);}
   else {
   newnode->hasVal = false;
   for (int j = 0; j < NUM_MAX_CHILDREN; j++) newnode->childNodes[j] = nullptr;
   currnode->childNodes[i] = newnode;
}
   return newnode;
}
}

template <typename ValueType>
void RadixTree<ValueType>::insert(std::string key, const ValueType& value) {
// read each character of the string, convert to number
// follow path in tree until possible using number as array index
// when a missing character is found, create a new node, attach it,
// iterate the process starting at the new node
// once a new node is created, all other characters will result in new nodes
// can write a private function that takes in pointer to RadTreeNode and a character
// figures out what to do and returns pointer to next node, new or existing
//cerr << "Key :" << endl;
//cerr << key << endl;
size_t len = key.length();
char ch;
if (len == 0) return; // will not process empty string
struct RadTreeNode<ValueType>* currnode = rootNode;
for (int i = 0; i < len; i++) {
   ch = key.at(i);
   currnode = insertStep(currnode, ch);
}
currnode->val = value; // will need to define assignment function to ValueType, value gets replaced if already there
// if maintaining a list, then use the
currnode->hasVal = true;
}


template <typename ValueType>
ValueType* RadixTree<ValueType>::search(std::string key) const {
size_t len = key.length();
char ch;
int i_ch;
if (len == 0) return nullptr;

struct RadTreeNode<ValueType>* currnode = rootNode;
struct RadTreeNode<ValueType>* nextnode;
for (int i = 0; i < len; i++) { // traverse nodes until match found
   ch = key.at(i);
   i_ch = ch; // convert to int
   nextnode = currnode->childNodes[i_ch];
   if (nextnode == nullptr) return nullptr; // nowhere to go
   else currnode = nextnode; // move forward
}
// check if current node has a value associated with it
//if (currnode->hasVal) cerr << "Found node with value " << endl;
if (currnode->hasVal) return &(currnode->val);
else return nullptr; // even though the string exists there's no value

}

#endif
