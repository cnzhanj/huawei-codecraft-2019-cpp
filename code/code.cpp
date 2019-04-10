// code.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>

int main()
{
	Cal cal;
	cal.init();
	cal.calDisMatrix();
	//cal.printDisMatrix();
	vector<vector<int> > dis = cal.getDisMatrix();
	cout << 1 << endl;
	cal.Floyd(dis);
	cout << 2 << endl;
	//cal.printMinDisPathRecord();
 	string basePath = "F:\\硕士资料\\2018-2019\\HUAWEI\\2-map-training-2\\";
	string pathAnswer = basePath + "answer.txt";
	cal.setMinDisPathRecordForCar();
	cout << 3 << endl;
	cal.writeAns(pathAnswer);
	cout << 4 << endl;
	/*vector<vector<int> > dis(9, vector<int>(9, MAXDISTANCE));
	for (int i = 0; i < dis.size(); i++)
	{
		for (int j = 0; j < dis.size(); j++)
		{
			if (i == j)
				dis[i][j] = 0;
			
		}
	}
	dis[0][1] = 1;
	dis[0][2] = 5;
	dis[1][2] = 3;
	dis[1][3] = 7;
	dis[1][4] = 5;

	dis[2][4] = 1;
	dis[2][5] = 7;
	dis[3][4] = 2;
	dis[3][6] = 3;
	dis[4][5] = 3;

	dis[4][6] = 6;
	dis[4][7] = 9;
	dis[5][7] = 5;
	dis[6][7] = 2;
	dis[6][8] = 7;

	dis[7][8] = 4;
	for (int i = 0; i < dis.size(); i++)
	{
		for (int j = i; j < dis.size(); j++)
		{
			dis[j][i] = dis[i][j];
		}
	}
	*/
	
}


