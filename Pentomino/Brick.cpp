/*
* ����Brick�࣬��ʾһ����
*/

#include "Brick.h"
const int MX = 10;//����εĳߴ�
const int MY = 6;

Brick::Brick(int value,bool isMirror)
{
	this->value = value;
	this->isMirror = isMirror;
}

/*
* ��ȡ���������Сֵ
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
* �����ƶ���ԭ�㣬��minX==0,minY==0
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
* ��ͼ����ת90�ȣ����ƶ���ԭ��
*/
void Brick::rotate()
{
	int i,temp;
	for (i = 0; i < 5; i++)
	{
		//��ʱ����ת90��
		temp = this->pos[i].x;
		this->pos[i].x = this->pos[i].y;
		this->pos[i].y = -temp;
	}
	//this->move2Zero();
}

/*
* ��ͼ�ξ���
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
* ��ʼ����Ӧ��next֮ǰ����
*/
void Brick::init()
{
	int angle = this->state % 4;
	if (angle <= 3 && angle > 0)
	{
		for (int i=0; i < 4 - angle; i++)
		{
			this->rotate();//��ת90��
		}
	}
	if (this->state > 3)
	{
		this->mirror();//����
	}
	this->move2Zero();
	this->state = 0;//����ԭʼ��λ
	this->posX = -1;
	this->posY = 0;
	this->posMaxX = MX - this->maxX - 1;
	this->posMaxY = MY - this->maxY - 1;
}

/*
* ��ȡ��һ�����ú����������ƶ�����ת������ͼ�Ρ�����0������û���������ܵ�ͼ��
*/
int Brick::next()
{
	//�����ƶ�
	if (this->posX < this->posMaxX)
	{
		this->posX++;
	}
	else if (this->posX == this->posMaxX)
	{
		//�����ƶ�
		if (this->posY < this->posMaxY)
		{
			this->posY++;
			this->posX = 0;
		}
		else if (this->posY == this->posMaxY)
		{
			//��X,Iͼ�����⴦��
			if (this->value == 10)//X
			{
				return 0;//û����������ͼ��
			}
			else if (this->value == 7)//I
			{
				if (this->state == 1)return 0;
				else
				{
					this->rotate();//��ת90��
					this->move2Zero();
				}
			}
			else if (this->value == 12)//Z
			{
				if (this->state == 5)
				{
					return 0;//û����������ͼ��
				}
				else if (this->state == 0 || this->state == 4)
				{
					this->rotate();//��ת90��
					this->move2Zero();
				}
				else if (this->state == 1)
				{
					this->rotate();//��ת90��
					this->rotate();//��ת90��
					this->rotate();//��ת90��
					this->mirror();//����
					this->move2Zero();
					this->state = 3;//���++֮�󣬱�Ϊ4
				}
			}
			else if (this->isMirror && this->state == 7
				|| !this->isMirror && this->state == 3
				)
			{
				return 0;//û����������ͼ��
			}
			else if (this->isMirror && this->state == 3)
			{
				this->rotate();//��ת90��
				this->mirror();//����
				this->move2Zero();
			}
			else
			{
				this->rotate();//��ת90��
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




