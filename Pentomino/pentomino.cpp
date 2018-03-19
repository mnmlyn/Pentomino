/*
* 伤脑筋十二块
* 暴力解法
*/

#include<iostream>
#include<cstring>
#include <fstream> 
#include<time.h>
#include"Brick.h"

/*
* 块的初始化
*/
void brickInit(Brick **brick)
{
	//N
	brick[0] = new Brick(1, true);
	brick[0]->pos[0] = { 0,0 };
	brick[0]->pos[1] = { 1,0 };
	brick[0]->pos[2] = { 2,0 };
	brick[0]->pos[3] = { 2,1 };
	brick[0]->pos[4] = { 3,1 };
	//Y
	brick[1] = new Brick(2, true);
	brick[1]->pos[0] = { 0,0 };
	brick[1]->pos[1] = { 1,0 };
	brick[1]->pos[2] = { 2,0 };
	brick[1]->pos[3] = { 3,0 };
	brick[1]->pos[4] = { 2,1 };
	//U
	brick[2] = new Brick(3, false);
	brick[2]->pos[0] = { 0,0 };
	brick[2]->pos[1] = { 2,0 };
	brick[2]->pos[2] = { 0,1 };
	brick[2]->pos[3] = { 1,1 };
	brick[2]->pos[4] = { 2,1 };
	//V
	brick[3] = new Brick(4, false);
	brick[3]->pos[0] = { 0,0 };
	brick[3]->pos[1] = { 1,0 };
	brick[3]->pos[2] = { 2,0 };
	brick[3]->pos[3] = { 0,1 };
	brick[3]->pos[4] = { 0,2 };
	//W
	brick[4] = new Brick(5, false);
	brick[4]->pos[0] = { 1,0 };
	brick[4]->pos[1] = { 2,0 };
	brick[4]->pos[2] = { 0,1 };
	brick[4]->pos[3] = { 1,1 };
	brick[4]->pos[4] = { 0,2 };
	//T
	brick[5] = new Brick(6, false);
	brick[5]->pos[0] = { 0,0 };
	brick[5]->pos[1] = { 1,0 };
	brick[5]->pos[2] = { 2,0 };
	brick[5]->pos[3] = { 1,1 };
	brick[5]->pos[4] = { 1,2 };
	//I//只需要两种state
	brick[6] = new Brick(7, false);
	brick[6]->pos[0] = { 0,0 };
	brick[6]->pos[1] = { 1,0 };
	brick[6]->pos[2] = { 2,0 };
	brick[6]->pos[3] = { 3,0 };
	brick[6]->pos[4] = { 4,0 };
	//L
	brick[7] = new Brick(8, true);
	brick[7]->pos[0] = { 0,0 };
	brick[7]->pos[1] = { 0,1 };
	brick[7]->pos[2] = { 0,2 };
	brick[7]->pos[3] = { 0,3 };
	brick[7]->pos[4] = { 1,3 };
	//P
	brick[8] = new Brick(9, true);
	brick[8]->pos[0] = { 0,0 };
	brick[8]->pos[1] = { 1,0 };
	brick[8]->pos[2] = { 0,1 };
	brick[8]->pos[3] = { 1,1 };
	brick[8]->pos[4] = { 0,2 };
	//X//只需要一种state
	brick[9] = new Brick(10, false);
	brick[9]->pos[0] = { 1,0 };
	brick[9]->pos[1] = { 0,1 };
	brick[9]->pos[2] = { 1,1 };
	brick[9]->pos[3] = { 2,1 };
	brick[9]->pos[4] = { 1,2 };
	//F
	brick[10] = new Brick(11, true);
	brick[10]->pos[0] = { 0,0 };
	brick[10]->pos[1] = { 1,0 };
	brick[10]->pos[2] = { 1,1 };
	brick[10]->pos[3] = { 2,1 };
	brick[10]->pos[4] = { 1,2 };
	//Z//旋转180度相同
	brick[11] = new Brick(12, true);
	brick[11]->pos[0] = { 0,0 };
	brick[11]->pos[1] = { 1,0 };
	brick[11]->pos[2] = { 1,1 };
	brick[11]->pos[3] = { 1,2 };
	brick[11]->pos[4] = { 2,2 };

}

/*
* 将矩阵复位
*/
void resetArr(int (*arr)[6])
{
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 6; j++)
			arr[i][j] = 0;
}

std::ofstream fout;

/*
* 打印矩阵，同时打印到文件
*/
void printArr(int(*arr)[6])
{
	using namespace std;
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 6; j++)
		{
			cout << arr[i][j] << "\t";
			fout << arr[i][j] << "\t";
		}
		cout << endl;
		fout << endl;
	}
}

