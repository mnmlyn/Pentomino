/*
* 定义Brick类，表示一个块
*/

#include "Brick.h"
const int MX = 10;//大矩形的尺寸
const int MY = 6;

Brick::Brick(int value,bool isMirror)
{
	this->value = value;
	this->isMirror = isMirror;
}

/*
* 获取坐标最大最小值
*/
void Brick::getMinMaxPos()
{
	int i;
	this->minX = this->pos[0].x;
	this->maxX = this->pos[0].x;
	this->minY = this->pos[0].y;
	this->maxY = this->pos[0].y;
	for (i = 1; i < 5; i++)
	{
		if (this->pos[i].x > this->maxX)this->maxX = this->pos[i].x;
		if (this->pos[i].x < this->minX)this->minX = this->pos[i].x;
		if (this->pos[i].y > this->maxY)this->maxY = this->pos[i].y;
		if (this->pos[i].y < this->minY)this->minY = this->pos[i].y;
	}
}

/*
* 将块移动到原点，即minX==0,minY==0
*/
void Brick::move2Zero()
{
	int i;
	this->getMinMaxPos();
	if (this->minX || this->minY)
	{
		for (i = 0; i < 5; i++)
		{
			this->pos[i].x -= this->minX;
			this->pos[i].y -= this->minY;
		}
	}
	this->getMinMaxPos();
}

/*
* 将图形旋转90度，并移动到原点
*/
void Brick::rotate()
{
	int i,temp;
	for (i = 0; i < 5; i++)
	{
		//逆时针旋转90度
		temp = this->pos[i].x;
		this->pos[i].x = this->pos[i].y;
		this->pos[i].y = -temp;
	}
	//this->move2Zero();
}

/*
* 将图形镜像
*/
void Brick::mirror()
{
	int i;
	for (i = 0; i < 5; i++)
	{
		this->pos[i].x = -this->pos[i].x;
	}
	//this->move2Zero();
}

/*
* 初始化，应在next之前调用
*/
void Brick::init()
{
	int angle = this->state % 4;
	if (angle <= 3 && angle > 0)
	{
		for (int i=0; i < 4 - angle; i++)
		{
			this->rotate();//旋转90度
		}
	}
	if (this->state > 3)
	{
		this->mirror();//镜像
	}
	this->move2Zero();
	this->state = 0;//代表原始方位
	this->posX = -1;
	this->posY = 0;
	this->posMaxX = MX - this->maxX - 1;
	this->posMaxY = MY - this->maxY - 1;
}

/*
* 获取下一个，该函数将不断移动、旋转、镜像图形。返回0代表再没有其他可能的图形
*/
int Brick::next()
{
	//横向移动
	if (this->posX < this->posMaxX)
	{
		this->posX++;
	}
	else if (this->posX == this->posMaxX)
	{
		//纵向移动
		if (this->posY < this->posMaxY)
		{
			this->posY++;
			this->posX = 0;
		}
		else if (this->posY == this->posMaxY)
		{
			//对X,I图案特殊处理
			if (this->value == 10)//X
			{
				return 0;//没有其他可能图形
			}
			else if (this->value == 7)//I
			{
				if (this->state == 1)return 0;
				else
				{
					this->rotate();//旋转90度
					this->move2Zero();
				}
			}
			else if (this->value == 12)//Z
			{
				if (this->state == 5)
				{
					return 0;//没有其他可能图形
				}
				else if (this->state == 0 || this->state == 4)
				{
					this->rotate();//旋转90度
					this->move2Zero();
				}
				else if (this->state == 1)
				{
					this->rotate();//旋转90度
					this->rotate();//旋转90度
					this->rotate();//旋转90度
					this->mirror();//镜像
					this->move2Zero();
					this->state = 3;//后边++之后，变为4
				}
			}
			else if (this->isMirror && this->state == 7
				|| !this->isMirror && this->state == 3
				)
			{
				return 0;//没有其他可能图形
			}
			else if (this->isMirror && this->state == 3)
			{
				this->rotate();//旋转90度
				this->mirror();//镜像
				this->move2Zero();
			}
			else
			{
				this->rotate();//旋转90度
				this->move2Zero();
			}
			this->state++;
			this->posX = 0;
			this->posY = 0;
			this->posMaxX = MX - this->maxX - 1;
			this->posMaxY = MY - this->maxY - 1;
		}
	}
	return 1;
}





