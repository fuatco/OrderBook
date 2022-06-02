//
//  OrderProcessor.hpp
//  KrakenOrderBook
//
//  Created by fuat co on 02/06/2022.
//

#ifndef OrderProcessor_hpp
#define OrderProcessor_hpp
#include "Common.h"
using namespace std;

class OrderProcessor {
private:
    string getSide(Side side){
        if(side == SELL){
            return "S";
        }
        return "B";
    }
public:
    OrderProcessor() = default;
    
    virtual void NewOrder(Order* order);
    virtual void TopOfBookChanged(Order* order);
    virtual void OrderRejected(Order* order);
    virtual void Trade(Order* buyOrder, Order* sellOrder);
};

#endif /* OrderProcessor_hpp */
