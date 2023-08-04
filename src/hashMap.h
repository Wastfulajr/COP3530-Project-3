//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_HASHMAP_H
#define COP3530_PROJECT_3_HASHMAP_H
#include <unordered_map>
#include <vector>
using namespace std;
#include "gameObject.h"

struct HashNode {

    vector<pair<int, gameObject>> _bucket;
    void put(int key, const gameObject& game);

};

class HashMap {

private:
    int _numElements;
    double _maxLF;
    int _capacity;
    //vector<HashNode*> *_hashVec = new vector<HashNode*>;
    HashNode **_hashArr;
    int hashFunc(int key) const;
    void reHash();


public:
    int getCapacity();
    ~HashMap();
    HashMap(int capacity, double maxLF = 0.5);
    void insert(int key, gameObject &game);
    bool at(const int key, gameObject &value) ;

};


#endif //COP3530_PROJECT_3_HASHMAP_H
