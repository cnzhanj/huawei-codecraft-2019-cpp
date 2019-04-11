#pragma once
#define MAXDISTANCE 1000000
#include<map>
class Cal
{
public:
	Cal();
	void init(string pathCar, string pathCross, string pathRoad, string pathPresetAnswer);
	void calDisMatrix();
	void initTimeMatrix();
	void calTimeMatrix(vector<Car> car);

	vector<vector<double> > getDisMatrix();
	vector<vector<double> > getTimeMatrix();
	void setVote(vector<Car > car);
	void mapCrossId();
	void mapRoadId();
	void mapCarId();
	void printDisMatrix();
	void writeAns(string pathAnswer);
	void Floyd(vector<vector<double>> dis);
	void printMinDisPathRecord();
	void setMinDisPathRecordForCar();
	void setRoadIdByCross();
	void setCarStartTime();
	void updateSpeedMatrix(vector<Car> car);
	void resetSpeedMatrix();
	void updateTimeMatrix(vector<vector<int> > disMatrix, vector<Car> car);
	void setCarStartTimeForCar(vector<Car> car, vector<int> time);
	void mainFunction();
	~Cal();
private:
	vector<Car> mCar;
	vector<Cross> mCross;
	vector<Road> mRoad;
	vector<int> mSaveRoadSpeed;
	vector<Road> mRoadTime;

	vector<vector<double> > mDisMatrix;
	vector<vector<double> > mTimeMatrix;

	vector<vector<double> > mVote;
	map<int, int> mMapCrossId;
	map<int, int> mMapRoadId;
	map<int, int> mMapCarId;
	vector<vector<double> > mMinDis;
	vector<vector<vector<int> > > mMinDisPathRecord;
	vector<vector<int> >  mRoadIdByCross;

};

