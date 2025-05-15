#pragma once
#include<iostream>
#include"worker.h"
using namespace std;

class Employee : public Worker
{
public:

	Employee(int id, string name, int departureid);

	virtual void ShowInfo();

	virtual string GetDepartureName();

	~Employee();
};
