//
// Created by finas on 8/2/2023.
//
#include <iostream>
#include "hashMap.h"


void HashNode::put(int key, const gameObject& game) {
    _bucket.emplace_back(key, game);
}

HashMap::HashMap(int capacity, double maxLF) {
    _numElements = 0;
    _capacity = capacity;
    _maxLF = maxLF;
    _hashArr = new HashNode *[_capacity];
    for (int i = 0; i < _capacity; i++) {
        _hashArr[i] = nullptr;
    }
}

int HashMap::getCapacity() const {
    return _capacity;
}

void HashMap::reHash() {
    int oldCap = _capacity;
    _capacity = _capacity * 2 + 1;
    HashNode **newHashMap = new HashNode *[_capacity];

    for (int i = 0; i < _capacity; i++) {
        newHashMap[i] = nullptr;
    }



    for (int i = 0; i < oldCap; i++) {
        HashNode *oldNode = _hashArr[i];

        if (oldNode == nullptr) {
            continue;
        }

        for(int j = 0; j < oldNode->_bucket.size(); j++) {
            if (oldNode->_bucket.at(j).first == 247890) {
            }

            pair<int, gameObject> myPair = (oldNode->_bucket.at(j));
            if (newHashMap[hashFunc(myPair.first)] == nullptr) {
                HashNode *node = new HashNode;
                newHashMap[hashFunc(myPair.first)] = node; // because _capacity is changed, so is the hashfunction
                node->put(myPair.first, myPair.second);
            }
            else {
                auto node = newHashMap[hashFunc(myPair.first)];
                node->put(myPair.first, myPair.second);
            }

        }

    }
    for (int i = 0; i < oldCap; i++) {
        HashNode *oldNode = _hashArr[i];
        if (oldNode == nullptr) {
            continue;
        }
        else {
            delete oldNode;
        }
    }

    delete [] _hashArr;
    _hashArr = newHashMap;
}

int HashMap::hashFunc(int key) const {

    return key % _capacity; // basically just reduce
}

void HashMap::insert(int key, gameObject &game) {

    int hashCode = hashFunc(key);

    if (hashCode > _capacity - 1) {

        reHash();
        insert(key, game);
    }

    else {

        // check if node at hashCode already exists
        HashNode* oldNode = _hashArr[hashCode];
        if (oldNode == nullptr) { // if it doesnt set it to a new node
            HashNode *node = new HashNode;
            _hashArr[hashCode] = node;
        }

        // check if the key already exists
        for (int i = 0; i < _hashArr[hashCode]->_bucket.size(); i++) {
            if (_hashArr[hashCode]->_bucket.at(i).first == key) {
                return; // if it does, return
            }
        }

        _hashArr[hashCode]->put(key, game);
        _numElements++;
    }
    if ((double)_numElements/(double)_capacity > _maxLF) {

        reHash();

    }

}

bool HashMap::at(const int key, gameObject &value) {
    int hashCode = hashFunc(key);
    if (hashCode > _capacity - 1) {
        return false;
    }
    HashNode node;
    if (_hashArr[hashCode] != nullptr) {
        node = *_hashArr[hashCode];
    }
    else {
        return false;
    }
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
    delete [] _hashArr;
}

void HashMap::PrintAll() {
    for (int i = 0 ; i < _capacity; i++) {
        if (_hashArr[i] != nullptr) {
            for (int j = 0; j < _hashArr[i]->_bucket.size(); j++) {
                _hashArr[i]->_bucket.at(j).second.PrintStats();
            }
        }
    }
}

int HashMap::getNumElements() const {
    return _numElements;
}