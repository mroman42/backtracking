# Backtracking.
# makefile

BIN=./bin
SRC=./src
FLAGS=-std=c++11 -Wall


# make all: Compilar todos los programas 
all: $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(wildcard $(SRC)/*.cpp))

# Opciones individuales 
$(BIN)/%: $(SRC)/%.cpp
	g++ $< -o $@ $(FLAGS)


# Limpieza de los ejecutables
clean:
	rm $(BIN)/*

cleanall: clean
	rm *.jpg *.dat tex/*
