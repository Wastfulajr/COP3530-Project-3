//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_GAMEOBJECT_H
#define COP3530_PROJECT_3_GAMEOBJECT_H
#include <utility>

using namespace std;

struct gameObject {

    int _appid;
    string _name;
    string _developer;
    string _publisher;
    string _score_rank;
    int _pos_reviews;
    int _neg_reviews;
    int _userscore;
    string _owners;
    int _average_forever; // average playtime since march 2009 in minutes
    int _average_2weeks; // average playtime in the last two weeks in minutes
    int _median_forever; // median playtime since march 2009 in minutes
    int _median_2weeks; // median playtime in last two weeks in minutes
    int _ccu;
    double _price;
    double _initial_price;
    double _discount;
    vector<string> _languages;
    string _genre;
    double _success_index;

    gameObject() {
        _appid = -1;
        _name = "default name";
        _developer = "default developer";
        _publisher = "default publisher";
        _score_rank = "default score_rank";
        _pos_reviews = -1;
        _neg_reviews = -1;
        _userscore = -1;
        _owners = -1;
        _average_forever = -1;
        _average_2weeks = -1;
        _median_forever = -1;
        _median_2weeks = -1;
        _ccu = -1;
        _price = -1.0;
        _initial_price = -1.0;
        _discount = -1.0;
        _genre = "default genre";

        _success_index = -1.0;
    }

    gameObject(int appid, string name, string developer, string publisher, string score_rank, int pos_reviews, int neg_reviews,
               int userscore, string owners, int average_forever, int average_2weeks, int median_forever, int median_2weeks, double price, double initialprice, double discount, int ccu) {
        _appid = appid;
        _name = std::move(name);
        _developer = std::move(developer);
        _publisher = std::move(publisher);
        _score_rank = std::move(score_rank);
        _pos_reviews = pos_reviews;
        _neg_reviews = neg_reviews;
        _userscore = userscore;
        _owners = owners;
        _average_forever = average_forever;
        _average_2weeks = average_2weeks;
        _median_forever = median_forever;
        _median_2weeks = median_2weeks;
        _ccu = ccu;
        _price = std::move(price);
        _initial_price = initialprice;
        _discount = std::move(discount);


        _success_index = (double)pos_reviews/(double)(pos_reviews+neg_reviews);
    }

    gameObject(int appid, string name, string &developer, string &publisher, string &score_rank,
               int &pos_reviews, int &neg_reviews, int &userscore, string &owners, int &average_forever,
               int &average_2weeks, int &median_forever, int &median_2weeks,
               int &ccu, double &price, double &intial_price, double &discount, vector<string> &languages, string &genre) {

        _appid = appid;
        _name = std::move(name);
        _developer = std::move(developer);
        _publisher = std::move(publisher);
        _score_rank = std::move(score_rank);
        _pos_reviews = pos_reviews;
        _neg_reviews = neg_reviews;
        _userscore = userscore;
        _owners = owners;
        _average_forever = average_forever;
        _average_2weeks = average_2weeks;
        _median_forever = median_forever;
        _median_2weeks = median_2weeks;
        _ccu = ccu;
        _price = std::move(price);
        _initial_price = intial_price;
        _discount = std::move(discount);
        _languages = std::move(languages);
        _genre = std::move(genre);

        _success_index = (double)pos_reviews/(double)(pos_reviews+neg_reviews);
    }

    void PrintStats();
};


#endif //COP3530_PROJECT_3_GAMEOBJECT_H
