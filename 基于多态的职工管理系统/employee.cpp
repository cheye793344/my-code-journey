#include"employee.h"

Employee::Employee(int id, string name, int departureid)
{
	m_id = id;
	m_name = name;
	m_departureid = departureid;
}

void Employee::ShowInfo()
{
	cout << "ְ����ţ�" << m_id << " "
		<< "ְ��������" << m_name << " "
		<< "���ű�ţ�" << m_departureid << " "
		<< "�������ƣ�" << GetDepartureName() << " "
		<< "��λְ����ɾ����·ŵ�����" << endl;
}

string Employee::GetDepartureName()
{
	return string("Ա��");
}