CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SOURCES = main.cpp transpositionCipher.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = test_transpositionCipher

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) /usr/lib/x86_64-linux-gnu/libUnitTest++.so

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean test
