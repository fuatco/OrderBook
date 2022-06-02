#include "OrderManager.hpp"

OrderManager::OrderManager(std::queue<Order*> o, OrderProcessor p){
    orders = o;
    processor = p;
}


void OrderManager::PublishBook(){
    while (!orders.empty()) {
        auto order = std::move(orders.front());
        orders.pop();
        if(!validateOrder(order)){
            processor.OrderRejected(order);
            continue;
        }
        
        switch (order->action) {
            case NEW:{
                addNewOrder(order);
                break;
            }
            case CANCEL:{
                 if(!orderExists(order)){
                     processor.OrderRejected(order);
                 }
                 cancelOrder(order);
                break;
            }
            case FLUSH:{
                //TODO
                break;
            }
            default:{
                break;
            }
        }
    }
}



bool OrderManager::validateOrder(Order* order){
    // validations for invalid orders
    if(order->action == Action::NONE){
        return false;
    }
    if(order->symbol.size() == 0){
        return false;
    }
    if(order->side == OTHER){
        return false;
    }
    if(order->qty < 0){
        return false;
    }
    return true;
}
bool OrderManager::isTopOfSellBookChange(Order* order){
    if(sellTable.find(order->symbol) != sellTable.end() && !sellTable[order->symbol].empty()){
        auto top = *sellTable[order->symbol].begin();
        if(top->price >= order->price){
            return true;
        }
        return false;
    }
    return true;
}
bool OrderManager::isTopOfBuyBookChange(Order* order){
    if(buyTable.find(order->symbol) != buyTable.end() && !buyTable[order->symbol].empty()){
        auto top = *buyTable[order->symbol].begin();
        if(top->price <= order->price){
            return true;
        }
        return false;
    }
    return true;
}

Order* OrderManager::hasMathcingBuyOrder(Order* order){
    if(buyTable[order->symbol].empty()){
        return nullptr;
    }
    // market order
    if(order->price == 0){
        auto top = buyTable[order->symbol].begin();
        buyTable[order->symbol].erase(top);
        return *top;
    }
    if(buyTable.find(order->symbol) != buyTable.end()){
        auto buyOrders = buyTable[order->symbol];
        for(auto &buyOrder : buyOrders){
            if(buyOrder->price == order->price){
                if(buyOrder->qty <= order->qty){
                    buyOrder->qty = buyOrder->qty - order->qty;
                    if(buyOrder->qty == 0){
                        buyOrders.erase(buyOrder);
                    }
                    sellTable[order->symbol] = std::move(buyOrders);
                    return buyOrder;
                }

            }
        }
    }
    return nullptr;
}
Order* OrderManager::hasMathcingSellOrder(Order* order){
    if(sellTable[order->symbol].empty()){
        return nullptr;
    }
    // market order
    if(order->price == 0){
        auto top = sellTable[order->symbol].begin();
        sellTable[order->symbol].erase(top);
        return *top;
    }
    
    if(sellTable.find(order->symbol) != sellTable.end()){
        auto sellOrders = sellTable[order->symbol];
        for(auto &sellOrder : sellOrders){
            if(sellOrder->price == order->price){
                if(sellOrder->qty <= order->qty){
                    sellOrder->qty = sellOrder->qty - order->qty;
                    if(sellOrder->qty == 0){
                        sellOrders.erase(sellOrder);
                    }
                    sellTable[order->symbol] = std::move(sellOrders);
                    return sellOrder;
                }

            }
        }
    }
    return nullptr;
}
bool OrderManager::orderExists(Order* order){
    if(idTable.find(order->orderID) != idTable.end()){
        return true;
    }
    return false;
}
void OrderManager::insertBuyOrder(Order* order){
    idTable[order->orderID] = order->symbol;
    buyTable[order->symbol].insert(std::move(order));

}
void OrderManager::insertSellOrder(Order* order){
    idTable[order->orderID] = order->symbol;
    sellTable[order->symbol].insert(std::move(order));
}

void OrderManager::cancelOrder(Order* order){
    string symbol = idTable[order->orderID];
    idTable.erase(order->orderID);
    
    if(buyTable.find(symbol) != buyTable.end()){
        auto buyOrders = std::move(buyTable[symbol]);
        for(auto &buyOrder : buyOrders){
            if(buyOrder->orderID == order->orderID){
                buyOrders.erase(buyOrder);
                break;
            }
        }
        buyTable[symbol] = std::move(buyOrders);
    }
    
    if(sellTable.find(symbol) != sellTable.end()){
        auto sellOrders = std::move(sellTable[symbol]);
        for(auto &sellOrder : sellOrders){
            if(sellOrder->orderID == order->orderID){
                sellOrders.erase(sellOrder);
                
                break;
            }
        }
        sellTable[symbol] = std::move(sellOrders);
    }
}

void OrderManager::addNewOrder(Order* order){
    switch (order->side) {
        case BUY:{
            processor.NewOrder(order);
            auto matchingOrder =hasMathcingSellOrder(order);
            if(matchingOrder){
                processor.Trade(order, matchingOrder);
                if(!sellTable[order->symbol].empty()){
                    auto top = *sellTable[order->symbol].begin();
                    processor.TopOfBookChanged(top);
                }
            }else {
                if(isTopOfBuyBookChange(order)){
                    processor.TopOfBookChanged(order);
                }
                insertBuyOrder(order);
            }
            break;
        }
        case SELL:{
            processor.NewOrder(order);
            auto matchingBuyOrder = hasMathcingBuyOrder(order);
            if(matchingBuyOrder){
                processor.Trade(matchingBuyOrder, order);
                if(!buyTable[order->symbol].empty()){
                    auto top = *buyTable[order->symbol].begin();
                    processor.TopOfBookChanged(top);
                }
            } else {
                if(isTopOfSellBookChange(order)){
                    processor.TopOfBookChanged(order);
                }
                insertSellOrder(order);
            }
            break;
        }
        default:{
            break;
        }
    }
}
