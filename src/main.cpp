//
// Created by finas on 8/2/2023.
//

#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <fstream>
#include "gameObject.h"
#include "hashMap.h"
#include "RBTree.h"

using namespace std;

void ReadFileHashMap(const char* filename, HashMap &map, set<string> &genre);
void ReadFileRBTree(const char* filename, RBTree &map, set<string> &genre);
gameObject CreateObj(string &lineFromFile);
void printDecendingOrderHM(HashMap &map);
void printDecendingOrderRB(HashMap &map);


int main() {

    const char* file = "data/steamspy.csv";
    const char* file2 = "data/test.csv";
    set<string> genres;

    string userInput;

    HashMap myHashMap;
    ReadFileHashMap(file2, myHashMap, genres);
    RBTree myRBTree;
    ReadFileRBTree(file2, myRBTree, genres);

    cout << "Welcome to the Steampunks' Trend Analyzer!" << endl;
    cout << "Please type one of the following numbers to browse the games from that genre." << endl << endl;

    int counter = 1;
    for (auto iter = genres.begin(); iter != genres.end(); iter++) {
        cout << "    " << counter << ". " << *iter << endl;
        counter++;
    }
    cout << endl;
    cin >> userInput;

    return 0;
}

gameObject CreateObj(string &lineFromFile) {

    int metacritic;
    int recommendations;

    istringstream stream(lineFromFile);
    string token;
    getline(stream, token, ',');
    int appid = stoi(token);
    getline(stream, token, ',');
    string type = token;
    getline(stream, token, ',');
    if (token[0] == '\"') {
        string fullname = "";
        token = token.substr(1);
        while (token[token.size() - 1] != '\"') {
            fullname.append(token);
            fullname.append(",");
            getline(stream, token, ',');
        }
        fullname.append(token.substr(0,token.size() - 1));
        token = fullname;
    }
    string name = token;
    getline(stream, token, ',');
    string genre = token;
    getline(stream, token, ',');
    if (token != "") {
        metacritic = stoi(token);
    }
    else {metacritic = 0;}
    getline(stream, token, ',');
    double price = stod(token)/100.00;
    getline(stream, token, ',');
    if (token != "") {
        recommendations = stoi(token);
    }
    else {recommendations = 0;}
    getline(stream, token, ',');
    string dev = token;


    gameObject game(appid, type, name, genre, metacritic, price, recommendations, dev);
    return game;
}

void ReadFileHashMap(const char* filename, HashMap &map, set<string> &genre) {
    // Read the file, create and store some game objects
    string lineFromFile;
    ifstream file;
    file.open(filename);
    getline(file, lineFromFile); // get the template line out of the way
    if (file.is_open()) {
        while (getline(file, lineFromFile)) {
            if (!lineFromFile.empty()) {
                gameObject obj = CreateObj(lineFromFile);
                map.insert(obj._appid, obj);
                genre.emplace(obj._genre);
            }
        }
    }
}

void ReadFileRBTree(const char* filename, RBTree &map, set<string> &genre) {
    // Read the file, create and store some game objects
    string lineFromFile;
    ifstream file;

    if(file.is_open()) {
        cout << "da file is open" << endl;
    }
    file.open(filename);

    getline(file, lineFromFile); // get the template line out of the way

    if (file.is_open()) {
        while (getline(file, lineFromFile)) {
            if (!lineFromFile.empty()) {
                gameObject obj = CreateObj(lineFromFile);
                map.insert(obj._appid, obj);
            }
        }
    }
}

void printDecendingOrderHM(HashMap &map) {
    vector<gameObject> sortVec;

}

void printDecendingOrderRB(HashMap &map) {

}