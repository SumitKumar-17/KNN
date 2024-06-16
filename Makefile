CXX = g++
TARGET = TreeIndex.out
SRCS = run.cpp DataVector.cpp TreeIndex.cpp
OBJS = $(SRCS:.cpp=.o)
CXXFLAGS = -Wall -O2

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: run
run: $(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET) $(OBJS)
