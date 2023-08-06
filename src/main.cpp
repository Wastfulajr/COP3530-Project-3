//
// Created by finas on 8/2/2023.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <set>
#include <fstream>
#include <map>
#include <algorithm>
#include "gameObject.h"
#include "hashMap.h"
#include "RBTree.h"

using namespace std;

void ReadFileHashMap(const char* filename, HashMap &map, set<string> &genre);
void ReadFileRBTree(const char* filename, RBTree &map, set<string> &genre);
gameObject CreateObj(string &lineFromFile);
void printDecendingOrderHM(string targetGenre, HashMap &map);
bool checkInteger(string str);
bool foundKey(int key, map<int,string> map);
vector<gameObject>& sortVecMetacritic(vector<gameObject> &vec);
bool comparator(const gameObject& lhs, const gameObject& rhs);
int correctTokenInt(string uncheckedToken);
string correctTokenString(string uncheckedToken);
double correctTokenDouble(string uncheckedToken);

int main() {

    const char* file = "data/steamspy.csv";
    const char* file2 = "final_data.csv";
    set<string> genres;
    map<int, string> genresMap;

    string dataChoice;
    int dataChoiceInt; // 1 is red-black tree; 2 is hash map
    string userInput;
    int choice;
    string targetGenre;

    cout << "Welcome to the Steampunks' Trend Analyzer!" << endl;
    cout << "Please wait while we load the data into RBTree and a HashMap..." << endl;

    HashMap myHashMap;
    ReadFileHashMap(file2, myHashMap, genres);
    RBTree myRBTree;
    ReadFileRBTree(file2, myRBTree, genres);
    bool weContinue = true;
    while (weContinue) {
        cout << endl << "Type one of the following numbers to browse the games from that genre. Type -1 to exit the program." << endl << endl;

        int counter = 1;
        for (auto iter = genres.begin(); iter != genres.end(); iter++) {
            cout << "    " << counter << ". " << *iter << endl;
            genresMap.emplace(counter, *iter);
            counter++;
        }

        cout << endl;
        bool inputBad = true;
        while (inputBad) {
            cin >> userInput;
            while (!checkInteger(userInput)) {
                cout << "Input was not an integer, please try again." << endl;
                cin >> userInput;
            }

            choice = stoi(userInput);

            if (choice == -1) {
                weContinue = false;
                cout << endl;
                cout << "Thank you for using the Steampunks' Trend Analyzer!" << endl;
            }
            else if (!foundKey(choice, genresMap)) {
                cout << "The integer you entered was not available in the list. Try again." << endl;
            }
            else {
                inputBad = false;
            }

        }
        targetGenre = genresMap.at(choice);
        cout << "Success index: # of positive reviews / # of all reviews." << endl;
        cout << "Games in the " << targetGenre << " genre sorted by success index: " << endl;

        cout << "AppID " << setw(10) << " | "  << "Name" << setw(79) << "| " << setw(10) << "Success Index" << " | " << endl;

        printDecendingOrderHM(targetGenre, myHashMap);

        cout << endl;
        bool decidingData = true;
        while (decidingData) {
            cout << "If you would like to retrieve the data using a red-black tree, type 1." << endl << "If you would like to retrieve the data using a hash map, type 2." << endl;
            cin >> dataChoice;
            while (!checkInteger(dataChoice)) {
                cout << "Input was not an integer, please try again." << endl;
                cin >> dataChoice;
            }
            dataChoiceInt = stoi(dataChoice);
            if (dataChoiceInt != 1 && dataChoiceInt != 2) { // if input is integer but not correct.
                cout << R"(Please enter either '1' or '2')" << endl;
            }
            else {
                decidingData = false;
            }

        }

        gameObject blanky;
        bool contGettingIDs = true;
        while (contGettingIDs) {
            cout << "Type the AppID of the game you would like to view full info for. Type -1 if you want to go back to the list of genres." << endl;
            cin >> userInput;
            while (!checkInteger(userInput)) {
                cout << "Input was not an integer, please try again." << endl;
                cin >> userInput;
            }

            choice = stoi(userInput);

            if (choice == -1) {
                contGettingIDs = false;
            }
            else if (choice < -1) {
                cout << "This AppID does not exist. Try again." << endl;
            }
            else if (dataChoiceInt == 2) { // If retrieving through hash map
                if (!myHashMap.at(choice, blanky)) {
                    cout << "No game was found with that AppID. Try again." << endl;
                }
                else {
                    myHashMap.at(choice, blanky);
                    blanky.PrintStats();
                    cout << endl;
                }
            }
            else { // if retrieving through red-black tree
                if (!myRBTree.search(choice)) {
                    cout << "No game was found with that AppID. Try again." << endl;
                }
                else {
                    auto tempRB = myRBTree.search(choice);
                    blanky = tempRB->game;
                    blanky.PrintStats();
                    cout << endl;
                }
            }


        }
    }
    return 0;
}

