CONFIG = $(shell pkg-config gtkmm-3.0 --cflags --libs | sed 's/ -I/ -isystem /g')
CXX := g++

all:
	$(CXX) -std=c++11 window.cpp main.cpp $(CONFIG) -o Maze -v

