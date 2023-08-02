//
// Created by finas on 8/2/2023.
//

#ifndef COP3530_PROJECT_3_GAMEOBJECT_H
#define COP3530_PROJECT_3_GAMEOBJECT_H


struct gameObject {
    int _appid;
    string _name;
    string _developer;
    string _publisher;
    string _score_rank;
    int _pos_reviews;
    int _neg_reviews;
    int _owners;
    string _average_forever; // average playtime since march 2009 in minutes
    string _average_2weeks; // average playtime in the last two weeks in minutes
    string _median_forever; // median playtime since march 2009 in minutes
    string _median_2weeks; // median playtime in last two weeks
    int _ccu;
    string _price;
    string _inital_price;
    string _discount;
    vector<string> _languages;
    string _genre;
};


#endif //COP3530_PROJECT_3_GAMEOBJECT_H
