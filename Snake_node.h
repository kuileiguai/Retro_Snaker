#pragma once
#include <iostream>
#include <string>
using namespace std;

class Snake_node {
public:
	int s_x;

	int s_y;

	//���� ��L �ң�R �ϣ�U �£�D
	string s_direction;

	void eatFood();

	Snake_node(int x,int y,string dir);
};