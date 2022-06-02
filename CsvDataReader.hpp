//
//  CsvDataReader.hpp
//  KrakenOrderBook
//
//  Created by fuat co on 02/06/2022.
//

#ifndef CsvDataReader_hpp
#define CsvDataReader_hpp

#include "Common.h"

using namespace  std;

class CsvDataReader {
private:
    string source;
public:
    CsvDataReader(const std::string& fileName);
    std::queue<Order*> GetTrades();
};

#endif /* CsvDataReader_hpp */
