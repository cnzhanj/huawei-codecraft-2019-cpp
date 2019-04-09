#include "pch.h"
#include "Cal.h"


Cal::Cal()
{
	string basePath = "F:\\Ë¶Ê¿×ÊÁÏ\\2018-2019\\HUAWEI\\2-map-training-2\\";
	string pathCar = basePath + "car.txt";
	string pathCross = basePath + "cross.txt";
	string pathRoad = basePath + "road.txt";
	string pathPresetAnswer = basePath + "presetAnswer.txt";
	Initial ini;
	ini.initialCar(pathCar);
	ini.initialCross(pathCross);
	ini.initialRoad(pathRoad);
	ini.initialPresetAnswer(pathPresetAnswer);

	mCar = ini.getCar();
	mCross = ini.getCross();
	mRoad = ini.getRoad();

}
void Cal::mapCrossId()
{
	map<int, int> crossId;
	for (int i = 0; i < mCross.size(); i++)
	{
		//cout << mCross[i].getId() << " " << i << endl;
		crossId[mCross[i].getId()] = i;
	}
	mMapCrossId = crossId;
}
void Cal::calAdjMatrix()
{
	vector<vector<int> > adjMatrix(mCross.size(), vector<int>(mCross.size(), MAXDISTANCE));
	mapCrossId();
	cout << mRoad.size() << endl << endl;
	for (int i = 0; i < mRoad.size(); i++)
	{
		int fromId = mRoad[i].getFrom();
		int toId = mRoad[i].getTo();
		//cout << i << " " << fromId << " " << toId << endl;
		int row = mMapCrossId[fromId];
		int col = mMapCrossId[toId];
		//cout << i << " " << row << " " << col << endl << endl;
		int length = mRoad[i].getLength();
		adjMatrix[row][col] = length;
		if (mRoad[i].getIsDuplex())
		{
			adjMatrix[col][row] = length;
		}
	}
	mAdjMatrix = adjMatrix;
}
void Cal::printAdjMatrix()
{
	cout << mAdjMatrix.size() << endl;
	int count = 0;
	for (int i = 0; i < mAdjMatrix.size(); i++)
	{
		for (int j = 0; j < mAdjMatrix[i].size(); j++)
		{
			//cout << mAdjMatrix[i][j] << " ";
			if (mAdjMatrix[i][j] < MAXDISTANCE)
				cout << count++ << " " << i << " " << j << endl;
		}
	}
}
void Cal::writeAns(string pathAnswer)
{
	ofstream answer(pathAnswer);
	for (int i = 0; i < mCar.size(); i++)
	{
		if (!mCar[i].getPreSet())
		{
			answer << '(' << mCar[i].getID() << ',' << mCar[i].getActualTime() << ',';
			vector<int> planRoute = mCar[i].getPlanRoute();
			for (int j = 0; j < planRoute.size(); j++)
			{
				answer << planRoute[j];
				if (j != planRoute.size() - 1)
					answer << ",";
			}
			answer << ')' << endl;
		}
	}
}
Cal::~Cal()
{
}
