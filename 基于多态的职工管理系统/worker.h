#pragma once
#include<iostream>
#include<cstring>
using namespace std;

class Worker
{
public:

	virtual void ShowInfo() = 0;

	virtual string GetDepartureName() = 0;

	int m_id;
	string m_name;
	int m_departureid;


};

