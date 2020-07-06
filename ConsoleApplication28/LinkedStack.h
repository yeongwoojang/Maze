#include"Stack.h"
class LinkedStack {
	Node* top;
public:
	LinkedStack() { top = NULL; }
	~LinkedStack() { while (!isEmpty())delete pop(); }
	bool isEmpty() { return top == NULL; }
	void setTop(Node*t) { top = t; }
	Node* getTop() {  return top; }
	void push(Node*p) {    //���Ḯ��Ʈ�� ������ ���ÿ��� ��ǥ�� ���� ��带 push()�� �� �ְ� �ϱ����ؼ� Node�� Location2D�� ��ӹް���.
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