cmake_minimum_required(VERSION 2.8.9)
project (OrderBook)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES
   ${SOURCE}
   ${CMAKE_CURRENT_SOURCE_DIR}/CsvDataReader.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/CsvDataReader.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/csv.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Common.h
   ${CMAKE_CURRENT_SOURCE_DIR}/OrderManager.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/OrderManager.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/OrderProcessor.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/OrderProcessor.cpp

)
ENABLE_TESTING()

add_executable(OrderBook main.cpp ${SOURCE_FILES})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
target_link_libraries(OrderBook stdc++fs)
ADD_EXECUTABLE(OrderBook_Test test.cpp ${SOURCE_FILES})
ADD_TEST(tests OrderBook_Test)