CXX:=g++
DEBUG_FLAG:= -g -O3
RELESE_FLAG:= -O3 -s -DNDEBUG
CURRENT_FLAGS:= $(RELESE_FLAG)
CURRENT_FLAGS += -std=c++11 -pthread -I../src -Wall -Wconversion -Wfatal-errors -Wextra
# BIN=./bin
BIN=../myBin

LIBS:= -lboost_system -lboost_thread -lboost_chrono
G_LIBS:= -lGL -lGLU -lglut -lGLEW -lSDL -lSDL2main -lSDL2

all:
	@echo "***********************************************"
	@echo Run one of the following commandline examples:
	@echo ""
	@echo make main
	@echo ""
	@echo "***********************************************"

main:
	@clear
	$(CXX) $(CURRENT_FLAGS) main.cc -o $(BIN)/main $(LIBS)
	@echo "--------------------------------"
	@echo "\tRUNNING PROGRAM"
	@echo "--------------------------------"
	$(BIN)/main
	@cat $(BIN)/main-result.txt