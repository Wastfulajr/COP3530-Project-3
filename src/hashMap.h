//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_HASHMAP_H
#define COP3530_PROJECT_3_HASHMAP_H
#include <unordered_map>
using namespace std;
#include "gameObject.h"

struct HashNode {

    vector<pair<int, gameObject>> _bucket;
    void put(int key, gameObject game);
    ~HashNode();

};

class HashMap {

private:
    int _numElements;
    double _maxLF;
    int _capacity;
    //vector<HashNode*> *_hashVec = new vector<HashNode*>;
    HashNode **_hashArr;

    HashMap(int capacity, double maxLF = 0.5);
    ~HashMap();
    int hashFunc(int key);
    void reHash();

public:
    void insert(int key, gameObject game);
    bool at(const int key, gameObject &value) ;

};


#endif //COP3530_PROJECT_3_HASHMAP_H
