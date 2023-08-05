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
    [[nodiscard]] int hashFunc(int key) const;
    void reHash();


public:
    int getCapacity() const;
    ~HashMap();
    explicit HashMap(int capacity = 20, double maxLF = 0.5);
    void insert(int key, gameObject &game);
    bool at(int key, gameObject &value) ;
    void PrintAll();
    int getNumElements() const;

};


#endif //COP3530_PROJECT_3_HASHMAP_H
