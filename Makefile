CXX      = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
TARGET   = library_system
SRCS     = src/main.cpp src/Book.cpp src/Member.cpp src/BorrowRecord.cpp src/Library.cpp

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

clean:
	del $(TARGET).exe 2>nul || rm -f $(TARGET)

.PHONY: all clean
