#pragma once
#include<iostream>
using namespace std;
#define FILENAME "employeeList.txt"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>

class WorkerManager{

public:

	int m_NewEmployeeNum;//�����ְ������
	int m_TotalEmployeeNum;//��ְ������
	Worker** m_EmployeeArray;//ְ������ָ��
	bool m_FileIsEmpty;//�ж��ļ��Ƿ�Ϊ�յı�־

	WorkerManager();//Ĭ�Ϲ��캯��

	void Show_Menu();//��ʾ�˵�

	void Add_Employee();//���ְ����Ϣ

	void save();//���������ļ�

	int get_EmploeeNum();//��ȡ�Ѵ浵����

	void init_EmployeeArray();//��ʼ��ְ������

	void Show_Employee();//��ʾְ����Ϣ

	void Delete_Employee();//ɾ��ְ����Ϣ
	int IsExist(int id);//�ж�ĳְ���Ƿ����

	void Modify_Employee();//�޸�ְ����Ϣ

	~WorkerManager();//��������

	void ExitSystem();//�˳�����
};