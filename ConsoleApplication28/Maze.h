#include"pch.h"
#include <iostream>
#include<fstream>
#include"LinkedStack.h"

using namespace std;
class Maze {
private:

	int row;    //미로의 행
	int col;    //미로의 열
	char **map;    //미로 맵
	LinkedStack jcStack;
	Location2D exit;     //미로의 출구	
	Stack stack1;
	Stack stack2;
public:
	Maze() {
		init(0, 0);
	}
	void init(int w, int h)   //map 이차원 배열을 동적으로 할당
	{
		map = new char*[h];
		for (int i = 0; i < h; i++)
			map[i] = new char[w];
	}
	void reset()    //미로 맵 maze를 동적으로 해제
	{
		for (int i = 0; i < col; i++)
			delete[]map[i];
		delete[]map;
	}
	void load(const char *fname) //미로 파일을 읽어옴
	{
		int s = 1;
		char c;
		char temp;
		row = 1;
		col = 0;
		FILE* fp;

		fp = fopen(fname, "r");
		if (fp == NULL)
			cout << "Error: 파일이 존재하지 않습니다" << endl;
		while ((c = getc(fp)) != EOF) {
			col++;
			if (c == '\n') { row++; }
		}
		col = col / row;

		fclose(fp);

		init(col, row);   //row행 col열 2차원 배열을 생성
		ifstream fin(fname, ios::in);    //fname파일을 읽어들임

		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)

