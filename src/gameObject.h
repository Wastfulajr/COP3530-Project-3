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
    string _type;
    string _name;
    string _genre;
    int _metacritic;
    double _price;
    int _recommendations;
    string _developer;

    gameObject();
    gameObject(int appid, string type, string name, string genre, int metacritic, double price, int recommendations, string developer);
    void PrintStats();
};


#endif //COP3530_PROJECT_3_GAMEOBJECT_H
