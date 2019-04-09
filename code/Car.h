#pragma once
#include<vector>
using namespace std;
#include<map>
class Car
{
public:
	Car();
	Car(vector<int> carData);
	Car(int id, int from, int to, int speed, int planTime, int priority, int preSet);
	
	int getID();
	int getFrom();
	int getTo();
	int getSpeed();
	int getPlanTime();
	int getPriority();
	int getPreSet();
	int getActualTime();
	vector<int> getPlanRoute();

	void setID(int id);
	void setFrom(int from);
	void setTo(int to);
	void setSpeed(int speed);
	void setPlanTime(int planTime);
	void setPriority(int priority);
	void setPreSet(int preSet);
	void setActualTime(int time);
	void setPlanRoute(vector<int> planRoute);
	


	~Car();
private:
	int mId;
	int mFrom;
	int mTo;
	int mSpeed;
	int mPlanTime;
	int mPriority;
	int mPreSet;
	int mActualTime;
	//map <int, int> mMapIdToIndex;
	vector<int> mPlanRoute;
};

