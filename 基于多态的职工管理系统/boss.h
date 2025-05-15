#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class Boss : public Worker
{
public:

	Boss(int id, string name, int departureid);

	virtual void ShowInfo();

	virtual string GetDepartureName();

	~Boss();
};

