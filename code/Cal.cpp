#include "pch.h"
#include "Cal.h"
#include<math.h>
#include<algorithm>
Cal::Cal()
{
	
	//vector<vector<vector<int> > > minDisPath(mCross.size(), vector<int>(mCross.size(), vector<int>(mCross.size(), MAXDISTANCE));
}
void Cal::init(string pathCar, string pathCross, string pathRoad, string pathPresetAnswer)
{
	
	Initial ini;
	ini.initialCar(pathCar);
	ini.initialCross(pathCross);
	ini.initialRoad(pathRoad);
	ini.initialPresetAnswer(pathPresetAnswer);

	mCar = ini.getCar();
	mCross = ini.getCross();
	mRoad = ini.getRoad();
	for (int i = 0; i < mRoad.size(); i++)
	{
		mSaveRoadSpeed.push_back(mRoad[i].getSpeed());
	}
	vector < vector<double> > vote(mCross.size(), vector<double>(mCross.size(), 0));
	mVote = vote;
	mapCrossId();
	mapRoadId();
	mapCarId();
	//mMinDis = (mCross.size(), vector<int>(mCross.size(), MAXDISTANCE));
}
void Cal::mapCrossId()
{
	map<int, int> crossId;
	for (int i = 0; i < mCross.size(); i++)
	{
		//cout << mCross[i].getId() << " " << i << endl;
		crossId[mCross[i].getId()] = i;
	}
	mMapCrossId = crossId;
}
void Cal::mapRoadId()
{
	map<int, int> roadId;
	for (int i = 0; i < mRoad.size(); i++)
	{
		//cout << mCross[i].getId() << " " << i << endl;
		roadId[mRoad[i].getId()] = i;
	}
	mMapRoadId = roadId;
}
void Cal::mapCarId()
{
	map<int, int> carId;
	for (int i = 0; i < mCar.size(); i++)
	{
		//cout << mCross[i].getId() << " " << i << endl;
		carId[mCar[i].getId()] = i;
	}
	mMapCarId = carId;
}
void Cal::calDisMatrix()
{
	vector<vector<double> > disMatrix(mCross.size(), vector<double>(mCross.size(), MAXDISTANCE));

	
	//cout << mRoad.size() << endl << endl;
	for (int i = 0; i < mRoad.size(); i++)
	{
		int fromId = mRoad[i].getFrom();
		int toId = mRoad[i].getTo();
		//cout << i << " " << fromId << " " << toId << endl;
		int row = mMapCrossId[fromId];
		int col = mMapCrossId[toId];
		//cout << i << " " << row << " " << col << endl << endl;
		int length = mRoad[i].getLength();
		disMatrix[row][col] = length;
		if (mRoad[i].getIsDuplex())
		{
			disMatrix[col][row] = length;
		}
	}
	mDisMatrix = disMatrix;
}
void Cal::initTimeMatrix()
{
	vector<vector<double> > timeMatrix(mCross.size(), vector<double>(mCross.size(), MAXDISTANCE));

	//cout << mRoad.size() << endl << endl;
	for (int i = 0; i < mRoad.size(); i++)
	{
		int fromId = mRoad[i].getFrom();
		int toId = mRoad[i].getTo();
		//cout << i << " " << fromId << " " << toId << endl;
		int row = mMapCrossId[fromId];
		int col = mMapCrossId[toId];
		//cout << i << " " << row << " " << col << endl << endl;
		int length = mRoad[i].getLength();
		timeMatrix[row][col] = double(length/ mRoad[i].getSpeed());
		if (mRoad[i].getIsDuplex())
		{
			timeMatrix[col][row] = double(length / mRoad[i].getSpeed());
		}
	}
	mTimeMatrix = timeMatrix;
}
void Cal::calTimeMatrix(vector<Car> car)
{
	vector<vector<double> > timeMatrix(mCross.size(), vector<double>(mCross.size(), 0));
	//cout << mVote.size() << endl;
	//vector<vector<int> > vote(mCross.size(), vector<int>(mCross.size(), 0));
	for (int i = 0; i < car.size(); i++)
	{
		vector<int> route = car[i].getPlanRoute();
		for (int j = 0; j < route.size(); j++)
		{
			int indexRoad = mMapRoadId[route[j]];
			int speed = min(mRoad[indexRoad].getSpeed(), car[i].getSpeed());
			//mRoad[indexRoad].setSpeed(speed);
			int fromId = mRoad[indexRoad].getFrom();
			int toId = mRoad[indexRoad].getTo();

			int row = mMapCrossId[fromId];
			int col = mMapCrossId[toId];
			timeMatrix[row][col] += double(mRoad[indexRoad].getLength() / speed);
			timeMatrix[row][col] += mVote[row][col];

			/*if (mRoad[i].getIsDuplex())
			{
				timeMatrix[col][row] = double(mRoad[indexRoad].getLength() / speed);
			}*/
		}
	}
	for (int i = 0; i < timeMatrix.size(); i++)
	{
		for (int j = 0; j < timeMatrix[i].size(); j++)
		{
			mTimeMatrix[i][j] += timeMatrix[i][j];
		}
	}
}
vector<vector<double> > Cal::getDisMatrix()
{
	return mDisMatrix;
}
vector<vector<double> > Cal::getTimeMatrix()
{
	return mTimeMatrix;
}
void Cal::updateSpeedMatrix(vector<Car> car)
{
	//vector<vector<int> > vote(mCross.size(), vector<int>(mCross.size(), 0));
	for (int i = 0; i < car.size(); i++)
	{
		vector<int> route = car[i].getPlanRoute();
		for (int j = 0; j < route.size(); j++)
		{
			int indexRoad = mMapRoadId[route[j]];
			int speed = min(mRoad[indexRoad].getSpeed(),car[i].getSpeed());
			mRoad[indexRoad].setSpeed(speed);
		}
	}
}
void Cal::resetSpeedMatrix()
{
	for (int i = 0; i < mRoad.size(); i++)
	{
		mRoad[i].setSpeed(mSaveRoadSpeed[i]);
	}
}
void Cal::setVote(vector<Car> car)
{
	vector<vector<double> > vote(mCross.size(), vector<double>(mCross.size(), 0));
	for (int i = 0; i < car.size(); i++)
	{
		vector<int> route = car[i].getPlanRoute();
		for (int j = 0; j < route.size(); j++)
		{
			int indexRoad = mMapRoadId[route[j]];
			int speed = min(mRoad[indexRoad].getSpeed(), car[i].getSpeed());
			double add = 1.0/(speed * mRoad[indexRoad].getChannel());

			int fromId = mRoad[indexRoad].getFrom();
			int toId = mRoad[indexRoad].getTo();

			int row = mMapCrossId[fromId];
			int col = mMapCrossId[toId];

			vote[row][col] += add;
		}
	}
	mVote = vote;
}
void Cal::Floyd(vector<vector<double>> dis) 
{
	vector<vector<double> > minDis(dis.size(), vector<double>(dis.size(), MAXDISTANCE));
	mMinDis = minDis;
	
	vector<vector<int> > minDisPath(dis.size(), vector<int>(dis.size(), -1));
	for (int i = 0; i < dis.size(); i++)
		for (int j = 0; j < dis[i].size(); j++)
		{
			if (i == j) 
			{ 
				mMinDis[i][j] = 0; 
				//path[i][j] = to_string(i); 
			}
			mMinDis[i][j] = dis[i][j];
			minDisPath[i][j] = j;
		}
	//vector< vector< vector<int> > > vector_3D_3(dis.size(), vector<vector<int>>(dis.size(), vector<int>(dis.size(),-1)));
	vector< vector< vector<int> > > tmpMinDisPathRecord(dis.size(), vector<vector<int>>(dis.size()));
	mMinDisPathRecord = tmpMinDisPathRecord;

	for (int k = 0; k < dis.size(); k++)
		for (int i = 0; i < dis.size(); i++)
			for (int j = 0; j < dis.size(); j++)
			{
				if (mMinDis[i][k] + mMinDis[k][j] < mMinDis[i][j])
				{
					mMinDis[i][j] = mMinDis[i][k] + mMinDis[k][j];
					minDisPath[i][j] = minDisPath[i][k];
				}
			}
	/*for (int k = 0; k < dis.size(); k++)
	{
		for (int i = 0; i < dis.size(); i++)
		{
			cout << mMinDis[k][i] << " ";
		}
		cout << endl;
	}
	cout << endl;*/
		
	for (int i = 0; i < dis.size(); i++)
	{
		for (int j = 0; j < dis.size(); j++)
		{
			mMinDisPathRecord[i][j].push_back(i);
			int k = minDisPath[i][j];
			while(k != j)
			{
				mMinDisPathRecord[i][j].push_back(k);
				k = minDisPath[k][j];
			}
			mMinDisPathRecord[i][j].push_back(j);
		}
	}
}
void Cal::printMinDisPathRecord()
{
	for (int i = 0; i < mMinDisPathRecord.size(); i++)
	{
		for (int j = 0; j < mMinDisPathRecord[i].size(); j++)
		{
			cout << i << " "<<j << ":";
			for (int k = 0; k < mMinDisPathRecord[i][j].size(); k++)
			{
				cout << mMinDisPathRecord[i][j][k] << " ";
			}
			cout << endl;
		}
	}
}
void Cal::setRoadIdByCross()
{
	vector<vector<int > > tmpRoadIdByCross(mCross.size(), vector<int>(mCross.size(),0));
	for (int i = 0; i < mRoad.size(); i++)
	{
		int indexFrom = mMapCrossId[mRoad[i].getFrom()];
		int indexTo = mMapCrossId[mRoad[i].getTo()];
		tmpRoadIdByCross[indexFrom][indexTo] = mRoad[i].getId();
		if(mRoad[i].getIsDuplex())
			tmpRoadIdByCross[indexTo][indexFrom] = mRoad[i].getId();
	}
	mRoadIdByCross = tmpRoadIdByCross;
}
void Cal::setMinDisPathRecordForCar()
{
	for (int i = 0; i < mCar.size(); i++)
	{
		if (!mCar[i].getPreSet())
		{
			int indexFrom = mMapCrossId[mCar[i].getFrom()];
			int indexTo = mMapCrossId[mCar[i].getTo()];
			vector<int> actualCross;
			for (int j = 0; j < mMinDisPathRecord[indexFrom][indexTo].size(); j++)
			{
				actualCross.push_back(mCross[mMinDisPathRecord[indexFrom][indexTo][j]].getId());
			}
			mCar[i].setPlanCross(actualCross);
			vector<int> actualRoute;
			setRoadIdByCross();
			for (int j = 0; j < actualCross.size() - 1; j++)
			{
				int From = actualCross[j];
				int To = actualCross[j+1];

				int indexFrom = mMapCrossId[From];
				int indexTo = mMapCrossId[To];

				actualRoute.push_back(mRoadIdByCross[indexFrom][indexTo]);

			}
			mCar[i].setPlanRoute(actualRoute);
		}
	}
}
void Cal::setCarStartTimeForCar(vector<Car> car, vector<int> time)
{
	//cout << car.size() << " " << time[0] << endl;
	for (int i = 0; i < car.size(); i++)
	{
		int index = mMapCarId[car[i].getId()];
		//cout << index << endl;
		if(time[i] > mCar[index].getPlanTime())
			mCar[index].setActualTime(time[i]);
		else 
			mCar[index].setActualTime(mCar[index].getPlanTime());
	}
}
void Cal::mainFunction()
{
	calDisMatrix();
	initTimeMatrix();
	Floyd(mTimeMatrix);
	setMinDisPathRecordForCar();

	int count = 0;
	vector<Car> priorityCar;
	vector<int> starTimeMatrix;
	int time = 0;
	int currentTime = 0;
	int sendPriCarEachTime = 1000;
	for (int i = 0; i < mCar.size(); i++)
	{
		if (mCar[i].getPriority())
		{
			priorityCar.push_back(mCar[i]);
			time = (currentTime / sendPriCarEachTime) + 1;
			currentTime++;
			//cout << currentTime << endl;
			//cout << time << endl;
			starTimeMatrix.push_back(time);
			count++;
			if ((count == sendPriCarEachTime))
			{
				cout << priorityCar.size() << endl;
				calTimeMatrix(priorityCar);
				setVote(priorityCar);
				Floyd(mTimeMatrix);
				setMinDisPathRecordForCar();
				setCarStartTimeForCar(priorityCar, starTimeMatrix);
				count = 0;
				//cout << priorityCar[0].getActualTime() << endl;
				priorityCar.clear();
				starTimeMatrix.clear();
			}
		}
	}
	cout << priorityCar.size() << endl;
	calTimeMatrix(priorityCar);
	setVote(priorityCar);
	Floyd(mTimeMatrix);
	setMinDisPathRecordForCar();
	setCarStartTimeForCar(priorityCar, starTimeMatrix);
	count = 0;
	//cout << priorityCar[0].getActualTime() << endl;
	priorityCar.clear();
	starTimeMatrix.clear();


	vector<Car> nomalCar;
	int sendNomalCarEachTime = 2000;
	count = 0;
	currentTime = 0;
	int timePriEnd = time;
	for (int i = 0; i < mCar.size(); i++)
	{
		if (!mCar[i].getPreSet() && !mCar[i].getPriority())
		{
			nomalCar.push_back(mCar[i]);
			time = (currentTime / sendNomalCarEachTime) + timePriEnd;
			currentTime++;
			//cout << time << endl;
			starTimeMatrix.push_back(time);
			count++;

			if ((count == sendNomalCarEachTime ))
			{
				cout << nomalCar.size() << endl;
				calTimeMatrix(nomalCar);
				setVote(nomalCar);
				Floyd(mTimeMatrix);
				setMinDisPathRecordForCar();
				setCarStartTimeForCar(nomalCar, starTimeMatrix);
				//cout << nomalCar[0].getActualTime() << endl;
				count = 0;
				nomalCar.clear();
				starTimeMatrix.clear();
			}
		}
	}
	cout << nomalCar.size() << endl;
	calTimeMatrix(nomalCar);
	setVote(nomalCar);
	Floyd(mTimeMatrix);
	setMinDisPathRecordForCar();
	setCarStartTimeForCar(nomalCar, starTimeMatrix);
	//cout << nomalCar[0].getActualTime() << endl;
	count = 0;
	nomalCar.clear();
	starTimeMatrix.clear();

	//int c = 1;
	//for (int i = 0; i < mCar.size(); i++)
	//{
	//	int time = (c / 30) + 1;
	//	if (!mCar[i].getPreSet())
	//	{
	//		time = max(time, mCar[i].getPlanTime());
	//		mCar[i].setActualTime(time);
	//		//cout << mCar[i].getActualTime() << endl;
	//	}
	//	c = c + 1;
	//}
}
void Cal::printDisMatrix()
{
	cout << mDisMatrix.size() << endl;
	int count = 0;
	for (int i = 0; i < mDisMatrix.size(); i++)
	{
		for (int j = 0; j < mDisMatrix[i].size(); j++)
		{
			//cout << mAdjMatrix[i][j] << " ";
			if (mDisMatrix[i][j] < MAXDISTANCE)
				cout << count++ << " " << i << " " << j << endl;
		}
	}
}
void Cal::writeAns(string pathAnswer)
{
	ofstream answer(pathAnswer);
	for (int i = 0; i < mCar.size(); i++)
	{
		if (!mCar[i].getPreSet())
		{
			//cout << mCar[i].getActualTime() << endl;
			answer << '(' << mCar[i].getId() << ',' << mCar[i].getActualTime() << ',';
			vector<int> planRoute = mCar[i].getPlanRoute();
			for (int j = 0; j < planRoute.size(); j++)
			{
				answer << planRoute[j];
				if (j != planRoute.size() - 1)
					answer << ",";
			}
			answer << ')' << endl;
		}
	}
}
Cal::~Cal()
{
}
