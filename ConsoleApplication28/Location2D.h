#include<cstdio>
#include<iostream>
using namespace std;
class Location2D {
protected:
	int row;    //За
	int col;    //ї­
public:
	Location2D(int r=0, int c=0) { row = r , col = c; }
	int getRow() { return row; }
	int getCol() { return col; }
	void setRow(int i) { row = i; }
	void setCol(int i) { col = i; }
	bool isNeighbor(Location2D &p) {
		return ((row == p.row && (col == p.col - 1 || col == p.col + 1))
			|| (col == p.col && (row == p.row - 1 || row == p.row + 1)));
	}
	bool operator==(Location2D&p) { return row == p.row && col == p.col; }
	void display() {
		cout<< "("<<row<<","<< col<<")";
	}
};
