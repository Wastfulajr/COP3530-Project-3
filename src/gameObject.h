//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_GAMEOBJECT_H
#define COP3530_PROJECT_3_GAMEOBJECT_H
#include <utility>
#include <string>

using namespace std;

struct gameObject {

    int _appid;
    string _name;
    string _type;
    string _genre;
    int _metacritic;
    int _recommendations;
    string _developer;
    int _positive;
    int _negative;
    string _owners;
    double _price;
    int _ccu;
    double _success;

    gameObject();
    gameObject(int appid, string name, string type, string genres, int metacritic, int recommendations, string developers, int positive, int negative, string owners, double price, int ccu);
    void PrintStats();
    void PrintStatsClean();
    friend bool operator<(const gameObject& lhs, const gameObject& rhs);
    friend bool operator>(const gameObject& lhs, const gameObject& rhs);
};


#endif //COP3530_PROJECT_3_GAMEOBJECT_H
