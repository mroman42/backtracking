# Backtracking.
# makefile

BIN=./bin
SRC=./src
TEX=./tex
FLAGS=-std=c++11 -Wall -g


# make all: Compilar todos los programas
all: $(patsubst $(SRC)/%.cpp, $(BIN)/%, $(wildcard $(SRC)/*.cpp)) $(BIN)/mochila_bbound $(BIN)/tsp_bbound $(BIN)/tsp_optbound $(BIN)/planificacion_bbound $(BIN)/3matching_bbound

# Opciones individuales
$(BIN)/%: $(SRC)/%.cpp
	g++ $< -o $@ $(FLAGS)

$(BIN)/mochila_bbound: $(SRC)/mochila.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/tsp_bbound: $(SRC)/tsp.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/tsp_optbound: $(SRC)/tsp.cpp
	g++ $< -o $@ $(FLAGS) -DOPTBOUND -DBBOUND

$(BIN)/tsp_pq_bbound: $(SRC)/tsp_pq.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/tsp_pq_optbound: $(SRC)/tsp_pq.cpp
	g++ $< -o $@ $(FLAGS) -DOPTBOUND -DBBOUND

$(BIN)/planificacion_bbound: $(SRC)/planificacion.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/3matching_bbound: $(SRC)/3matching.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

$(BIN)/qap_bbound: $(SRC)/qap.cpp
	g++ $< -o $@ $(FLAGS) -DBBOUND

# Archivos .tex
.PHONY: tex

tex:
	./gentex.sh


# Limpieza de los ejecutables
clean:
	rm $(BIN)/*

cleanall: clean
	rm *.jpg *.dat tex/*
