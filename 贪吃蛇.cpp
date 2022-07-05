//#pragma warning(disable:4996)
#include <iostream>
#include <Windows.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "Snake_node.h"
#include "Food.h"

using namespace std;

Food *food;

list<Snake_node> s_list; 

string temp_dir;
string u_temp_dir;
string last_dir;
int last_x;
int last_y;
int velocity = 2;
int score = 0;

void Gotoxy(int x, int y) {
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

void Welcome(){
	for (int i = 0; i < 10; i++) {
		cout << endl;
	}
	cout << "\t\t\t\t";	
	for (int i = 0; i < 18; i++) {
		cout << "■";
	}	
	cout << endl;
	cout << "\t\t\t\t■\t\t\t\t  ■" << endl;
	cout << "\t\t\t\t■\t 欢迎来到贪吃蛇世界\t  ■" << endl;
	cout << "\t\t\t\t■\t\t\t\t  ■" << endl;
	cout << "\t\t\t\t";
	for (int i = 0; i < 18; i++) {
		cout << "■";
	}

	for (int i = 0; i < 6; i++) {
		cout << endl;
	}
	for (int i = 0; i < 40; i++) {
		cout << " ";
	}
	system("pause");
	system("cls"); 

}

void GameStart() {
	system("mode con cols=100 lines=35");
	Welcome();
}

//打印地图  
void CreatMap() {
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			if (i == 0 || i == 29) {
				cout << "■";
			}
			else {
				if (j == 0 || j == 29) {
					cout << "■";
				}
				else {
					cout << "  ";
				}
			}
		}
		cout << endl;
	} 

}

void textMap() {
	Gotoxy(64, 12);
	cout << "得分："<<score;
	Gotoxy(64, 13);
	cout << "一个食物得分为10分";
	Gotoxy(64, 16);
	cout << "不能穿墙，不能咬到自己";
	Gotoxy(64, 17);
	cout << "用↑、↓、←、→分别控制蛇的移动";
	Gotoxy(64, 19);
	cout << "F1:快速   F2:常速   F3:慢速";
	Gotoxy(64, 21);
	cout << "ESC:退出游戏   Space:暂停游戏";
}

//初始化蛇
void initSnake() {
	Snake_node *s0 = new Snake_node(20, 15,"L");
	s_list.push_back(*s0);
	Snake_node *s1 = new Snake_node(22, 15,"L");
	s_list.push_back(*s1);
	Snake_node *s2 = new Snake_node(24, 15,"L");
	s_list.push_back(*s2);
	Snake_node *s3 = new Snake_node(26, 15,"L");
	s_list.push_back(*s3);

	for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) {
		Gotoxy(it->s_x,it->s_y);
		if (it == s_list.begin()) {
			cout << "■";
		}
		else {
			cout << "□";
		}

	}
	
	
}

//刷新食物
void refreshFood() {
	int x, y;
	while (true) {
		int temp = 0;
		srand((unsigned)time(NULL));
		x = (rand() % (28)) + 1;
		y = (rand() % (28)) + 1;
		for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) {
			if (it->s_x == 2*x && it->s_y == y) {
				temp++;
			}
		}
		if (temp == 0) {
			break;
		}
	}

	food = new Food(2*x, y);
	Gotoxy(food->f_x, food->f_y);
	cout << "■";
}

