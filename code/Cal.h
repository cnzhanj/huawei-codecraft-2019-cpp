#pragma once
#define MAXDISTANCE 1000000
#include<map>
class Cal
{
public:
	Cal();
	void calAdjMatrix();
	void mapCrossId();
	void printAdjMatrix();
	void writeAns(string pathAnswer);
	~Cal();
private:
	vector<Car> mCar;
	vector<Cross> mCross;
	vector<Road> mRoad;
	vector<vector<int> > mAdjMatrix;
	map<int, int> mMapCrossId;
};

