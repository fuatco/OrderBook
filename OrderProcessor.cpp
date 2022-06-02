//
//  OrderProcessor.cpp
//  KrakenOrderBook
//
//  Created by fuat co on 02/06/2022.
//

#include "OrderProcessor.hpp"

void OrderProcessor::NewOrder(Order* order){
    std::cout << "A " << order->userID << " " << order->orderID << endl;
}
void OrderProcessor::TopOfBookChanged(Order* order){
    std::cout <<"B "<< getSide(order->side)<< " " << order->price<< " " << order->qty << endl;
}
void OrderProcessor::OrderRejected(Order* order){
    std::cout << "R"  << " " << order->userID << " " << order->orderID << endl;
}
void OrderProcessor::Trade(Order* buyOrder, Order* sellOrder){
    std::cout << "T " << buyOrder->userID << " " << buyOrder->orderID << " " << sellOrder->userID << " " << sellOrder->orderID << " " << buyOrder->price << " " << buyOrder->qty << endl;
}
