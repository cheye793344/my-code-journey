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