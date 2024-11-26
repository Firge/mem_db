CXX = g++
CXXFLAGS = -std=c++17 -Wall -I.

TARGET = database_test

SRCS = Database.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS) test_main.o
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) test_main.o -lgtest -lgtest_main -pthread

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) test_main.o
