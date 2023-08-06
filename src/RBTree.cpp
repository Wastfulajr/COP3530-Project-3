//
// Created by Jonathan
//

#include "RBTree.h"
#include <iostream>

// avl tree project throwback
void RBTree::rotateLeft(RBNode* node) {
    if (node == nullptr) {
        return;
    }

    RBNode* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != nullptr) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = rightChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = rightChild;
    }
    else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

// swapped version of left rotation
void RBTree::rotateRight(RBNode* node) {
    if (node == nullptr) {
        return;
    }

    RBNode* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != nullptr) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == nullptr) {
        root = leftChild;
    }
    else if (node == node->parent->left) {
        node->parent->left = leftChild;
    }
    else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

// used in find uncle and in deletion (we may not need deletion)
RBNode* RBTree::findSibling(RBNode* node) {
    if (node == nullptr || node->parent == nullptr) {
        return nullptr;
    }

    if (node == node->parent->left) { // if this is left child of parent,
        return node->parent->right; // return right child of parent
    }
    else {
        return node->parent->left; // return left child of parent
    }
}

// find uncle -- necessary for correcting tree after insertion
RBNode* RBTree::findUncle(RBNode* node) {
    RBNode* parent = node->parent;
    if (parent == nullptr || parent->parent == nullptr) {
        return nullptr;
    }

    return findSibling(parent);
}


// TRUE IS BLACK ---- FALSE IS RED
// responsible for insertion, calls upon correctTree which is responsible for correcting (rotation and color wise) the tree
void RBTree::insert(int val, gameObject& game) {
    RBNode* newNode = new RBNode(val, game);
    if (root == nullptr) { // if inserting root
        root = newNode;
        root->color = true;
    }
    else {
        RBNode* current = root;
        RBNode* parent = nullptr;

        // finding the correct open spot
        while (current != nullptr) {
            parent = current;
            if (val < current->key) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        newNode->parent = parent;
        if (val < parent->key) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        correctTree(newNode);
    }
}

// TRUE IS BLACK ---- FALSE IS RED
// used after insert to correct the tree
void RBTree::correctTree(RBNode* node) {
    if (node == root) { // if inserted node was the root node
        node->color = true; // node color = black
        return;
    }

    // relevant tree members
    RBNode* parent = node->parent;
    RBNode* grandparent = parent->parent;
    RBNode* uncle = findUncle(node);

    if (parent->color == false) { // if parent color is red
        if (uncle != nullptr && uncle->color == false) { // if the uncle is red, flip colors
            parent->color = true;
            uncle->color = true;
            grandparent->color = false;
            correctTree(grandparent);
        }
        else { // if the uncle is black, rotate
            if (parent == grandparent->left) { // left left case or left right case
                if (node == parent->right) { // left right case
                    rotateLeft(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateRight(grandparent);
            }
            else { // right right case or right left case
                if (node == parent->left) {// right left case
                    rotateRight(parent);
                    node = parent;
                    parent = node->parent;
                }
                rotateLeft(grandparent);
            }
            parent->color = true;
            grandparent->color = false;
        }
    }
}

RBNode* RBTree::search(int val) {
    RBNode* current = root; // start from root

    while (current != nullptr) {
        if (val == current->key) {
            return current;
        }
        else if (val < current->key) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }

    return nullptr; // should be the same whether its return current or return nullptr
}

// inorderTraversal(rbTree.returnRoot())
void RBTree::inorderTraversal(RBNode* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        std::cout << node->key << " ";
        inorderTraversal(node->right);
    }
}

RBNode *RBTree::returnRoot() {
    return this->root;
}

