//
// Created by finas on 8/2/2023.
//

#include <string>
#include <vector>
#include <iostream>

using namespace std;

#include "gameObject.h"

void gameObject::PrintStats() {
    cout << "Game properties of game with appID\'" << _appid <<"\'" << endl;
    cout << "    Name : " << _name << endl;
    cout << "    Developer : " << _developer << endl;
    cout << "    Publisher : " << _publisher << endl;
    cout << "    Genre : " << _genre << endl;
    cout << "    Score Rank : " << _score_rank << endl;
    cout << "    Positive Reviews : " << _pos_reviews << endl;
    cout << "    Negative Reviews : " << _neg_reviews << endl;
    cout << "    User Score : " << _userscore << endl;
    cout << "    Number of Owners : " << _owners << endl;
    cout << "    Average Playtime (all time) : " << _average_forever << endl;
    cout << "    Average Playtime (last two weeks) : " << _average_2weeks << endl;
    cout << "    Median Playtime (all time) : " << _median_forever << endl;
    cout << "    Median Playtime (last twoo weeks) : " << _median_2weeks << endl;
    cout << "    Peak CCU (8/3/23) : " << _ccu << endl;
    cout << "    Price : " << _price << endl;
    cout << "    Initial Price : " << _initial_price << endl;
    cout << "    Discount : " << _discount << endl;
}