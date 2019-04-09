#include "pch.h"
#include "Road.h"
#include<vector>
using namespace std;
Road::Road()
{
}
Road::Road(vector<int> roadData)
{
	setId(roadData[0]);
	setLength(roadData[1]);
	setSpeed(roadData[2]);
	setChannel(roadData[3]);
	setFrom(roadData[4]);
	setTo(roadData[5]);
	setIsDuplex(roadData[6]);
	setCurrentMaxSpeed(roadData[2]);
}
Road::Road(int id, int length, int speed, int channel, int from, int to, int isDuplex) {
	setId(id);
	setLength(length);
	setSpeed(speed);
	setChannel(channel);
	setFrom(from);
	setTo(to);
	setIsDuplex(isDuplex);
	setCurrentMaxSpeed(speed);
}
int Road::getId() { return mId; }
int Road::getLength() { return mLength; }
int Road::getSpeed() { return mSpeed; }
int Road::getChannel() { return mChannel; }
int Road::getFrom() { return mFrom; }
int Road::getTo() { return mTo; }
int Road::getIsDuplex() { return mIsDuplex; }
int Road::getCurrentMaxSpeed() { return mCurrentMaxSpeed; }

void Road::setId(int id) { mId = id; }
void Road::setLength(int length) { mLength = length; }
void Road::setSpeed(int speed) { mSpeed = speed; }
void Road::setChannel(int channel) { mChannel = channel; }
void Road::setFrom(int from) { mFrom = from; }
void Road::setTo(int to) { mTo = to; }
void Road::setIsDuplex(int isDuplex) { mIsDuplex = isDuplex; }
void Road::setCurrentMaxSpeed(int speed) { mCurrentMaxSpeed = speed; };

Road::~Road()
{
}
