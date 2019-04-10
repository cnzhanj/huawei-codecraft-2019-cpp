#include "pch.h"
#include "Cal.h"


Cal::Cal()
{

	//vector<vector<vector<int> > > minDisPath(mCross.size(), vector<int>(mCross.size(), vector<int>(mCross.size(), MAXDISTANCE));
}
void Cal::init()
{
	string basePath = "F:\\硕士资料\\2018-2019\\HUAWEI\\2-map-training-2\\";
	string pathCar = basePath + "car.txt";
	string pathCross = basePath + "cross.txt";
	string pathRoad = basePath + "road.txt";
	string pathPresetAnswer = basePath + "presetAnswer.txt";
	Initial ini;
	ini.initialCar(pathCar);
	ini.initialCross(pathCross);
	ini.initialRoad(pathRoad);
	ini.initialPresetAnswer(pathPresetAnswer);

	mCar = ini.getCar();
	mCross = ini.getCross();
	mRoad = ini.getRoad();

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
void Cal::calDisMatrix()
{
	vector<vector<int> > disMatrix(mCross.size(), vector<int>(mCross.size(), MAXDISTANCE));
	mapCrossId();
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
vector<vector<int> > Cal::getDisMatrix()
{
	return mDisMatrix;
}
void Cal::Floyd(vector<vector<int>> dis) 
{
	vector<vector<int> > minDis(dis.size(), vector<int>(dis.size(), MAXDISTANCE));
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
			answer << '(' << mCar[i].getID() << ',' << mCar[i].getActualTime() << ',';
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
