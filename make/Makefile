#compiler
GCC = g++
#compiler flags
CFLAG = -g -Wall
#output file
LFLAGS = -o
#binary file directory
BIN = ../bin
#source file directory
SRC = ../src
#include file directory
INC = ../inc
#object file directory

IFLAGS = -I $(INC)

OBJ = ../obj
#valgrind report
CVFLAGS = -v --tool=memcheck --leak-check=full --show-reachable=yes --log-file=valclient

#compile all source file

all: clean buildServer buildClient

buildServer: $(OBJ)/server.o 
	$(GCC) $(IFLAGS) $(CFLAG) $(LFLAGS) $(BIN)/server $(OBJ)/server.o  $(SRC)/server.cpp

buildClient: $(OBJ)/client.o
	$(GCC) $(IFLAGS) $(CFLAG) $(LFLAGS) $(BIN)/client $(OBJ)/client.o $(SRC)/client.cpp

$(OBJ)/server.o: $(SRC)/server.cpp
	$(GCC) $(IFLAGS) $(CFLAG) -c  $(LFLAGS) $(OBJ)/server.o $(SRC)/serverfunc.cpp

$(OBJ)/client.o: $(SRC)/client.cpp
	$(GCC) $(IFLAGS) $(CFLAG) -c $(LFLAGS) $(OBJ)/client.o $(SRC)/clientfunc.cpp


#run server
server:
	./bin/server

client:
	./bin/client

clean:
	rm $(BIN)/server $(BIN)/client $(OBJ)/server.o $(OBJ)/client.o
