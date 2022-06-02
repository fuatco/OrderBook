# OrderBook

# To run the program in docker container
 docker build -t orderBook .
 docker run orderBook
 
# Input data
  Input.csv contains the scenario that the program will run
  Feel free to add different scenarios or add more orders
  After modifying the input.csv please make sure you rebuild and run the container
  
  
  
 # Program documentation 
  CsvDataReader - parses the CSV file and creates an order from each row, orders with invalid fields will be rejected, Queue data structuse is used to store the orders. 
    FIFO is needed here to process the orders in the right order
  OrderManager - Uses hashtable for buy/sell orders, tables are updated every time there is match or top of book changed, time complexities O(1) and space complexity O(n)
  OrderProcessor - Class to output the results, methods are virtual so can be overrided for unit testing
  csv.h - 3rd party csv file reader
  


# Improvements 
- Currently data is read only from CSV file, there can be configuration for different formats
- Unit testing, unfortunatelly ran out of time so unit tests can be added for OrderManger class
- Currently the program works only with a single file, make it dynamic to process files in a directory or keep pooling from a path to process files
