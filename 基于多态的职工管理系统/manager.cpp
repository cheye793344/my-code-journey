#include"manager.h"

Manager::Manager(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Manager::ShowInfo()
{
	cout << "ְ����ţ�" << m_id << " "
		<< "ְ��������" << m_name << " "
		<< "���ű�ţ�" << m_departureid << " "
		<< "�������ƣ�" << GetDepartureName() << " "
		<< "��λְ������ϰ��·ŵ����񣬲����·������Ա��" << endl;
}

string Manager::GetDepartureName()
{
	return string("����");
}