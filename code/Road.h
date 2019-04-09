#pragma once
class Road
{
public:
	Road();
	Road(vector<int> roadData);
	Road(int id, int length, int speed, int channel, int from, int to, int isDuplex) ;
	int getId();
	int getLength();
	int getSpeed();
	int getChannel();
	int getFrom();
	int getTo();
	int getIsDuplex();
	int getCurrentMaxSpeed();

	void setId(int id);
	void setLength(int length);
	void setSpeed(int speed);
	void setChannel(int channel);
	void setFrom(int from);
	void setTo(int to);
	void setIsDuplex(int isDuplex);
	void setCurrentMaxSpeed(int speed);
	~Road();
private:
	int mId;
	int mFrom;
	int mTo;
	int mLength;
	int mIsDuplex;
	int mChannel;
	int mSpeed;
	int mCurrentMaxSpeed;
	vector<vector<int> > mContainsCar;
	//int[][] containsCar;
};

