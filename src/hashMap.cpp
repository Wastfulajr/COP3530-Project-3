//
// Created by finas on 8/2/2023.
//

#include "hashMap.h"

HashNode::HashNode(int key, gameObject game) {
    _key = key;
    _game = game;
}

void HashMap::emplace(int key, gameObject game) {
    _mapArray[key] = game;
}

gameObject &HashMap::at(int key) {
    return _mapArray[key];
}

HashMap::~HashMap() {
    delete _mapArray;
}