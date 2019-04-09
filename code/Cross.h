#pragma once
#include"pch.h"
#include<vector>
using namespace std;
class Cross
{
public:
	Cross();
	Cross(int id, vector<int> road);
	Cross(vector<int> crossData);
	void setId(int id );
	void setRoad(vector<int> road);

	int getId();
	vector<int> getRoad();
	~Cross();
private:
	int mId;
	vector<int> mRoad;
};

