CONFIG = $(shell pkg-config gtkmm-3.0 --cflags --libs | sed 's/ -I/ -isystem /g')
CXX := g++
SOURCES := window.cpp main.cpp splash.cpp aldos-broder.cpp fusion.cpp
all:
	$(CXX) -std=c++11 $(SOURCES) $(CONFIG) -o Maze -v

