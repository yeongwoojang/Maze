#include "pch.h"
#include <iostream>
#include "Maze.h"
using namespace std;


int main()
{
	Maze maze; //미로 탐색 객체 생성
	maze.load("maze.txt");
	maze.print();
	maze.dfsMaze();
    maze.searchExit();
	//미로를 탐색해 출구를 찾음
	maze.print();
	return 0;

}
