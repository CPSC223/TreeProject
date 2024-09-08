all: TreeProject

TreeProject: main.cpp linked_list.cpp linked_list.hpp
	g++ -g -Wall -std=c++11 main.cpp linked_list.cpp -o outputExecutable
	./outputExecutable