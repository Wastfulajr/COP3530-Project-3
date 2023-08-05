//
// Created by finas on 8/2/2023.
//

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "gameObject.h"

gameObject::gameObject() {
    _appid = -1;
    _type = "default type";
    _name = "default name";
    _genre = "default genre";
    _metacritic = -1;
    _price = -1.0;
    _recommendations = -1;
    _developer = "default developer";
}

gameObject::gameObject(int appid, string type, string name, string genre, int metacritic, double price,
                       int recommendations, string developer) {
    _appid = -1;
    _type = type;
    _name = name;
    _genre = genre;
    _metacritic = metacritic;
    _price = price;
    _recommendations = recommendations;
    _developer = developer;
}


void gameObject::PrintStats() {
    cout << "Game properties of game with appID\'" << _appid <<"\'" << endl;
    cout << "    Name : " << _name << endl;
    cout << "    Type : " << _type << endl;
    cout << "    Genre : " << _genre << endl;
    cout << "    Price : " << _price << endl;
    cout << "    Developer : " << _developer << endl;
    cout << "    Metacritic Score : " << _metacritic << endl;
    cout << "    Number of Recommendations : " << _recommendations << endl;
}