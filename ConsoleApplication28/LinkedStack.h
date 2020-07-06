#include"Stack.h"
class LinkedStack {
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() { while (!isEmpty())delete pop(); }
	bool isEmpty() { return top == NULL; }
	void setTop(Node*t) { top = t; }
	Node* getTop() {  return top; }
	void push(Node*p) {    //연결리스트로 구현한 스택에서 좌표를 가진 노드를 push()할 수 있게 하기위해서 Node가 Location2D를 상속받게함.
		if (isEmpty())top = p;
		else {
			p->setLink(top);
			top = p;
		}
	}
	Node*pop() {
		if (isEmpty())return NULL;
		Node*p = top;
		top = top->getLink();
		return p;
	}
	Node*peek() { return top; }
	void display() {
		cout << "[LinkedStack]" << endl;
		for (Node*p = top; p != NULL; p = p->getLink())
			p->display();
		cout << endl;
	}
};