			{
				fin >> temp;    //0행0열부터row-1행col-1열까지 읽은 것을 순서대로 temp에저장
				map[i][j] = temp;     //0행0열부터row-1행col-1열까지 읽은 것을 순서대로 map에저장
				//출발점과 도착점을 구분하기위해 s라는 int형 변수를 두어서 그 값이 1이면 출발점 2면 도착점으로 설정했다. 
				//출발점을 찾았을경우 s를 +1 해주어서 다음 만나는 벽쪽에있는 0은 무조건 출발점이된다.
				if (map[i][j] == '0'&&s == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))   //출발점의 좌표일 경우
				{
					Location2D entry(i, j);
					stack1.push(entry);    //출발점을 스택에 쌓는
					printf("                                               <출발점: (%d, %d)>", entry.getRow(), entry.getCol());
					s++;
					map[i][j] = '3';    //출발점은 이미 지나온 길들과 구분하기 위해 값을 '3'으로 바꿔놓는다.
					printf("\n");
				}
				else if (map[i][j] == '0'&& s == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))    //도착점의 좌표일 경우
				{
					exit.setCol(j);
					exit.setRow(i);
					printf("                                               <도착점: (%d, %d)>", exit.getRow(), exit.getCol());
					map[i][j] = '9';
				}
			}
			
		}
		fin.close();
	}

	bool isValidLoc(int r, int c)
	{
		if (r < 0 || c < 0 || r >= row || c >= col) //범위를 벗어나면 갈 수 없다
			return false;
		else
			return (map[r][c] == '0' || map[r][c] == '9');   //비어있는 통로나 도착지점일 때만 true
	}

	void print() //현재 Maze를 화면에 출력
	{
		int s = 1;
		cout << "\n--------전체 미로의 크기---------  " << endl << "--------------"<<row << " *" << col<< "-------------" << endl;
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				//출발점은 항상 미로의 벽에 있어야하고 '0'이어야 한다. 그런데 도착점도 같은 조건이기 때문에 그 둘을 구분하기위해 int형 변수 s를 생성해서 s가1이면 출발점 2면 도착점으로한다.
				//맨처음 벽에있는 0을 만나면 그것을 출발점으로 설정하고 s를 1증가시킨다.
				if (map[i][j] == '0' && s == 1 && (i == 0 || j == 0 || i == row - 1 || j == col - 1)) //출발점
				{
					cout << "○";
					s++;
				}
				//미로가 갈 수 있는 길은 무조건 벽 안쪽에 있다.
				else if (map[i][j] == '0' && ((i != 0 && i != row - 1) && (j != 0 && j != col - 1)))  //갈 수 있는길
				{
					cout << "  ";
				}
				//출발점을 이미 찾은 상태라면 s의 값은2가 되어있을 것이다. 따라서 s가 2인 상태에서 만나는 벽에있는 '0'은 벽에 있는 두번째 '0'이라는 뜻이고 그것이 도착점이 된다.
				else if (map[i][j] == '0'&& s == 2 && (i == 0 || j == 0 || i == row - 1 || j == col - 1))  //도착점
				{

					cout << "◎";
				}
				else if (map[i][j] == '1')
				{
					cout << "■";
				}
				else if (map[i][j] == '7')
				{
					cout << "＊"; //지나온 길
				}
				else if (map[i][j] == '3') {
					cout << "○";
				}
				else if (map[i][j] == '9')
				{
					cout << "◎";
				}
				else if (map[i][j] == '5') {
					cout << "☆";
				}
				

			}
			cout << endl;

		}
	}


		void searchExit()        //실제 미로를 탐색하는 함수
		{
			FILE *writeMaze;    //미로의 경로를 txt파일에 출력할 파일변수 선언
			writeMaze = fopen("print.txt", "w");  //파일을 쓰기모드로 연다
			fprintf(writeMaze, "<DFS탐색으로 미로 탈출>\n");
			fprintf(writeMaze, "<분기점을 만나면 그 때 까지 경로를 출력합니다.>\n");
			int count = 0;

			while (!stack1.isEmpty())     //스택이 비어있지 않는 동안
			{
				
				Location2D here = stack1.pop();  //stack에 들어가있는 최상단요소를 here에 pop()시킨다. 
				stack2.push(here);    //그리고 그 here을 stack2에 push() stack2에는 마지막으로 간 경로가 최상위에 push()된다.
				int r = here.getRow();
				int c = here.getCol();
				if (map[r][c] != '3'&&map[r][c] != '9')map[r][c] = '7';//stack2의 최상단 요소가 출발점과 도착점이 아니라면 지나온 길로 표시한다.

				if (exit.getRow() == r && exit.getCol() == c)     //도착점이라면
				{
					while (!stack2.isEmpty()) {    //stack2의 요소들을 전부다 jcStack (연결리스트를 이용한스택)에 push()한다. 그러면 staka2에 쌓였던 것에 역순으로 jcStack에 쌓이게 된다.
												   // 이것은 경로를 왔던 순서대로 출력하게 해준다.
						Node *n = new Node(stack2.peek().getRow(), stack2.peek().getCol());
						jcStack.push(n);
						stack2.pop();

					}
					while (!jcStack.isEmpty()) {    //jcStack에 요소가 없을 때까지
						printf("(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());    //jcStack의 최상단 요소를 출력
						fprintf(writeMaze, "(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());//jcStack의 최상단 요소를 txt파일에출력
						jcStack.pop();    //다음 요소를 출력하기 위해 pop()
					}
					fprintf(writeMaze, "\n");
					fclose(writeMaze);
					printf("\n-------------도착!---------------");
					return;
				}
				//위에서 초기화 한 stack2의 최상단 요소의 행과 열r 과 c로 조건을 만들었는데 (r,c)주변에 갈 곳이있으면 그 갈 수 있는 곳을
				//stack에 push()하고 count를 +1해준다. 그런데 탐색 순서가 북 서 남 동 이기때문에 만약 북, 서, 남, 동 모든곳 다 갈 수 있다면
				// (r,c)는 분기점이 되고 stack 에는 최상단요소로 서쪽이 push()된다. 따라서 서쪽방향 먼저 탐색 하게 된다.
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

					//count가 2보다 크거나 같으면 (r,c)주변에 갈 수 있는곳이 2곳 이상이라는 뜻이므로 분기점이 된다.
					if (count >= 2) {
						map[r][c] = '5';//분기점은 '5'로 설정해서 다른 경로들과 차별을 둔다.
						while (!stack2.isEmpty()) {    //분기점을 만나면 stack2에 쌓였던 요소들을 jcStack에 pop()해서 담는다.
							Node *n = new Node(stack2.peek().getRow(), stack2.peek().getCol());
							jcStack.push(n);
							stack2.pop();
						}
						
						while (!jcStack.isEmpty()) {    //stack2의 요소들을 다 jcStack에 담았다면 이제 jcStack의 요소들을 출력한다.
							if (map[jcStack.peek()->getRow()][jcStack.peek()->getCol()] == '3') {
								printf("-------------출발!---------------\n");
								printf("<분기점을 만나면 그 곳 까지 경로를 출력합니다.>\n");
							}
							printf("(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());    //jcStack에는 stack2에 쌓였던 것에 역순으로 쌓여있기 때문에 처음 출발 했던 곳부터 출력된다.
							fprintf(writeMaze, "(%d, %d)", jcStack.peek()->getRow(), jcStack.peek()->getCol());  //txt파일에도 똑같이 출력한다.
							jcStack.pop();
						}
						printf("<☆>");
						fprintf(writeMaze, "\n");
						printf("\n");
					}
					count = 0;
				}


			}
		}
		void dfsMaze() {
			printf("---------------------------------\n");
			printf("---------------------------------               [이웃 위치 탐색 순서]\n");
			printf("---------------------------------                      ①↑\n");
			printf("---------------------------------                    ②←  →④\n");
			printf("------DFS으로 미로 탈출하기------                        ↓③\n");
			printf("---------------------------------\n");
			printf("---------------------------------\n");
		}
	
};
