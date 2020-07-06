#include<cstdlib>
#include "Location2D.h"
inline void error(const char *str) {
	printf("%s", str);
	exit(1);
}
#define MAX_STACK_SIZE 100
class Stack {
	int top;
	Location2D data[MAX_STACK_SIZE];
public:
	Stack() { top = -1; }
	bool isEmpty() { return top == -1; }
	bool isFull() { return top + 1 == MAX_STACK_SIZE; }

	void push(Location2D n) {
		if (isFull()) error("스택 포화상태");
		else {
			data[++top] = n;
		}
	}
	Location2D pop() {
		if (isEmpty()) return NULL;
		return data[top--];
	}
	Location2D peek() {
		if (isEmpty()) return NULL;
		return data[top];
	}
	int getTop() { return top; }
	void setTop(int t) { top = t; }
};
//Node는 Location2D를 상속 받는다
class Node :public Location2D {
	Node*link;
public:
	Node(int x, int y) :Location2D(x, y) { link = NULL; }    //Location2D를 상속 받았기 때문에 Node는 객체 생성 시 x,y(즉, 행,열)값을 초기화 할 수 있다.
	~Node(void) {}
	Node*getLink() { return link; }
	void setLink(Node*p) { link = p; }

};
