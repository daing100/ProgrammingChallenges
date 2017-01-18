CXX=g++
CFLAGS=-g -Wall

LIB_DIR=-Llib
INC_DIR=-Iinclude

LDFLAGS=

CODEFILE=parser.cpp

EXE_DIR=-o $(CODEFILE:.cpp=.exe)

FLAGS=$(CFLAGS) $(LIB_DIR) $(INC_DIR) $(EXE_DIR)

$(CODEFILE:.cpp=):
	$(CXX) $(FLAGS) $(CODEFILE) $(LDFLAGS)
