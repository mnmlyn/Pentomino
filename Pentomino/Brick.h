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
	bool isMirror;//���ɾ��񣬴����Գƺ����״����ͨ����ת�õ�
	int value;

	int minX;//�������
	int maxX;
	int minY;//�������
	int maxY;
	
	int state;

	int posX;//���ڴ�����е�λ��
	int posY;
	int posMaxX;//���ڴ�����е����λ��
	int posMaxY;

	/*
	* �����ƶ���ԭ�㣬��minX==0,minY==0
	*/
	void move2Zero();
	/*
	* ��ͼ����ת90��
	*/
	void rotate();
	/*
	* ��ͼ�ξ���
	*/
	void mirror();
	/*
	* ��ʼ����Ӧ��next֮ǰ����
	*/
	void init();
	/*
	* ��ȡ��һ�����ú����������ƶ�����ת������ͼ�Ρ�����0������û���������ܵ�ͼ��
	* �ʼӦ�ȵ���init
	*/
	int next();
private:
	int a;
	void getMinMaxPos();
};