/*********************
 * Name:Marshal Pfluger
 * Coding 07
 * Purpose: In this assignment we will create
 * a Binary Search Tree object that will work with
 * the same struct Data and struct Node from the
 * previous assignments (int for id and string for‘data’).
**********************/

#include "bintree.h"


BinTree::BinTree() {
    root = nullptr;
    count = 0;
}
BinTree::~BinTree() {
    clear();
}

bool BinTree::isEmpty() {
    return root;
}

int BinTree::getCount() {
    return count;
}

//Gets true root data
bool BinTree::getRootData(Data *tempData) {
    bool status = false;
    if(root){
        tempData->id = root->data.id;
        tempData->information = root->data.information;
        status = true;
    }else{
        tempData->id = -1;
        tempData->information = " ";
    }
    return status;
}

//Display tree public method
void BinTree::displayTree() {
    std::cout << "DISPLAY TREE" << std::endl;
    std::cout << "==============================================" << std::endl;
    //Check if tree is empty
    if (isEmpty()){
        std::cout << "Tree is NOT empty" << std::endl;
    } else{
        std::cout << "Tree is empty" << std::endl;
    }
    //Display height
    std::cout << "Height:" << getHeight() <<std::endl;
    //Display node count
    std::cout << "Node Count:"<< getCount() << std::endl;
    //Display traversals
    std::cout << "\nPre-Order Traversal" << std::endl;
    displayPreOrder();
    std::cout << "\nIn-Order Traversal" << std::endl;
    displayInOrder();
    std::cout << "\nPost-Order Traversal\n" << std::endl;
    displayPostOrder();
    std::cout << "==============================================\n" << std::endl;
}

//Clear and delete tree public method
void BinTree::clear() {
    clear(root);
}

//public addNode method
bool BinTree::addNode(int id, const string *str) {
    bool status = false;
    if (id > MIN && str != nullptr){
        auto *newNode = new DataNode;
        newNode->data.id = id;
        newNode->data.information = *str;
        newNode->left = nullptr;
        newNode->right = nullptr;
        status = addNode(newNode, &root);
    }
    return status;
}

//Remove node public method
bool BinTree::removeNode(int id) {
    bool status = false;
    int tempCount = count;
    root = removeNode(id, root);
    if (count < tempCount){
        status = true;
    }
    return status;
}

//Getnode public method
bool BinTree::getNode(Data *tempData, int id) {
    bool status = false;
    if(id > MIN){
        status = getNode(tempData, id, root);
    }
    return status;
}

//searches for id in tree public method
bool BinTree::contains(int id) {
    bool status = false;
    if(id > MIN){
        status = contains(id, root);
    }
    return status;
}

int BinTree::getHeight() {
    return getHeight(root);
}

void BinTree::displayPreOrder() {
    displayPreOrder(root);
}

void BinTree::displayPostOrder() {
    displayPostOrder(root);
}

void BinTree::displayInOrder() {
    displayInOrder(root);
}


/*****************************************
 * overloaded methods
 * ***************************************/

//clear table private method
// uses recursion to navigate tree
void BinTree::clear(DataNode *tempRoot) {
    if(tempRoot){
        clear(tempRoot->left);
        clear(tempRoot->right);
        tempRoot->left = nullptr;
        tempRoot->right = nullptr;
        delete tempRoot;
        root = nullptr;
        count--;
    }
}

//addNode private method passes in pointer to pointer
//Uses recursion and binary search to add node in tree.
bool BinTree::addNode(DataNode *newNode, DataNode **tempRoot) {
    bool status = false;
    if (*tempRoot) {
        //Recurse left
        if (newNode->data.id < ((*tempRoot)->data.id)){
            status = addNode(newNode, &(*tempRoot)->left);
        }
        //Recurse right
        if (newNode->data.id > ((*tempRoot)->data.id)){
            status = addNode(newNode, &(*tempRoot)->right);
        }
    } else {
        //Adds node to correct position
        *tempRoot = newNode;
        status = true;
        count++;
    }
    return status;
}

