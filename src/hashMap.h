//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_HASHMAP_H
#define COP3530_PROJECT_3_HASHMAP_H
#include <unordered_map>
using namespace std;
#include "gameObject.h"

struct HashNode {

    int _key;
    gameObject _game;

    HashNode(int key, gameObject game);

};

class HashMap {

private:
    gameObject* _mapArray = new gameObject[150000];
    ~HashMap();
public:
    void emplace(int key, gameObject game);
    gameObject& at(int key);

};


#endif //COP3530_PROJECT_3_HASHMAP_H
