CXX=g++
CFLAGS = -g -Wall

LIB_DIR = -Llib
INC_DIR = -Iinclude

CODE_FILE = conway.cpp

LD_LIBS = -lpdcurses

EXE_DIR = -o $(CODE_FILE:.cpp=.exe)

$(CODE_FILE:.cpp=):
	$(CXX) $(EXE_DIR) $(CFLAGS) $(CODE_FILE) $(LIB_DIR) $(INC_DIR) $(LD_LIBS)
