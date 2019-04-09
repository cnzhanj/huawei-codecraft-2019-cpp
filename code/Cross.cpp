#include "pch.h"
#include "Cross.h"
Cross::Cross()
{
}
Cross::Cross(vector<int> crossData)
{
	setId(crossData[0]);
	vector<int> road;
	for (int i = 1; i < crossData.size(); i++)
		road.push_back(crossData[i]);
	setRoad(road);
}
Cross::Cross(int id, vector<int> road)
{
	setId(id);
	setRoad(road);
}
void Cross::setId(int id){mId = id;}
void Cross::setRoad(vector<int> road){mRoad = road;}

int Cross::getId() { return mId; }
vector<int> Cross::getRoad() { return mRoad; }

Cross::~Cross()
{
}
