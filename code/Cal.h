#pragma once
#define MAXDISTANCE 1000000
#include<map>
class Cal
{
public:
	Cal();
	void init();
	void calDisMatrix();
	vector<vector<int> > getDisMatrix();
	void mapCrossId();
	void printDisMatrix();
	void writeAns(string pathAnswer);
	void Floyd(vector<vector<int>> dis);
	void printMinDisPathRecord();
	void setMinDisPathRecordForCar();
	void setRoadIdByCross();
	~Cal();
private:
	vector<Car> mCar;
	vector<Cross> mCross;
	vector<Road> mRoad;
	vector<vector<int> > mDisMatrix;
	map<int, int> mMapCrossId;
	vector<vector<int> > mMinDis;
	vector<vector<vector<int> > > mMinDisPathRecord;
	vector<vector<int> >  mRoadIdByCross;

};

