//
//  OrderManager.hpp
//  KrakenOrderBook
//
//  Created by fuat co on 02/06/2022.
//

#ifndef OrderManager_hpp
#define OrderManager_hpp
#include "Common.h"
#include "OrderProcessor.hpp"

using namespace std;

class OrderManager {
private:
    std::queue<Order*> orders;
    std::unordered_map<string,std::set<Order*>> buyTable;
    std::unordered_map<string,std::set<Order*>> sellTable;
    std::unordered_map<int, string> idTable;
    OrderProcessor processor;
    
    bool validateOrder(Order* order);
    bool isTopOfSellBookChange(Order* order);
    bool isTopOfBuyBookChange(Order* order);
    Order* hasMathcingBuyOrder(Order* order);
    Order* hasMathcingSellOrder(Order* order);
    bool orderExists(Order* order);
    void insertBuyOrder(Order* order);
    void insertSellOrder(Order* order);
    void cancelOrder(Order* order);
    void addNewOrder(Order* order);
    
public:
    OrderManager(std::queue<Order*> o, OrderProcessor p);
    ~OrderManager(){
        while (!orders.empty())
         {
             auto p = orders.front();
             orders.pop();
             delete p;
         }
        for(auto &i : buyTable){
            i.second.clear();
        }
        for(auto &i : sellTable){
            i.second.clear();
        }
    }
    void PublishBook();
    
};
#endif /* OrderManager_hpp */
