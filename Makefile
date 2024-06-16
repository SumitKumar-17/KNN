CXX = g++
CXXFLAGS = -Wall -O2

OUTPUT = TreeIndex.out
SOURCES = run.cpp DataVector.cpp TreeIndex.cpp

all: $(OUTPUT)
	./$(OUTPUT)

$(OUTPUT): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	rm -f $(OUTPUT)

.PHONY: all clean
