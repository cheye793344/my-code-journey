#include"boss.h"

Boss::Boss(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Boss::ShowInfo()
{
	cout << "ְ����ţ�" << m_id
		<< "ְ��������" << m_name
		<< "���ű�ţ�" << m_departureid
		<< "�������ƣ�" << GetDepartureName()
		<< "��λְ�𣺹���˾��������" << endl;
}

string Boss::GetDepartureName()
{
	return string("�ܲ�");
}