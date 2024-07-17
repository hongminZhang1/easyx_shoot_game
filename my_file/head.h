#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <cstdlib>
using namespace std;
const int H = 600;
const int W = 800;
const int K = 4;//爆率
int dx[25] = { 0,0,0,-1,1,1,1,-1,-1,2,2,1,1,-2,-2,-1,-1,1,1,3,3,-1,-1,-3,-3 };//方向数组
int dy[25] = { 0,-1,1,0,0,1,-1,1,-1,1,-1,2,-2,1,-1,2,-2,3,-3,1,-1,3,-3,1,-1 };
int check[20][6];//确定得分
void init_score_check() {
	for (int i = 10;i <= 12;i++)
		for (int j = 1;j <= 5;j++)
			check[i][j] = 5 * j;
	for (int i = 13;i <= 16;i++)
		for (int j = 1;j <= 5;j++)
			check[i][j] = 3 * j;
	for (int i = 17;i <= 19;i++)
		for (int j = 1;j <= 5;j++)
			check[i][j] = 2 * j;
}
