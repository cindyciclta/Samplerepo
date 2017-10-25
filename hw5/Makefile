CXX = g++
CXXFLAGS = -g -Wall -std=c++11
BIN_DIR = bin

all: hw5

hw5: hw5.cpp ArithmeticExpression.o BooleanExpression.o Command.o In.o exception.o
	g++ $(CXXFLAGS) ArithmeticExpression.o BooleanExpression.o Command.o In.o hw5.cpp exception.cpp -o hw5

Command.o: Command.h Command.cpp
	g++ $(CXXFLAGS) -c Command.cpp -o Command.o

ArithmeticExpression.o: ArithmeticExpression.h ArithmeticExpression.cpp
	g++ $(CXXFLAGS) -c ArithmeticExpression.cpp -o ArithmeticExpression.o

BooleanExpression.o: BooleanExpression.h BooleanExpression.cpp
	g++ $(CXXFLAGS) -c BooleanExpression.cpp -o BooleanExpression.o

In.o: In.h In.cpp
	g++ $(CXXFLAGS) -c In.cpp -o In.o

exception.o: exception.h exception.cpp
	g++ $(CXXFLAGS) -c exception.cpp -o exception.o

clean:
	rm -rf $(BIN_DIR)
$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp
