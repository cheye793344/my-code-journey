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

	int m_NewEmployeeNum;//新添加职工人数
	int m_TotalEmployeeNum;//总职工人数
	Worker** m_EmployeeArray;//职工数组指针
	bool m_FileIsEmpty;//判断文件是否为空的标志

	WorkerManager();//默认构造函数

	void Show_Menu();//显示菜单

	void Add_Employee();//添加职工信息

	void save();//保存名单文件

	int get_EmploeeNum();//获取已存档人数

	void init_EmployeeArray();//初始化职工数组

	void Show_Employee();//显示职工信息

	void Delete_Employee();//删除职工信息
	int IsExist(int id);//判断某职工是否存在

	void Modify_Employee();//修改职工信息

	~WorkerManager();//析构函数

	void ExitSystem();//退出程序
};