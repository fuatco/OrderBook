#ifndef Common_h
#define Common_h

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <set>
#include <memory>
#include <algorithm>
#include "csv.h"
using namespace std;
enum Action {
    NEW,
    CANCEL,
    FLUSH,
    NONE
};

enum Side{
    BUY,
    SELL,
    OTHER
};

class Order {
public:
    Action action;
    int userID;
    string symbol;
    int price;
    int qty;
    Side side;
    int orderID;
    
    Action mapAction(string action){
        if(action == "N"){
            return NEW;
        }else if(action == "C"){
            return CANCEL;
        }else if (action == "F"){
            return FLUSH;
        }
        return NONE;
    }
    
    Side mapSide(char side){
        if(side == 'S'){
            return SELL;
        }else if (side == 'B'){
            return BUY;
        }
        return OTHER;
    }

    Order(string a, int uID, string s, int p, int q, char sd, int oId){
        action = mapAction(a);
        userID = uID;
        symbol = s;
        price = p;
        qty = q;
        side = mapSide(sd);
        orderID = oId;
    }
    
    bool operator < (const Order& o) const
    {
        return (price > o.price);
    }

};

#endif /* Common_h */
