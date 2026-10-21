.PHONY: all debug release clean

CXX = g++
CXXFLAGS_DEBUG = -g -O0 -Wall
CXXFLAGS_RELEASE = -O2 -Wall -DNDEBUG
TARGET_DEBUG = modAlphaCipher-dbg
TARGET_RELEASE = modAlphaCipher
SOURCES = main.cpp modAlphaCipher.cpp

all: debug release

debug: $(TARGET_DEBUG)

release: $(TARGET_RELEASE)

$(TARGET_DEBUG): $(SOURCES)
	$(CXX) $(CXXFLAGS_DEBUG) $(SOURCES) -o $(TARGET_DEBUG)

$(TARGET_RELEASE): $(SOURCES)
	$(CXX) $(CXXFLAGS_RELEASE) $(SOURCES) -o $(TARGET_RELEASE)

clean:
	rm -f $(TARGET_DEBUG) $(TARGET_RELEASE)
