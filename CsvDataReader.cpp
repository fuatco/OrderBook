
#include "CsvDataReader.hpp"

CsvDataReader::CsvDataReader(const std::string& fileName){
    source = fileName;
}
std::queue<Order*> CsvDataReader::GetTrades(){
    std::queue<Order*> orders;
    io::CSVReader<7> in(source);
    in.read_header(io::ignore_extra_column, "action", "user(int)", "symbol(string)", "price(int)", "qty(int)", "side(char B or S)", "userOrderId(int)");
    std::string action;
    int userID;
    string symbol;
    int price;
    int qty;
    char side;
    int orderID;
    try {
        while(in.read_row(action, userID, symbol, price, qty, side, orderID)){
            orders.push(new Order(action, userID, symbol, price, qty, side, orderID));
        }
    } catch(std::exception exc){
       // TODO handle exception
    }
    return orders;
}
