#include"boss.h"

Boss::Boss(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Boss::ShowInfo()
{
	cout << "职工编号：" << m_id
		<< "职工姓名：" << m_name
		<< "部门编号：" << m_departureid
		<< "部门名称：" << GetDepartureName()
		<< "岗位职责：管理公司所有事务" << endl;
}

string Boss::GetDepartureName()
{
	return string("总裁");
}