#include "pch.h"
#include "Car.h"
#include<vector>
using namespace std;

Car::Car()
{
}
Car::Car(vector<int> carData)
{
	setID(carData[0]);
	setFrom(carData[1]);
	setTo(carData[2]);
	setSpeed(carData[3]);
	setPlanTime(carData[4]);
	setPriority(carData[5]);
	setPreSet(carData[6]);
}
Car::Car(int id, int from, int to, int speed, int planTime, int priority, int preSet)
{
	setID(id);
	setFrom(from);
	setTo(to);
	setSpeed(speed);
	setPlanTime(planTime);
	setPriority(priority);
	setPreSet(preSet);
	setActualTime(planTime);
	//ans = new ArrayList<Integer>();
}

int Car::getID() { return mId; }
int Car::getFrom() { return mFrom; }
int Car::getTo() { return mTo;}
int Car::getSpeed() { return mSpeed; }
int Car::getPlanTime() { return mPlanTime; }
int Car::getPriority() { return mPriority; }
int Car::getPreSet() { return mPreSet; }
int Car::getActualTime() { return mActualTime; }
vector<int> Car::getPlanRoute() { return mPlanRoute; }

void Car::setID(int id) { mId = id; }
void Car::setFrom(int from) { mFrom = from; }
void Car::setTo(int to) { mTo = to; }
void Car::setSpeed(int speed) { mSpeed = speed; }
void Car::setPlanTime(int planTime) { mPlanTime = planTime; }
void Car::setPriority(int priority) { mPriority = priority; }
void Car::setPreSet(int preSet) { mPreSet = preSet; }
void Car::setActualTime(int time) { mActualTime = time; }
void Car::setPlanRoute(vector<int> planRoute) { mPlanRoute = planRoute; }
Car::~Car()
{
}
