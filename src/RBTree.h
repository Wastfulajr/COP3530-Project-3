//
// Created by Jonathan
//

#ifndef CRAZYPROJECT3_RBTREE_H
#define CRAZYPROJECT3_RBTREE_H
#include <utility>

#include "gameObject.h"


struct RBNode {
    int key;
    bool color; // TRUE IS BLACK ---- FALSE IS RED
    gameObject game;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int key) : key(key), color(false), left(nullptr), right(nullptr), parent(nullptr) {}
    // clion was begging me to use std::move for constructor below this so i just let lil bro do it and included <utility> -- may remove later if causes weird issues
    RBNode(int key, gameObject game) : key(key), color(false), game(std::move(game)), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    RBNode* root;

    void rotateLeft(RBNode* node);
    void rotateRight(RBNode* node);
    void correctTree(RBNode* node);
    RBNode* findSibling(RBNode* node);
    RBNode* findUncle(RBNode* node);

public:
    RBNode* returnRoot();
    RBTree() : root(nullptr) {}
    void insert(int key, gameObject game);
    RBNode* search(int val);
    void debugInsert(int key);
    void inorderTraversal(RBNode* node);
};


#endif //CRAZYPROJECT3_RBTREE_H
