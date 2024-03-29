# Backtracking.
# makefile

BIN=./bin
SRC=./src
TEX=./tex
FLAGS=-std=c++11 -Wall -g


# make all: Compilar todos los programas
all: $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(wildcard $(SRC)/*.cpp)) $(BIN)/mochila_bbound $(BIN)/tsp_bb_opt $(BIN)/planificacion_bbound $(BIN)/3matching_bbound $(BIN)/qap_bbound1 $(BIN)/qap_bbound2 $(BIN)/qap_bbound3

# Opciones individuales
$(BIN)/%: $(SRC)/%.cpp
	g++ $< -o $@ $(FLAGS)

$(BIN)/mochila_bbound: $(SRC)/mochila.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/tsp_bb_opt: $(SRC)/tsp_bb.cpp
	g++ $< -o $@ $(FLAGS) -DOPTBOUND

$(BIN)/planificacion_bbound: $(SRC)/planificacion.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/3matching_bbound: $(SRC)/3matching.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/qap_bbound1: $(SRC)/qap.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND1

$(BIN)/qap_bbound2: $(SRC)/qap.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND2

$(BIN)/qap_bbound3: $(SRC)/qap.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND3

# Archivos .tex
.PHONY: all clean cleanall


# Limpieza de los ejecutables
clean:
	rm $(BIN)/*

cleanall: clean
	rm *.jpg *.dat tex/*
