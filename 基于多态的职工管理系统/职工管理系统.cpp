#include<iostream>
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
using namespace std;

int main()
{   //���Ժ���
	/*
	Test()
	{
	Worker* worker = NULL;
	worker = new Manager(2, "����",2);
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

		case 0:  //�˳�
			wm.ExitSystem();
			break;

		case 1:  //����
			wm.Add_Employee();
			break;

		case 2:  //��ʾ
			wm.Show_Employee();
			break;

		case 3:  //ɾ��
			wm.Delete_Employee();
			break;

		case 4:  //�޸�
			wm.Modify_Employee();
			break;

		case 5:  //����

			break;

		case 6:   //����

			break;

		case 7:  //���

			break;
		}
	}

	return 0;
}