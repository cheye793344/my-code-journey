#include"workerManager.h"
//���캯��
WorkerManager::WorkerManager()
{
	ifstream ifs;

	//�ļ�������
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open()) { 
		cout << "�㻹û�д���������Ŷ��" << endl;
		m_NewEmployeeNum = 0;//��ʼ����������
		m_TotalEmployeeNum = 0;//��ʼ��������
		m_EmployeeArray = NULL;//��ʼ������ָ��
		m_FileIsEmpty = true;//�ж��ļ�Ϊ��
		ifs.close();
		return;
	}

	//�����ļ����ļ�Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "����Ϊ�գ���ʼ���ְ���ɣ�" << endl;
		m_NewEmployeeNum = 0;//��ʼ����������
		m_TotalEmployeeNum = 0;//��ʼ��������
		m_EmployeeArray = NULL;//��ʼ������ָ��
		m_FileIsEmpty = true;//�ж��ļ�Ϊ��
		ifs.close();
		return;
	}

	//������������
	m_TotalEmployeeNum = get_EmploeeNum();
	cout << "����" << m_TotalEmployeeNum << "��ְ����Ϣ" << endl;
	m_EmployeeArray = new Worker * [m_TotalEmployeeNum];
	init_EmployeeArray();
}
//��ʾ�˵�
void WorkerManager::Show_Menu()
{
	cout << "��ӭʹ��ְ������ϵͳ��" << endl;
	cout << "0.�˳��������" << endl;
	cout << "1.����ְ����Ϣ" << endl;
	cout << "2.��ʾְ����Ϣ" << endl;
	cout << "3.ɾ��ְ����Ϣ" << endl;
	cout << "4.�޸�ְ����Ϣ" << endl;
	cout << "5.����ְ����Ϣ" << endl;
	cout << "6.���ձ������" << endl;
	cout << "7.���������Ϣ" << endl;
	cout << endl;
}
//���ְ����Ϣ
void WorkerManager::Add_Employee()
{
	cout << "��������Ҫ��ӵ�ְ��������" << endl;
	cin >> m_NewEmployeeNum;
	if (m_NewEmployeeNum <= 0) { cout << "��������ȷ��������"; }
	else
	{
		int NewSize = m_TotalEmployeeNum + m_NewEmployeeNum;//��������ռ��С
		Worker** NewSpace = new Worker* [NewSize];//���������¿ռ�

		//����ԭ����
		if (m_EmployeeArray != NULL)
		{
			for (int i = 0; i < m_TotalEmployeeNum; ++i) {
				NewSpace[i] = m_EmployeeArray[i];
			}
		}

		//����µ�ְ����Ϣ
		for (int i = 0; i < m_NewEmployeeNum; ++i) {
			int m_id;
			string m_name;
			int m_departureid;

			cout << "����������� "<<i+1<<" ��Ա���ı�� ���� ְλ���(1Ϊ��ͨԱ����2Ϊ����3Ϊ�ܲ�):" << endl;
			cin >> m_id >> m_name >> m_departureid;

			Worker* worker = NULL;
			//�ֲ�ͬ�������
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

			//����������Ϣ������������
				NewSpace[m_TotalEmployeeNum + i] = worker;
		}

		//�ͷ�ԭ����ָ����ڴ�
		if (m_EmployeeArray != NULL) {
			delete[]m_EmployeeArray;
		}

		//ʹԭ����ָ��������
		m_EmployeeArray = NewSpace;

		//������ְ������
		m_TotalEmployeeNum = NewSize;

		//���浽�ļ���
		save();

		m_FileIsEmpty = false;

		//��ʾ�ɹ��������
		cout << "�ɹ���� " << m_NewEmployeeNum << " ��Ա����" << endl;
	}
	system("pause");
}
//���������ļ�
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
//ͳ���ļ����Ѵ浵����
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
//��ʼ��ְ������
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
//��ʾְ����Ϣ
void WorkerManager::Show_Employee() {
	if (m_FileIsEmpty) {
		cout << "�㻹û�д���������Ŷ" << endl;
	}
	else {
		for (size_t i = 0; i < m_TotalEmployeeNum; i++) {
			m_EmployeeArray[i]->ShowInfo();
		}
	}

	system("pause");
}
//ɾ��ְ����Ϣ
void WorkerManager::Delete_Employee() {
	if (m_FileIsEmpty) {
		cout << "�㻹û�д���������Ŷ" << endl;
	}
	else {
		//����ְ�����ɾ��
		cout << "��������Ҫɾ����Ա���ı�ţ�" << endl;
		int target_id = 0;
		cin >> target_id;
		int index = IsExist(target_id);
		if (index == -1) {
			cout << "�����ڱ��Ϊ" << target_id << "��ְ������������ı���Ƿ���ȷ��" << endl;
		}
		else {
			for (size_t i = index; i < m_TotalEmployeeNum - 1; ++i) {
				m_EmployeeArray[i] = m_EmployeeArray[i + 1];
			}
			m_TotalEmployeeNum--;
			save();
			cout << "ɾ���ɹ���" << endl;
		}
	}
	system("pause");
}
//�޸�ְ����Ϣ
void WorkerManager::Modify_Employee() {
	if (m_FileIsEmpty) {
		cout << "�㻹δ����������Ŷ" << endl;
	}
	else {
		cout << "��������Ҫ�޸ĵ�ְ���ı�ţ�" << endl;
		int target_id;
		cin >> target_id;
		int index = IsExist(target_id);
		if (index != -1) {
			delete m_EmployeeArray[index];

			int new_id = 0;
			string new_name = "";
			int new_departure_id = 0;

			cout << "�����������µ�ְ����š�ְ�����������ű��(1.��ְͨ����2.����3.�ܲ�)��" << endl;

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
			cout << "�޸ĳɹ���";
		}
		else {
			cout << "û�в��ҵ����Ϊ" << target_id << "��ְ�������������Ƿ���ȷ��" << endl;
		}
	}
	system("pause");
}
//�ж�ְ���Ƿ����
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
//����ְ����Ϣ
void WorkerManager::Find_Employee() {
	if (m_FileIsEmpty) {
		cout << "�㻹û�д���������Ŷ" << endl;
	}
	else {
		cout << "��ѡ����ҷ�ʽ��" << endl;
		cout << "1.��ְ����Ų���" << endl;
		cout << "2.��ְ����������" << endl;

		int op;
		cin >> op;
		if (op == 1) {
			cout << "������Ҫ���ҵ�ְ���ı�ţ�" << endl;
			int target_id = 0;
			cin >> target_id;
			int index = IsExist(target_id);
			if (index != -1) {
				cout << "���ҳɹ���" << endl;
				m_EmployeeArray[index]->ShowInfo();
			}
			else {
				cout << "δ�ҵ�����ְ������������ı���Ƿ���ȷ��" << endl;
			}
		}
		else if (op == 2) {
			string target_name = "";
			cout << "������Ҫ���ҵ�ְ��������" << endl;
			cin >> target_name;
			bool is_found = false;
			for (size_t i = 0; i < m_TotalEmployeeNum; ++i) {
				if (m_EmployeeArray[i]->m_name == target_name) {
					is_found = true;
					cout << "���ҳɹ���" << endl;
					m_EmployeeArray[i]->ShowInfo();
				}
			}
			if (is_found == false) {
				cout << "�����ڸ���Ա������ȷ�����������Ƿ���ȷ��";
			}
		}
	}
	system("pause");
}
//��ְ����������
void WorkerManager::Sort_Employee() {
	if (m_FileIsEmpty) {
		cout << "�㻹û�д���������Ŷ" << endl;
		system("pause");
	}
	else {
		cout << "��ѡ������ʽ��" << endl;
		cout << "1.��ְ���������" << endl;
		cout << "2.��ְ����Ž���" << endl;

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
		cout << "������ɣ�" << endl;
		save();
		Show_Employee();
	}
}
//����ļ�
void WorkerManager::Clean_File() {
	cout << "ȷ����գ�" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.ȡ��" << endl;

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
		cout << "�������������" << endl;
	}
	system("pause");
}
//�˳�����
void WorkerManager::ExitSystem()
{
	cout << "�ټ���" << endl;
	system("pause");
	exit(0);
}
//��������
WorkerManager::~WorkerManager()
{
	if (m_EmployeeArray != NULL) {
		delete[]m_EmployeeArray;
		m_EmployeeArray = NULL;
	}
}