#include"employee.h"

Employee::Employee(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Employee::ShowInfo()
{
	cout << "职工编号：" << m_id << " "
		<< "职工姓名：" << m_name << " "
		<< "部门编号：" << m_departureid << " "
		<< "部门名称：" << GetDepartureName() << " "
		<< "岗位职责：完成经理下放的任务" << endl;
}

string Employee::GetDepartureName()
{
	return string("员工");
}