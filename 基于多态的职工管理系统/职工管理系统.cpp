#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{   //测试函数
	/*
	Test()
	{
	Worker* worker = NULL;
	worker = new Manager(2, "张三",2);
	worker->ShowInfo();
	}
	*/

	WorkerManager wm;

	wm.Show_Menu();

	int choice = 0;

	while (true)
	{
		cin >> choice;

		switch (choice) {

		case 0:  //退出
			wm.ExitSystem();
			break;

		case 1:  //增加
			wm.Add_Employee();
			break;

		case 2:  //显示
			wm.Show_Employee();
			break;

		case 3:  //删除
			wm.Delete_Employee();
			break;

		case 4:  //修改
			wm.Modify_Employee();
			break;

		case 5:  //查找

			break;

		case 6:   //排序

			break;

		case 7:  //清空

			break;
		}
	}

	return 0;
}