void printDecendingOrderHM(string targetGenre, HashMap &map) {
    vector<gameObject> sortVec;
    for (int i = 0; i < map.getCapacity(); i++) {
        if (map._hashArr[i] != nullptr) {
            for (int j = 0; j < map._hashArr[i]->_bucket.size(); j++) {
                if (map._hashArr[i]->_bucket.at(j).second._genre == targetGenre) {
                    sortVec.emplace_back(map._hashArr[i]->_bucket.at(j).second);
                }
            }
        }
    }

    sort(sortVec.begin(), sortVec.end(), greater<gameObject>());

    for (int i = 0; i < sortVec.size(); i++) {
        sortVec.at(i).PrintStatsClean();
    }
}

bool foundKey(int key, map<int, string> m) {
    if (m.find(key) == m.end()) {
        return false;
    }
    return true;
}

bool checkInteger(string str) {
    bool isNeg = false;
    if (str == "") {
        return false;
    }
    if (str[0] == '-') {
        str = str.substr(1,str.size()-1);
        isNeg = true;
    }
    for (int i = 0; i < str.size(); i++) {
        if (!isdigit(str[i])) {
            return false;
        }
    }
    return true;
}

int correctTokenInt(string uncheckedToken) {
    if (uncheckedToken == "") {
        return 0;
    }
    else {
        return stoi(uncheckedToken);
    }
}

double correctTokenDouble(string uncheckedToken) {
    if (uncheckedToken == "") {
        return 0.0;
    }
    else {
        return stod(uncheckedToken);
    }
}

string correctTokenString(string uncheckedToken) {
    if (uncheckedToken == "") {
        return "None";
    }
    else {
        return uncheckedToken;
    }
}

gameObject CreateObj(string &lineFromFile) {

    istringstream stream(lineFromFile);
    string token;

    getline(stream, token, ',');

    int appid = stoi(token);


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

    string type = correctTokenString(token);

    getline(stream, token, ',');

    string genres = correctTokenString(token);

    getline(stream, token, ',');

    int metacritic = correctTokenInt(token);

    getline(stream, token, ',');

    int recommendations = correctTokenInt(token);

    getline(stream, token, ',');
    if (token[0] == '\"') {
        string fulldev = "";
        token = token.substr(1);
        while (token[token.size() - 1] != '\"') {
            fulldev.append(token);
            fulldev.append(",");
            getline(stream, token, ',');
        }
        fulldev.append(token.substr(0,token.size() - 1));
        token = fulldev;
    }

    string developers = token;

    getline(stream, token, ',');

    int positive = correctTokenInt(token);

    getline(stream, token, ',');

    int negative = correctTokenInt(token);

    getline(stream, token, ',');
    if (token[0] == '\"') {
        string fullowners = "";
        token = token.substr(1);
        while (token[token.size() - 1] != '\"') {
            fullowners.append(token);
            fullowners.append(",");
            getline(stream, token, ',');
        }
        fullowners.append(token.substr(0,token.size() - 1));
        token = fullowners;
    }

    string owners = token;

    getline(stream, token, ',');

    double price = correctTokenDouble(token);

    getline(stream, token, ',');

    int ccu = correctTokenInt(token);


    gameObject* game = new gameObject(appid,name,type,genres,metacritic,recommendations,developers,positive,negative,owners,price,ccu);

    return *game;
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
