//
// Created by finas on 8/2/2023.
//

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

#include "gameObject.h"

gameObject::gameObject() {
    _appid = -1;
    _name = "default name";
    _type = "default type";
    _genre = "default genre";
    _metacritic = -1;
    _recommendations = -1;
    _developer = "default dev";
    _positive = -1;
    _negative = -1;
    _userscore = -1;
    _owners = -1;
    _price = -1.00;
    _ccu = -1;
    _success = -1.0;
}

gameObject::gameObject(int appid, string name, string type, string genres, int metacritic, int recommendations, string developers, int positive, int negative, int userscore, int owners, double price, int ccu) {
    _appid = appid;
    _name = name;
    _type = type;
    _genre = genres;
    _metacritic = metacritic;
    _recommendations = recommendations;
    _developer = developers;
    _positive = positive;
    _negative = negative;
    _userscore = userscore;
    _owners = owners;
    _price = price;
    _ccu = ccu;
    _success = (double)(_positive)/(double)(_positive/(_negative+_positive));
}


void gameObject::PrintStats() {
    cout << "Game properties of game with appID \'" << _appid <<"\'" << endl;
    cout << "    Name: " << _name << endl;
    cout << "    Type: " << _type << endl;
    cout << "    Genre: " << _genre << endl;
    cout << "    Price: " << "$" << _price << endl;
    cout << "    Developer: " << _developer << endl;
    cout << "    Metacritic Score: " << _metacritic << endl;
    cout << "    Number of Positive Reviews: " << _positive << endl;
    cout << "    Number of Negative Reviews: " << _negative << endl;
    cout << "    Total Reviews: " << _negative + _positive << endl;
    cout << "    Number of Recommendations: " << _recommendations << endl;

}

void gameObject::PrintStatsClean() {
    cout << setw(10) << "AppID: " << _appid << " | " << setw(60) << _name << " | " << setw(25) << _metacritic << endl;
}

bool operator<(const gameObject& lhs, const gameObject& rhs) {
    return (lhs._metacritic < rhs._metacritic);
}
bool operator>(const gameObject& lhs, const gameObject& rhs) {
    return (lhs._metacritic > rhs._metacritic);
}