//removeNode private method
DataNode *BinTree::removeNode(int id, DataNode *tempRoot) {
    if (tempRoot){
        //Recurse left
        if (id < tempRoot->data.id){
            tempRoot->left = removeNode(id, tempRoot->left);
        //Recurse right
        }else if (id > tempRoot->data.id){
            tempRoot->right = removeNode(id, tempRoot->right);
        //single or no child insert
        }else{
            DataNode *tempNode;
            if(tempRoot->left == nullptr){
                tempNode = tempRoot->right;
                delete tempRoot;
                tempRoot = tempNode;
                count--;
            //single or no child insert
            }else if(tempRoot->right == nullptr){
                tempNode = tempRoot->left;
                delete tempRoot;
                tempRoot = tempNode;
                count--;
            //Multi child insert
            }else{
                tempNode = minValueNode(tempRoot->right);
                tempRoot->data.id = tempNode->data.id;
                tempRoot->data.information = tempNode->data.information;
                tempRoot->right = removeNode(tempNode->data.id, tempRoot->right);
            }
        }
    }
    return tempRoot;
}

//getNode private method
bool BinTree::getNode(Data *tempData, int id, DataNode *tempRoot) {
    bool status = false;
    if(tempRoot){
        if(id == tempRoot->data.id){
            tempData->id = tempRoot->data.id;
            tempData->information = tempRoot->data.information;
            status = true;
        //Recurse left
        }else if (id < (tempRoot->data.id)){
            status = getNode(tempData, id, tempRoot->left);
        //Recurse left
        }else if ((id > (tempRoot->data.id))){
            status = getNode(tempData, id, tempRoot->right);
        }
    }
    return status;
}

//contains private method
//almost identical to getnode without returning data
bool BinTree::contains(int id, DataNode *tempRoot) {
    bool status = false;
    if(tempRoot){
        if(id == tempRoot->data.id){
            status = true;
        }else if (id < (tempRoot->data.id)){
            status = contains(id, tempRoot->left);
        }else if ((id > (tempRoot->data.id))){
            status = contains(id, tempRoot->right);
        }
    }
    return status;
}

//getHeight private method
//counts each level of recursion
int BinTree::getHeight(DataNode *tempRoot) {
    int lh = 0, rh = 0;
    int highest;
    if (tempRoot){
        lh = getHeight(tempRoot->left);
        rh = getHeight(tempRoot->right);
        highest = std::max(lh, rh) + 1;
    }else{
        highest = MIN;
    }
    return highest;
}

//pre order traversal private method
void BinTree::displayPreOrder(DataNode *tempRoot) {
    if (tempRoot) {
        cout << tempRoot->data.id << " " << tempRoot->data.information << endl;
        if (tempRoot->left) {
            displayPreOrder(tempRoot->left);
        }
        if (tempRoot->right) {
            displayPreOrder(tempRoot->right);
        }
    }
}

//post order traversal private method
void BinTree::displayPostOrder(DataNode *tempRoot) {
    if (tempRoot) {
        if (tempRoot->left) {
            displayPostOrder(tempRoot->left);
        }
        if (tempRoot->right) {
            displayPostOrder(tempRoot->right);
        }
        cout << tempRoot->data.id << " " << tempRoot->data.information << endl;
    }
}

//in order traversal private method
void BinTree::displayInOrder(DataNode *tempRoot) {
    if (tempRoot) {
        if (tempRoot->left) {
            displayInOrder(tempRoot->left);
        }
        cout << tempRoot->data.id << " " << tempRoot->data.information << endl;
        if (tempRoot->right) {
            displayInOrder(tempRoot->right);
        }
    }
}

//minvalue Node private method used in removeNode method
DataNode *BinTree::minValueNode(DataNode *tempNode) {
    DataNode* current = tempNode;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}


