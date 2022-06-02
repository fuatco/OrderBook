FROM cpp-build-base:0.1.0 AS build
WORKDIR /src
COPY CMakeLists.txt main.cpp Common.h OrderManager.hpp OrderManager.cpp OrderProcessor.cpp OrderProcessor.hpp csv.h input.csv CsvDataReader.hpp CsvDataReader.cpp test.cpp ./

RUN cmake .
RUN make
RUN make test
FROM ubuntu:bionic
WORKDIR /opt/OrderBook

COPY --from=build /src/OrderBook ./
COPY --from=build /src/input.csv /root/data/
CMD ["./OrderBook"]
