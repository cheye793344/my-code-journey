#include"workerManager.h"
//构造函数
WorkerManager::WorkerManager()
{
	ifstream ifs;

	//文件不存在
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) { 
		cout << "你还没有创建过名单哦！" << endl;
		m_NewEmployeeNum = 0;//初始化新增人数
		m_TotalEmployeeNum = 0;//初始化总人数
		m_EmployeeArray = NULL;//初始化数组指针
		m_FileIsEmpty = true;//判断文件为空
		ifs.close();
		return;
	}

	//存在文件但文件为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "名单为空，开始添加职工吧！" << endl;
		m_NewEmployeeNum = 0;//初始化新增人数
		m_TotalEmployeeNum = 0;//初始化总人数
		m_EmployeeArray = NULL;//初始化数组指针
		m_FileIsEmpty = true;//判断文件为空
		ifs.close();
		return;
	}

	//存在已有名单
	m_TotalEmployeeNum = get_EmploeeNum();
	cout << "已有" << m_TotalEmployeeNum << "条职工信息" << endl;
	m_EmployeeArray = new Worker * [m_TotalEmployeeNum];
	init_EmployeeArray();
}
//显示菜单
void WorkerManager::Show_Menu()
{
	cout << "欢迎使用职工管理系统！" << endl;
	cout << "0.退出管理程序" << endl;
	cout << "1.增加职工信息" << endl;
	cout << "2.显示职工信息" << endl;
	cout << "3.删除职工信息" << endl;
	cout << "4.修改职工信息" << endl;
	cout << "5.查找职工信息" << endl;
	cout << "6.按照编号排序" << endl;
	cout << "7.清空所有信息" << endl;
	cout << endl;
}
//添加职工信息
void WorkerManager::Add_Employee()
{
	cout << "请输入需要添加的职工人数：" << endl;
	cin >> m_NewEmployeeNum;
	if (m_NewEmployeeNum <= 0) { cout << "请输入正确的人数！"; }
	else
	{
		int NewSize = m_TotalEmployeeNum + m_NewEmployeeNum;//计算所需空间大小
		Worker** NewSpace = new Worker* [NewSize];//堆区开辟新空间

		//拷贝原数据
		if (m_EmployeeArray != NULL)
		{
			for (int i = 0; i < m_TotalEmployeeNum; ++i) {
				NewSpace[i] = m_EmployeeArray[i];
			}
		}

		//添加新的职工信息
		for (int i = 0; i < m_NewEmployeeNum; ++i) {
			int m_id;
			string m_name;
			int m_departureid;

			cout << "请依次输入第 "<<i+1<<" 名员工的编号 姓名 职位编号(1为普通员工，2为经理，3为总裁):" << endl;
			cin >> m_id >> m_name >> m_departureid;

			Worker* worker = NULL;
			//分不同对象添加
			switch (m_departureid) {
			
			case 1:
				worker = new Employee(m_id,m_name,1);
				break;
			case 2:
				worker = new Manager(m_id, m_name, 2);
				break;
			case 3:
				worker = new Boss(m_id, m_name, 3);
				break;
			default:
				break;
			}

			//把新增的信息存入新数组中
				NewSpace[m_TotalEmployeeNum + i] = worker;
		}

		//释放原数组指向的内存
		if (m_EmployeeArray != NULL) {
			delete[]m_EmployeeArray;
		}

		//使原数组指向新数组
		m_EmployeeArray = NewSpace;

		//更新总职工人数
		m_TotalEmployeeNum = NewSize;

		//保存到文件中
		save();

		m_FileIsEmpty = false;

		//提示成功添加人数
		cout << "成功添加 " << m_NewEmployeeNum << " 名员工！" << endl;
	}
	system("pause");
}
//保存名单文件
void WorkerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	for (int i = 0; i < m_TotalEmployeeNum; i++) {
		ofs << m_EmployeeArray[i]->m_id << " "
			<< m_EmployeeArray[i]->m_name << " "
			<< m_EmployeeArray[i]->m_departureid << endl;
	}

	ofs.close();
}
//统计文件中已存档人数
int WorkerManager::get_EmploeeNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int departureId;

	int num = 0;

	while (ifs >> id && ifs >> name && ifs >> departureId) { ++num; }

	ifs.close();
	return num;
}
//初始化职工数组
void WorkerManager::init_EmployeeArray() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int departureId;

	int index = 0;

	while (ifs >> id && ifs >> name && ifs >> departureId) {
		Worker* worker = NULL;
		switch (departureId) {
		case 1:
			worker = new Employee(id, name, departureId);
			break;
		case 2:
			worker = new Manager(id, name, departureId);
			break;
		case 3:
			worker = new Boss(id, name, departureId);
			break;
		}
		 m_EmployeeArray[index] = worker;
		++index;
	}
}
//显示职工信息
void WorkerManager::Show_Employee() {
	if (m_FileIsEmpty) {
		cout << "你还没有创建过名单哦" << endl;
	}
	else {
		for (size_t i = 0; i < m_TotalEmployeeNum; i++) {
			m_EmployeeArray[i]->ShowInfo();
		}
	}

	system("pause");
}
//删除职工信息
void WorkerManager::Delete_Employee() {
	if (m_FileIsEmpty) {
		cout << "你还没有创建过名单哦" << endl;
	}
	else {
		//按照职工编号删除
		cout << "请输入你要删除的员工的编号：" << endl;
		int target_id = 0;
		cin >> target_id;
		int index = IsExist(target_id);
		if (index == -1) {
			cout << "不存在编号为" << target_id << "的职工，请检查输入的编号是否正确！" << endl;
		}
		else {
			for (size_t i = index; i < m_TotalEmployeeNum - 1; ++i) {
				m_EmployeeArray[i] = m_EmployeeArray[i + 1];
			}
			m_TotalEmployeeNum--;
			save();
			cout << "删除成功！" << endl;
		}
	}
	system("pause");
}
//修改职工信息
void WorkerManager::Modify_Employee() {
	if (m_FileIsEmpty) {
		cout << "你还未创建过名单哦" << endl;
	}
	else {
		cout << "请输入需要修改的职工的编号：" << endl;
		int target_id;
		cin >> target_id;
		int index = IsExist(target_id);
		if (index != -1) {
			delete m_EmployeeArray[index];

			int new_id = 0;
			string new_name = "";
			int new_departure_id = 0;

			cout << "请依次输入新的职工编号、职工姓名、部门编号(1.普通职工，2.经理，3.总裁)：" << endl;

			cin >> new_id >> new_name >> new_departure_id;
			Worker* worker = NULL;
			switch (new_departure_id) {
			case 1:
				worker = new Employee(new_id, new_name, new_departure_id);
				break;

			case 2:
				worker = new Manager(new_id, new_name, new_departure_id);
				break;

			case 3:
				worker = new Boss(new_id, new_name, new_departure_id);
				break;

			default:
				break;
			}
			m_EmployeeArray[index] = worker;
			save();
			cout << "修改成功！";
		}
		else {
			cout << "没有查找到编号为" << target_id << "的职工，请检查输入是否正确！" << endl;
		}
	}
	system("pause");
}
//判断职工是否存在
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < m_TotalEmployeeNum; ++i) {
		if (m_EmployeeArray[i]->m_id == id) {
			index = i;
			break;
		}
	}
	return index;
}
//查找职工信息
void WorkerManager::Find_Employee() {
	if (m_FileIsEmpty) {
		cout << "你还没有创建过名单哦" << endl;
	}
	else {
		cout << "请选择查找方式：" << endl;
		cout << "1.按职工编号查找" << endl;
		cout << "2.按职工姓名查找" << endl;

		int op;
		cin >> op;
		if (op == 1) {
			cout << "请输入要查找的职工的编号：" << endl;
			int target_id = 0;
			cin >> target_id;
			int index = IsExist(target_id);
			if (index != -1) {
				cout << "查找成功！" << endl;
				m_EmployeeArray[index]->ShowInfo();
			}
			else {
				cout << "未找到该名职工，请检查输入的编号是否正确！" << endl;
			}
		}
		else if (op == 2) {
			string target_name = "";
			cout << "请输入要查找的职工姓名：" << endl;
			cin >> target_name;
			bool is_found = false;
			for (size_t i = 0; i < m_TotalEmployeeNum; ++i) {
				if (m_EmployeeArray[i]->m_name == target_name) {
					is_found = true;
					cout << "查找成功！" << endl;
					m_EmployeeArray[i]->ShowInfo();
				}
			}
			if (is_found == false) {
				cout << "不存在该名员工，请确认姓名输入是否正确！";
			}
		}
	}
	system("pause");
}
//对职工进行排序
void WorkerManager::Sort_Employee() {
	if (m_FileIsEmpty) {
		cout << "你还没有创建过名单哦" << endl;
		system("pause");
	}
	else {
		cout << "请选择排序方式：" << endl;
		cout << "1.按职工编号升序" << endl;
		cout << "2.按职工编号降序" << endl;

		int op = 0;
		cin >> op;
		for (size_t i = 0; i < m_TotalEmployeeNum; ++i) {
			size_t min_or_max = i;
			for (size_t j = i + 1; j < m_TotalEmployeeNum; j++){
				if (op == 1) {
					if (m_EmployeeArray[min_or_max]->m_id > m_EmployeeArray[j]->m_id) {
						min_or_max = j;
					}
				}
				else {
					if (m_EmployeeArray[min_or_max]->m_id < m_EmployeeArray[j]->m_id) {
						min_or_max = j;
					}
				}
			}
			if (i != min_or_max) {
				Worker* temp = m_EmployeeArray[i];
				m_EmployeeArray[i] = m_EmployeeArray[min_or_max];
				m_EmployeeArray[min_or_max] = temp;
			}
		}
		cout << "排序完成！" << endl;
		save();
		Show_Employee();
	}
}
//清空文件
void WorkerManager::Clean_File() {
	cout << "确认清空？" << endl;
	cout << "1.确认" << endl;
	cout << "2.取消" << endl;

	int op = 0;
	cin >> op;

	if (op == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();

		if (m_EmployeeArray != NULL) {
			for (size_t i = 0; i < m_TotalEmployeeNum; ++i) {
				if (m_EmployeeArray[i] != NULL) {
					delete m_EmployeeArray[i];
				}
			}
			m_TotalEmployeeNum = 0;
			delete[] m_EmployeeArray;
			m_EmployeeArray = NULL;
			m_FileIsEmpty = true;
		}
		cout << "已清空所有数据" << endl;
	}
	system("pause");
}
//退出程序
void WorkerManager::ExitSystem()
{
	cout << "再见！" << endl;
	system("pause");
	exit(0);
}
//析构函数
WorkerManager::~WorkerManager()
{
	if (m_EmployeeArray != NULL) {
		delete[]m_EmployeeArray;
		m_EmployeeArray = NULL;
	}
}