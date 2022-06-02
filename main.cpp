#include "csv.h"
#include "Common.h"
#include "CsvDataReader.hpp"
#include "OrderManager.hpp"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
using namespace std;



int main(int argc, const char * argv[]) {
    std::string fileName = fs::current_path().root_path().string() + "root/data/input.csv";
    CsvDataReader reader(fileName);
    auto trades = reader.GetTrades();
    
    OrderProcessor processor;
    OrderManager manager(trades, processor);
    manager.PublishBook();
    
    return 0;
}
