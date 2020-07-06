#include"pch.h"
#include <iostream>
#include<fstream>
#include"LinkedStack.h"

using namespace std;
class Maze {
private:

	int row;    //�̷��� ��
	int col;    //�̷��� ��
	char **map;    //�̷� ��
	LinkedStack jcStack;
	Location2D exit;     //�̷��� �ⱸ	
	Stack stack1;
	Stack stack2;
public:
	Maze() {
		init(0, 0);
	}
	void init(int w, int h)   //map ������ �迭�� �������� �Ҵ�
	{
		map = new char*[h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}
	void reset()    //�̷� �� maze�� �������� ����
	{
		for (int i = 0; i < col; i++)
			delete[]map[i];
		delete[]map;
	}
	void load(const char *fname) //�̷� ������ �о��
	{
		int s = 1;
		char c;
		char temp;
		row = 1;
		col = 0;
		FILE* fp;

		fp = fopen(fname, "r");
		if (fp == NULL)
			cout << "Error: ������ �������� �ʽ��ϴ�" << endl;
		while ((c = getc(fp)) != EOF) {
			col++;
			if (c == '\n') { row++; }
		}
		col = col / row;

		fclose(fp);

		init(col, row);   //row�� col�� 2���� �迭�� ����
		ifstream fin(fname, ios::in);    //fname������ �о����

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)

			{
				fin >> temp;    //0��0������row-1��col-1������ ���� ���� ������� temp������
				map[i][j] = temp;     //0��0������row-1��col-1������ ���� ���� ������� map������
				//������� �������� �����ϱ����� s��� int�� ������ �ξ �� ���� 1�̸� ����� 2�� ���������� �����ߴ�. 
				//������� ã������� s�� +1 ���־ ���� ������ ���ʿ��ִ� 0�� ������ ������̵ȴ�.
				if (map[i][j] == '0'&&s == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))   //������� ��ǥ�� ���
				{
					Location2D entry(i, j);
					stack1.push(entry);    //������� ���ÿ� �״�
					printf("                                               <�����: (%d, %d)>", entry.getRow(), entry.getCol());
					s++;
					map[i][j] = '3';    //������� �̹� ������ ���� �����ϱ� ���� ���� '3'���� �ٲ���´�.
					printf("\n");
				}
				else if (map[i][j] == '0'&& s == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))    //�������� ��ǥ�� ���
				{
					exit.setCol(j);
					exit.setRow(i);
					printf("                                               <������: (%d, %d)>", exit.getRow(), exit.getCol());
					map[i][j] = '9';
				}
			}
			
		}
		fin.close();
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= row || c >= col) //������ ����� �� �� ����
			return false;
		else
			return (map[r][c] == '0' || map[r][c] == '9');   //����ִ� ��γ� ���������� ���� true
	}

	void print() //���� Maze�� ȭ�鿡 ���
	{
		int s = 1;
		cout << "\n--------��ü �̷��� ũ��---------  " << endl << "--------------"<<row << " *" << col<< "-------------" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//������� �׻� �̷��� ���� �־���ϰ� '0'�̾�� �Ѵ�. �׷��� �������� ���� �����̱� ������ �� ���� �����ϱ����� int�� ���� s�� �����ؼ� s��1�̸� ����� 2�� �����������Ѵ�.
				//��ó�� �����ִ� 0�� ������ �װ��� ��������� �����ϰ� s�� 1������Ų��.
				if (map[i][j] == '0' && s == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1)) //�����
				{
					cout << "��";
					s++;
				}
				//�̷ΰ� �� �� �ִ� ���� ������ �� ���ʿ� �ִ�.
				else if (map[i][j] == '0' && ((i != 0 && i != row - 1) && (j != 0 && j != col - 1)))  //�� �� �ִ±�
				{
					cout << "  ";
				}
				//������� �̹� ã�� ���¶�� s�� ����2�� �Ǿ����� ���̴�. ���� s�� 2�� ���¿��� ������ �����ִ� '0'�� ���� �ִ� �ι�° '0'�̶�� ���̰� �װ��� �������� �ȴ�.
				else if (map[i][j] == '0'&& s == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))  //������
				{

					cout << "��";
				}
				else if (map[i][j] == '1')
				{
					cout << "��";
				}
				else if (map[i][j] == '7')
				{
					cout << "��"; //������ ��
				}
				else if (map[i][j] == '3') {
					cout << "��";
				}
				else if (map[i][j] == '9')
				{
					cout << "��";
				}
				else if (map[i][j] == '5') {
					cout << "��";
				}
				

			}
			cout << endl;

		}
	}


		void searchExit()        //���� �̷θ� Ž���ϴ� �Լ�
		{
			FILE *writeMaze;    //�̷��� ��θ� txt���Ͽ� ����� ���Ϻ��� ����
			writeMaze = fopen("print.txt", "w");  //������ ������� ����
			fprintf(writeMaze, "<DFSŽ������ �̷� Ż��>\n");
			fprintf(writeMaze, "<�б����� ������ �� �� ���� ��θ� ����մϴ�.>\n");
			int count = 0;

			while (!stack1.isEmpty())     //������ ������� �ʴ� ����
			{
				
				Location2D here = stack1.pop();  //stack�� ���ִ� �ֻ�ܿ�Ҹ� here�� pop()��Ų��. 
				stack2.push(here);    //�׸��� �� here�� stack2�� push() stack2���� ���������� �� ��ΰ� �ֻ����� push()�ȴ�.
				int r = here.getRow();
				int c = here.getCol();
				if (map[r][c] != '3'&&map[r][c] != '9')map[r][c] = '7';//stack2�� �ֻ�� ��Ұ� ������� �������� �ƴ϶�� ������ ��� ǥ���Ѵ�.

				if (exit.getRow() == r && exit.getCol() == c)     //�������̶��
				{
					while (!stack2.isEmpty()) {    //stack2�� ��ҵ��� ���δ� jcStack (���Ḯ��Ʈ�� �̿��ѽ���)�� push()�Ѵ�. �׷��� staka2�� �׿��� �Ϳ� �������� jcStack�� ���̰� �ȴ�.
												   // �̰��� ��θ� �Դ� ������� ����ϰ� ���ش�.
						Node *n = new Node(stack2.peek().getRow(), stack2.peek().getCol());
						jcStack.push(n);
						stack2.pop();

					}
					while (!jcStack.isEmpty()) {    //jcStack�� ��Ұ� ���� ������
						printf("(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());    //jcStack�� �ֻ�� ��Ҹ� ���
						fprintf(writeMaze, "(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());//jcStack�� �ֻ�� ��Ҹ� txt���Ͽ����
						jcStack.pop();    //���� ��Ҹ� ����ϱ� ���� pop()
					}
					fprintf(writeMaze, "\n");
					fclose(writeMaze);
					printf("\n-------------����!---------------");
					return;
				}
				//������ �ʱ�ȭ �� stack2�� �ֻ�� ����� ��� ��r �� c�� ������ ������µ� (r,c)�ֺ��� �� ���������� �� �� �� �ִ� ����
				//stack�� push()�ϰ� count�� +1���ش�. �׷��� Ž�� ������ �� �� �� �� �̱⶧���� ���� ��, ��, ��, �� ���� �� �� �� �ִٸ�
				// (r,c)�� �б����� �ǰ� stack ���� �ֻ�ܿ�ҷ� ������ push()�ȴ�. ���� ���ʹ��� ���� Ž�� �ϰ� �ȴ�.
				else
				{
					if (isValidLoc(r - 1, c))
					{

						stack1.push(Location2D(r - 1, c));
						count++;	
					}
					if (isValidLoc(r, c - 1))
					{
						stack1.push(Location2D(r, c - 1));
						count++;
					}

					if (isValidLoc(r + 1, c))
					{

						stack1.push(Location2D(r + 1, c));
						count++;
					}


					if (isValidLoc(r, c + 1))
					{
						stack1.push(Location2D(r, c + 1));
						count++;
					}

					//count�� 2���� ũ�ų� ������ (r,c)�ֺ��� �� �� �ִ°��� 2�� �̻��̶�� ���̹Ƿ� �б����� �ȴ�.
					if (count >= 2) {
						map[r][c] = '5';//�б����� '5'�� �����ؼ� �ٸ� ��ε�� ������ �д�.
						while (!stack2.isEmpty()) {    //�б����� ������ stack2�� �׿��� ��ҵ��� jcStack�� pop()�ؼ� ��´�.
							Node *n = new Node(stack2.peek().getRow(), stack2.peek().getCol());
							jcStack.push(n);
							stack2.pop();
						}
						
						while (!jcStack.isEmpty()) {    //stack2�� ��ҵ��� �� jcStack�� ��Ҵٸ� ���� jcStack�� ��ҵ��� ����Ѵ�.
							if (map[jcStack.peek()->getRow()][jcStack.peek()->getCol()] == '3') {
								printf("-------------���!---------------\n");
								printf("<�б����� ������ �� �� ���� ��θ� ����մϴ�.>\n");
							}
							printf("(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());    //jcStack���� stack2�� �׿��� �Ϳ� �������� �׿��ֱ� ������ ó�� ��� �ߴ� ������ ��µȴ�.
							fprintf(writeMaze, "(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());  //txt���Ͽ��� �Ȱ��� ����Ѵ�.
							jcStack.pop();
						}
						printf("<��>");
						fprintf(writeMaze, "\n");
						printf("\n");
					}
					count = 0;
				}


			}
		}
		void dfsMaze() {
			printf("---------------------------------\n");
			printf("---------------------------------               [�̿� ��ġ Ž�� ����]\n");
			printf("---------------------------------                      ���\n");
			printf("---------------------------------                    ���  ���\n");
			printf("------DFS���� �̷� Ż���ϱ�------                        ���\n");
			printf("---------------------------------\n");
			printf("---------------------------------\n");
		}
	
};
