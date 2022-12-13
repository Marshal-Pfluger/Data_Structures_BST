/*********************
 * Name:Marshal Pfluger
 * Coding 07
 * Purpose: In this assignment we will create
 * a Binary Search Tree object that will work with
 * the same struct Data and struct Node from the
 * previous assignments (int for id and string for‘data’).
**********************/

#ifndef BINTREE_BINTREE_H
#define BINTREE_BINTREE_H
#define MIN 0

#include <iostream>
#include <string>
#include "data.h"
using std::cout;
using std::endl;
using std::string;

class BinTree {
public:
    //Public members without overloads
    BinTree();
    ~BinTree();
    bool isEmpty();
    int getCount();
    bool getRootData(Data*);
    void displayTree();

    //Public members with overloads
    void clear();
    bool addNode(int, const string*);
    bool removeNode(int);
    bool getNode(Data*, int);
    bool contains(int);
    int getHeight();
    void displayPreOrder();
    void displayPostOrder();
    void displayInOrder();

private:

    //Private attributes
    DataNode *root;
    int count;

    //Private methods
    void clear(DataNode*);
    bool addNode(DataNode*, DataNode**);
    DataNode* removeNode(int, DataNode*);
    DataNode* minValueNode(DataNode*);
    bool getNode(Data*, int, DataNode*);
    static bool contains(int, DataNode*);
    int getHeight(DataNode*);
    void displayPreOrder(DataNode*);
    void displayPostOrder(DataNode*);
    void displayInOrder(DataNode*);

};


#endif /* BINTREE_BINTREE_H */

