//
// Created by finas on 8/2/2023.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include "gameObject.h"
#include "hashMap.h"
#include "RBTree.h"

using namespace std;

void ReadFileHashMap(const char* filename, HashMap &map);
void ReadFileRBTree(const char* filename, RBTree &map);
gameObject CreateObj(string &lineFromFile);


int main() {

    const char* file = "data/steamspy.csv";
    vector<string> genres;

    return 0;
}

gameObject CreateObj(string &lineFromFile) {
    istringstream stream(lineFromFile);

    string token;
    getline(stream, token, ',');
    int appid = stoi(token);
    getline(stream, token, ',');
    string name = token;
    getline(stream, token, ',');
    string developer = token;
    getline(stream, token, ',');
    string publisher = token;
    getline(stream, token, ',');
    string score_rank = token;
    getline(stream, token, ',');
    int pos_reviews = stoi(token);
    getline(stream, token, ',');
    int neg_reviews = stoi(token);
    getline(stream, token, ',');
    int userscore = stoi(token);
    getline(stream, token, ',');
    string owners = token; // problem... the owner has  commas in it so the delimiter is gonna get messed up
    getline(stream, token, ',');
    int average_forever = stoi(token);
    getline(stream, token, ',');
    int average_2weeks = stoi(token);
    getline(stream, token, ',');
    int median_forever = stoi(token);
    getline(stream, token, ',');
    int median_2weeks = stoi(token);
    getline(stream, token, ',');
    double price = stod(token);
    getline(stream, token, ',');
    double initialprice = stod(token);
    getline(stream, token, ',');
    double discount = stod(token);
    getline(stream, token, ',');
    int ccu = stoi(token);

    // todo: add genre when available!!

    gameObject game(appid, name, developer, publisher, score_rank, pos_reviews, neg_reviews, userscore, owners, average_forever, average_2weeks, median_forever, median_2weeks, price, initialprice, discount, ccu);
    return game;
}

void ReadFileHashMap(const char* filename, HashMap &map) {
    // Read the file, create and store some game objects
    string lineFromFile;
    ifstream file(filename);
    getline(file, lineFromFile); // get the template line out of the way
    if (file.is_open()) {
        while (getline(file, lineFromFile)) {
            if (!lineFromFile.empty()) {
                gameObject obj = CreateObj(lineFromFile);
                map.emplace(obj._appid, obj);
            }
        }
    }
}
void ReadFileRBTree(const char* filename, RBTree &map) {
    // Read the file, create and store some game objects
    string lineFromFile;
    ifstream file(filename);
    if (file.is_open()) {
        while (getline(file, lineFromFile)) {
            if (!lineFromFile.empty()) {
                gameObject obj = CreateObj(lineFromFile);
                map.insert(obj._appid, obj);
            }
        }
    }
}