void moveSnake() {	
	//擦除当前蛇
	for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) {
		Gotoxy(it->s_x, it->s_y);
	    cout << "  ";
	}
	
	//改变蛇各个节点的坐标位置
	for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) 
	{
		if (it == s_list.begin()) {
			if (it->s_direction == "L") {
				it->s_x -= 2; //向左位移一个单位	
			}
			else if (it->s_direction == "R") {
				it->s_x += 2; //向右位移一个单位
			}
			else if (it->s_direction == "U") {
				it->s_y -= 1; //向上位移一个单位
			}
			else if (it->s_direction == "D") {
				it->s_y += 1; //向下位移一个单位
			}
			temp_dir = it->s_direction;
			u_temp_dir = it->s_direction;
		}
		else {

			if (u_temp_dir != it->s_direction) {
				string T;
				T = u_temp_dir;
				if (it->s_direction == "L") {
					it->s_x -= 2; //向左位移一个单位	
				}
				else if (it->s_direction == "R") {
					it->s_x += 2; //向右位移一个单位
				}
				else if (it->s_direction == "U") {
					it->s_y -= 1; //向上位移一个单位
				}
				else if (it->s_direction == "D") {
					it->s_y += 1; //向下位移一个单位
				}
				u_temp_dir = it->s_direction;
				it->s_direction = T;
			}
			else {
				if (it->s_direction == "L") {
					it->s_x -= 2; //向左位移一个单位	
				}
				else if (it->s_direction == "R") {
					it->s_x += 2; //向右位移一个单位
				}
				else if (it->s_direction == "U") {
					it->s_y -= 1; //向上位移一个单位
				}
				else if (it->s_direction == "D") {
					it->s_y += 1; //向下位移一个单位
				}
			}

		}
		last_dir = it->s_direction;
		last_x = it->s_x;
		last_y = it->s_y;
	} 

	//判断头结点是否吃到食物
	if (s_list.begin()->s_x == food->f_x && s_list.begin()->s_y == food->f_y) {
		score += 10;
		Gotoxy(70, 12);
		cout << score;
		if (last_dir == "L") {
			Snake_node *s = new Snake_node(last_x + 2, last_y, "L");
			s_list.push_back(*s);
			delete s;
		}
		else if (last_dir == "R") {
			Snake_node *s = new Snake_node(last_x - 2, last_y, "R");
			s_list.push_back(*s);
			delete s;
		}
		else if (last_dir == "U") {
			Snake_node *s = new Snake_node(last_x, last_y + 1, "U");
			s_list.push_back(*s);
			delete s;
		}
		else if (last_dir == "D") {
			Snake_node *s = new Snake_node(last_x, last_y - 1, "D");
			s_list.push_back(*s);
			delete s;
		}
		refreshFood();
	}


	//重画蛇
	for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) {
		Gotoxy(it->s_x, it->s_y);
		if (it == s_list.begin()) {
			cout << "■";
		}
		else {
			cout << "□";
		}
	}

}

bool collision() {
	if (s_list.begin()->s_x < 2 || s_list.begin()->s_x > 57 || s_list.begin()->s_y < 1 || s_list.begin()->s_y > 28) {
		return true;
	}
	else {
		return false;
	}	
}

bool biteself() {
	for (list<Snake_node>::iterator it = s_list.begin(); it != s_list.end(); it++) {
		if (it != s_list.begin()) {
			if (s_list.begin()->s_x == it->s_x && s_list.begin()->s_y == it->s_y) {
				return true;
			}
		}
	}
	return false;
}

void runGame() {	
	while (1) 
	{

		//判断有无输入
		if (_kbhit()) {
			char ch = _getch();	

			switch (ch) 
			{
			case 27://ESC
				return;
				break;
			case 32://空格
				Gotoxy(64, 23);
				system("pause");
				Gotoxy(64, 23);
				cout << "                    ";
				break;
			case 59://F1
				velocity = 1;
				break;
			case 60://F2
				velocity = 2;
				break;
			case 61://F3
				velocity = 3;
				break;
			case 72: {//上
				if (s_list.begin()->s_direction == "D") {
					break;
				}
				s_list.begin()->s_direction = "U";
				break;
			}
			case 75://左
				if (s_list.begin()->s_direction == "R") {
					break;
				}
				s_list.begin()->s_direction = "L";
				break;
			case 77://右
				if (s_list.begin()->s_direction == "L") {
					break;
				}
				s_list.begin()->s_direction = "R";
				break;
			case 80://下
				if (s_list.begin()->s_direction == "U") {
					break;
				}
				s_list.begin()->s_direction = "D";
				break;
			default:
				break;
			}
			
		}


		else {
			//移动蛇
			moveSnake();

			//判断蛇是否撞墙
			if (collision()) {
				break;
			}

			//判断蛇是否咬到自己
			if (biteself()) {
				break;
			}

			//调整速度
			switch (velocity) {
			case 1:
				Sleep(300);
				break;
			case 2:
				Sleep(500);
				break;
			case 3:
				Sleep(700);
				break;
			}
		}



	}
	
}

int main()
{
	GameStart();
	CreatMap();
	textMap();
	initSnake();
	refreshFood();
	runGame();
	s_list.clear();
	Gotoxy(64, 23);
	system("pause");
	return 0;
}