#include"manager.h"

Manager::Manager(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Manager::ShowInfo()
{
	cout << "职工编号：" << m_id << " "
		<< "职工姓名：" << m_name << " "
		<< "部门编号：" << m_departureid << " "
		<< "部门名称：" << GetDepartureName() << " "
		<< "岗位职责：完成老板下放的任务，并且下放任务给员工" << endl;
}

string Manager::GetDepartureName()
{
	return string("经理");
}