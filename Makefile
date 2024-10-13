CC = g++
CXXFLAGS = -std=c++17 -o 
OBJ0 = main
OBJ1 = input/PDAInput
OBJ2 = structure/PDA
OBJ3 = structure/PDAStack
OBJ4 = structure/state
OBJ5 = structure/symbol

all: clean ${OBJ0}

${OBJ0}:
	${CC} ${CXXFLAGS} $@ src/$@.cpp src/${OBJ1}.cpp src/${OBJ2}.cpp src/${OBJ3}.cpp src/${OBJ4}.cpp src/${OBJ5}.cpp

clean:
	rm -f ${OBJ0}
