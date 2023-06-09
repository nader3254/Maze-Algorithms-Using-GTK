all:
	  g++ -std=c++11 window.cpp main.cpp $(pkg-config gtkmm-3.0 --cflags --libs | sed 's/ -I/ -isystem /g') -o Maze -v