/*
* 判断未填充连通区域是否能够放入至少一个块
*/
bool isAreaOk(int(*_arr)[6])
{
	using namespace std;
	int i, j;
	int arr[12][8];
	//边框
	for (i = 0; i < 12; i++)
	{
		arr[i][0] = 1;
		arr[i][7] = 1;
	}
	for (i = 0; i < 8; i++)
	{
		arr[0][i] = 1;
		arr[11][i] = 1;
	}
	//内容
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 6; j++)
		{
			arr[i + 1][j + 1] = _arr[i][j];
		}
	}

	//栈
	int stack[6 * 10] = {0};
	int sp = 0;
	int x, y, count = 0, op;


	for (i = 1; i < 11; i++)
	{
		for (j = 1; j < 7; j++)
		{
			if (arr[i][j] != 0)continue;
			count = 0;
			//入栈
			arr[i][j] = -1;
			if (!arr[i + 1][j])
			{
				stack[sp++] = 0;
				x = i + 1;
				y = j;
			}
			else if (!arr[i][j + 1])
			{
				stack[sp++] = 1;
				x = i;
				y = j + 1;
			}
			else if (!arr[i - 1][j])
			{
				stack[sp++] = 2;
				x = i - 1;
				y = j;
			}
			else if (!arr[i][j - 1])
			{
				stack[sp++] = 3;
				x = i;
				y = j - 1;
			}
			else
			{
				return false;//只有单独的一块
			}
			count++;

			while (sp || op != 3)
			{
				//入栈
				if (arr[x][y] == 0)
				{
					arr[x][y] = -1;
					count++;
				}
				//上下左右搜寻
				if (!arr[x + 1][y])
				{
					stack[sp++] = 0;
					x = x + 1;
					y = y;
				}
				else if (!arr[x][y + 1])
				{
					stack[sp++] = 1;
					x = x;
					y = y + 1;
				}
				else if (!arr[x - 1][y])
				{
					stack[sp++] = 2;
					x = x - 1;
					y = y;
				}
				else if (!arr[x][y - 1])
				{
					stack[sp++] = 3;
					x = x;
					y = y - 1;
				}
				else
				{
					//出栈
					if (sp > 0)
					{
						op = stack[--sp];
					}
					else
					{
						break;
					}
					if (op == 0)
					{
						x = x - 1;
						y = y;
					}
					else if (op == 1)
					{
						x = x;
						y = y - 1;
					}
					else if (op == 2)
					{
						x = x + 1;
						y = y;
					}
					else if (op == 3)
					{
						x = x;
						y = y + 1;
					}
				}
			}
			//cout << "count=" << count << endl;
			if (count % 5 != 0)
			{
				//cout << "Break!!! count=" << count << endl;
				return false;
			}
		}
	}
	return true;
}

int g_index = 0;

void fillArr(Brick **bk,int(*_arr)[6],int b)
{
	using namespace std;
	int arr[10][6];
	int i;
	memcpy(arr, _arr, 6 * 10 * sizeof(int));
	bk[b]->init();
	while (bk[b]->next())
	{
		if (b == 0)
		{
			g_index++;
			fout.close();
			fout.open("data.txt", ios::app);
			cout << "g_index=" << g_index << endl;//输出查看进度
			fout << "g_index=" << g_index << endl;//输出查看进度
		}
		for (i = 0; i < 5; i++)
		{
			if (arr[bk[b]->pos[i].x + bk[b]->posX][bk[b]->pos[i].y + bk[b]->posY] == 0)
			{
				arr[bk[b]->pos[i].x + bk[b]->posX][bk[b]->pos[i].y + bk[b]->posY] = bk[b]->value;
			}
			else
			{
				break;
			}
		}//behind here!
		if (5 != i)//填充发生冲突
		{
			memcpy(arr, _arr, 6 * 10 * sizeof(int));
			continue;
		}
		else
		{
			if (11 == b)
			{
				printArr(arr);
				std::cout << std::endl;
				std::cout << std::endl;
				fout << std::endl;
				fout << std::endl;
				return;//已经填满，最后一块不需要再变换
			}
			if (isAreaOk(arr))
			{
				fillArr(bk, arr, b + 1);
			}
			else
			{
				memcpy(arr, _arr, 6 * 10 * sizeof(int));
				continue;
			}
		}
	}

}

int main()
{
	using namespace std;

	//计时
	clock_t start, finish;
	double totaltime;
	start = clock();

	int arr[10][6] = { 0 };
	
	Brick *bk[12];
	brickInit(bk);//定义12块的形状

	fout.open("data.txt");

	fillArr(bk, arr, 0);

	//计时
	finish = clock();
	totaltime = (double)(finish - start) / CLOCKS_PER_SEC;
	cout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;
	fout << "\n此程序的运行时间为" << totaltime << "秒！" << endl;

	cout << "End" << endl;
	fout << "End" << endl;

	fout.close();

	cin.get();
	return 0;
}