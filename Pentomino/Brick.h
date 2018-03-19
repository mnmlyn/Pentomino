#pragma once

struct Postion
{
	int x;
	int y;
};

class Brick
{
public:
	Brick(int value, bool isMirror);
	Postion pos[5];
	bool isMirror;//不可镜像，代表对称后的形状可以通过旋转得到
	int value;

	int minX;//块的左沿
	int maxX;
	int minY;//块的上沿
	int maxY;
	
	int state;

	int posX;//块在大矩形中的位置
	int posY;
	int posMaxX;//块在大矩形中的最大位置
	int posMaxY;

	/*
	* 将块移动到原点，即minX==0,minY==0
	*/
	void move2Zero();
	/*
	* 将图形旋转90度
	*/
	void rotate();
	/*
	* 将图形镜像
	*/
	void mirror();
	/*
	* 初始化，应在next之前调用
	*/
	void init();
	/*
	* 获取下一个，该函数将不断移动、旋转、镜像图形。返回0代表再没有其他可能的图形
	* 最开始应先调用init
	*/
	int next();
private:
	int a;
	void getMinMaxPos();
};
