#include <iostream>
#include <string>
#include "Common.h"
#include "OrderProcessor.hpp"
#include "OrderManager.hpp"

#define ASSERT_THROW( condition )                             \
{                                                                   \
  if( !( condition ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
    );                                                              \
  }                                                                 \
}

#define ASSERT_EQUAL( x, y )                                  \
{                                                                   \
  if( ( x ) != ( y ) )                                              \
  {                                                                 \
    throw std::runtime_error(   std::string( __FILE__ )             \
                              + std::string( ":" )                  \
                              + std::to_string( __LINE__ )          \
                              + std::string( " in " )               \
                              + std::string( __PRETTY_FUNCTION__ )  \
                              + std::string( ": " )                 \
                              + std::to_string( ( x ) )             \
                              + std::string( " != " )               \
                              + std::to_string( ( y ) )             \
    );                                                              \
  }                                                                 \
}


class DummyOrderProcessor : public OrderProcessor {
public:
    std::vector<Order*> newTrades;
    std::vector<Order*> rejectedOrders;
    std::vector<Order*> trades;
    Order* top;
    
    void NewOrder(Order* order) override {
        newTrades.push_back(order);
    }
    void TopOfBookChanged(Order* order)override{
        top = order;
    }
    void  OrderRejected(Order* order)override{
        rejectedOrders.push_back(order);
    }
    void  Trade(Order* buyOrder, Order* sellOrder)override
    {
        trades.push_back(buyOrder);
        trades.push_back(sellOrder);
    }
};


void single_order_test()
{
    std::queue<Order*> trades;
    Order* buyOrder = new Order("B", 1, "symbol", 11, 11, BUY, 123);
    trades.push(buyOrder);
    
    DummyOrderProcessor p;
    OrderManager manager(trades, p);
    manager.PublishBook();
    ASSERT_EQUAL(p.newTrades.size(), 1);
}




int main(int, char**)
{
    //single_order_test();
    
    return 0;
}
