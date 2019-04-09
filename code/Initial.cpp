#include "pch.h"
#include "Initial.h"
#include<iostream>
#include<sstream>
using namespace std;
Initial::Initial()
{
}

/*
@in, src: ���ָ���ַ���
@in, delim: �ָ����ַ���
@in_out, dest: ����ָ���ÿ���ַ���
*/
void split(const string& src, const string& delim, vector<int>& dest)
{
	string str = src;
	string::size_type start = 1, index;
	string substr;

	index = str.find_first_of(delim, start);	//��str�в���(��ʼ��start) delim�������ַ��ĵ�һ�γ��ֵ�λ��
	while (index != string::npos)
	{
		substr = str.substr(start, index - start);
		int intSubtr = stoi(substr);
		dest.push_back(intSubtr);
		start = str.find_first_not_of(delim, index);	//��str�в���(��ʼ��index) ��һ��������delim���ַ����ֵ�λ��
		if (start == string::npos) return;

		index = str.find_first_of(delim, start);
	}
}

void Initial::setPresetCarRoute(vector<int> presetAnswerData)
{
	int carId = presetAnswerData[0];
	int index = mMapCarIdToIndex[carId];

	int carPlanTime = presetAnswerData[1];

	vector<int> carRoute;
	for (int i = 2; i < presetAnswerData.size(); i++)
	{
		carRoute.push_back(presetAnswerData[i]);
	}

	mCar[index].setPlanTime(carPlanTime);
	mCar[index].setPlanRoute(carRoute);
}
void Initial::initialCar(string pathCar)
{
	fstream input(pathCar);
	string str;
	int index = 0;
	while (getline(input, str))
	{
		if (str[0] == '#')
			continue;
		for(auto &s : str)
		{
			if (ispunct(s))
				s = ' ';
		}
		vector<int> carData;
		string result;
		stringstream input(str);
		//���������result�У�������res�� 
		while (input >> result)
		{
			carData.push_back(stoi(result));
		}
		Car car(carData);
		mCar.push_back(car);
		mMapCarIdToIndex[carData[0]] = index;
		index++;
	}
}
void Initial::initialCross(string pathCross)
{
	fstream input(pathCross);
	string str;
	while (getline(input, str))
	{
		if (str[0] == '#')
			continue;
		for (auto &s : str)
		{
			if (ispunct(s))
				s = ' ';
		}
		vector<int> crossData;
		string result;
		stringstream input(str);
		//���������result�У�������res�� 
		while (input >> result)
		{
			crossData.push_back(stoi(result));
		}
		Cross cross(crossData);
		mCross.push_back(cross);
	}
}
void Initial::initialRoad(string pathRoad)
{
	fstream input(pathRoad);
	string str;
	while (getline(input, str))
	{
		if (str[0] == '#')
			continue;
		for (auto &s : str)
		{
			if (ispunct(s))
				s = ' ';
		}
		vector<int> roadData;
		string result;
		stringstream input(str);
		//���������result�У�������res�� 
		while (input >> result)
		{
			roadData.push_back(stoi(result));
		}
		Road road(roadData);
		mRoad.push_back(road);
	}
}
void Initial::initialPresetAnswer(string pathPresetAnswer)
{
	fstream input(pathPresetAnswer);
	string str;
	int count = 0;
	while (getline(input, str))
	{
		if (str[0] == '#')
			continue;
		for (auto &s : str)
		{
			if (ispunct(s))
				s = ' ';
		}
		vector<int> presetAnswerData;
		string result;
		stringstream input(str);
		//���������result�У�������res�� 
		while (input >> result)
		{
			presetAnswerData.push_back(stoi(result));
		}
		setPresetCarRoute(presetAnswerData);
		//cout << count++ << endl;
	}
}
vector<Car> Initial::getCar()
{
	return mCar;
}
vector<Cross> Initial::getCross()
{
	return mCross;
}
vector<Road> Initial::getRoad()
{
	return mRoad;
}
Initial::~Initial()
{
}
