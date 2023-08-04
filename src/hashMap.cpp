//
// Created by finas on 8/2/2023.
//

#include "hashMap.h"

void HashNode::put(int key, gameObject game) {
    _bucket.push_back(make_pair(key, game));
}

HashNode::~HashNode() {
    for (int i = 0; i < _bucket.size(); i++) {
        delete _bucket.at(i);
    }
}

HashMap::HashMap(int capacity, double maxLF) {
    _capacity = capacity;
    _maxLF = maxLF;
    _hashArr = new HashNode*[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _hashArr[i] = nullptr;
    }
}

void HashMap::reHash() {
    int oldCap = _capacity;
    _capacity = _capacity * 2 + 1;
    HashNode** newHashMap = new HashNode*[_capacity];
    for (int i = 0; i < _capacity; i++) {
        newHashMap[i] = nullptr;
    }

    for (int i = 0; i < oldCap; i++) {
        HashNode* node = _hashArr[i];

    }
}

int HashMap::hashFunc(int key) {
    return key % _capacity; // basically just reduce
}

void HashMap::insert(int key, gameObject game) {
    int hashCode = hashFunc(key);
    if (hashCode > _capacity - 1) {
        // rehash and attempt another insert
    }
    else {
        _hashArr[hashCode]->put(key, game);
        _numElements++;
    }
    if ((double)_numElements/(double)_capacity > _maxLF) {
        // rehash
    }

}

bool HashMap::at(const int key, gameObject &value) {
    int hashCode = hashFunc(key);
    if (hashCode > _capacity - 1) {
        return false;
    }
    HashNode node = *_hashArr[hashCode];
    for (int i = 0; i < node._bucket.size(); i++) {
        if (node._bucket.at(i).first == key) {
            value = node._bucket.at(i).second;
            return true;
        }
    }
    return false;
}

HashMap::~HashMap() {
    for (int i = 0 ; i < _capacity; i++) {
        delete _hashArr[i];
    }
    delete _hashArr;
}