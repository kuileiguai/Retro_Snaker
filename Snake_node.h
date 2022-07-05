#pragma once
#include <iostream>
#include <string>
using namespace std;

class Snake_node {
public:
	int s_x;

	int s_y;

	//方向 左：L 右：R 上：U 下：D
	string s_direction;

	void eatFood();

	Snake_node(int x,int y,string dir);
};