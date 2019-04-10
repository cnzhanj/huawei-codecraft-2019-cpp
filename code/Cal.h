#pragma once
#define MAXDISTANCE 1000000
#include<map>
class Cal
{
public:
	Cal();
	void init(string pathCar, string pathCross, string pathRoad, string pathPresetAnswer);
	void calDisMatrix();
	vector<vector<int> > getDisMatrix();
	void setVote(vector<Car > car);
	void mapCrossId();
	void mapRoadId();
	void printDisMatrix();
	void writeAns(string pathAnswer);
	void Floyd(vector<vector<int>> dis);
	void printMinDisPathRecord();
	void setMinDisPathRecordForCar();
	void setRoadIdByCross();
	void setCarStartTime();
	~Cal();
private:
	vector<Car> mCar;
	vector<Cross> mCross;
	vector<Road> mRoad;
	vector<vector<int> > mDisMatrix;
	map<int, int> mMapCrossId;
	map<int, int> mMapRoadId;
	vector<vector<int> > mMinDis;
	vector<vector<vector<int> > > mMinDisPathRecord;
	vector<vector<int> >  mRoadIdByCross;

};

