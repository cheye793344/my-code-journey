/*
1.����Բ���
����

��дһ��Բ��Circle��ʵ�ְ뾶�����롢����ļ���������Circle��Ķ���������ʾ��

class Circle
{
private:
    double r;
public:
    void input();
    double area() const;
    void output() const;
};

Ҫ��ʵ��Circle���3����Ա�������������뾶���������������������������main�������ԡ�

int main()
{
    Circle myCircle;
    myCircle.input();
    myCircle.output();
    return 0;
}


����

����һ�У�����Բ�İ뾶(double����)��


���

���һ�У����Բ�����(����С�������λ)��


�������� 1

3
������� 1

28.27
��ʾ

1����������ǰʹ��������䣺cout<<setiosflags(ios::fixed)<<setprecision(2);�����������ʽ����Ҫ����iomanipͷ�ļ�

2��ʹ��acos(-1.0)���õ�Բ���ʵľ�ȷֵ���ɽ�������Ϊ���������磺const double PI = acos��-1.0������Ҫ����cmathͷ�ļ�

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

class Circle {
public:
    double r = 0;
    const double PI = acos(-1.0);
    Circle() {}
    void input() {
        cin >> r;
    }
    void output() {
        double area = PI * r * r;
            cout << setiosflags(ios::fixed) << setprecision(3) << area;
    }
};


int main()
{
    Circle myCircle;
    myCircle.input();
    myCircle.output();
    return 0;
}



2.������դ�������
����

һ��������������ͼ��ʾ��������������Χ��һ���ι�������������Χ����դ����դ���۸�Ϊ50Ԫ/�ף��������Ϊ240Ԫ/ƽ���ס�������Ϊ1.5�ף��������ĳ��Ϳ��ɼ������롣

ͼƬ.png

�������;��ι�������Rectangle��������дRectangle�࣬������main�������㲢���������դ������ۡ�

int main()
{
    int a = 50, b = 240;
    double x, y;
    cin >> x >> y;
    Rectangle rect1(x, y), rect2(x + 3, y + 3);
    cout << rect2.Perimeter()*a << "\n";
    double area;
    area = rect2.Area() - rect1.Area();
    cout << area*b << "\n";
    return 0;
}


����

�������ĳ��Ϳ�


���

���2��

��һ����դ�������

�ڶ����ǹ��������


�������� 1

2.4 1.2
������� 1

960
4752
�������� 2

2 1
������� 2

900
4320
��ʾ

������������ rect1(x, y)��ʾ��������ľ����ö��� rect2(x + 3, y + 3)��ʾ


#include <iostream>
using namespace std;

class Rectangle {
private:
    double x, y;

public:
    Rectangle(double x,double y):x(x),y(y) {}
    double Perimeter() {
        return 2 * x + 2 * y;
    }
    double Area() {
        return x*y;
    }
};

int main()
{
    int a = 50, b = 240;
    double x, y;
    cin >> x >> y;
    Rectangle rect1(x, y), rect2(x + 3, y + 3);
    cout << rect2.Perimeter() * a << "\n";
    double area;
    area = rect2.Area() - rect1.Area();
    cout << area * b << "\n";
    return 0;
}

3.ͼ����
����

������ͼ����Book��������

class Book
{
private:
    char *name;
    char *author;
    int sale;
public:
    Book();
    Book(const char *, const char *, int);
    Book(const Book &);
    void print() const;
    ~Book();
};

��ʵ��Book��ĳ�Ա������������main��������Book�ࡣ

int main()
{
    char name[110],author[110];
    int sale;
    cin.getline(name,110);
    cin.getline(author,110);
    cin>>sale;
    if(strcmp(name,"-1") == 0 && strcmp(author,"-1") == 0 && sale == -1){
        Book bk1;
        bk1.print();
    }else if(strcmp(name,"0") == 0 && strcmp(author,"0") == 0 && sale == 0){
        Book bk3;
        Book bk4(bk3);
        bk4.print();
    }else{
        Book bk2(name, author, sale);
        bk2.print();
    }
    return 0;
}

����

��main�����У������������ݣ���һ�����������(���Ȳ�����100�������пո�)���ڶ��������ߵ�����(���Ȳ�����100�������пո�),������������(��������)��������������Ӧ�ĳ�Ա�������ֱ�Ϊname,author��sale��������Ŀ�������Ĺ��캯������ʼ��������Ҫע����ǣ���Ŀ�����������캯�����ֱ����޲ι��캯�����вι��캯���Ϳ������캯����

����Ҫ�󣺵������name,author��sale��Ϊ-1��ʱ��ʹ���޲ι��캯������ʼ�����󣬴�ʱҪ��name����Ϊ"No name",author����Ϊ"No author",sale����Ϊ0�������붼Ϊ0��ʱ��ʹ�ÿ������캯�����������������main�����е�ʵ�ֿ����������ģ�Book bk1;Book bk2(bk1);bk2.print();�������һ��ʹ���вι��캯�����������


���

ʹ�����е�void print()�������������Ҫ�������name������author�����ĺ�����'\t'�����sale�������û��з����� Name:��Author:��Sale: ���涼��һ���ո񣬾���μ����������


�������� 1

C++ Primer
Stanley B. Lippman, et al.
1000
������� 1

Name: C++ Primer        Author: Stanley B. Lippman, et al.      Sale: 1000



#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;

class Book {
private:
    char* name;
    char* author;
    int sale;
public:
    Book(){
        const char* defaultName = "No name";
        const char* defaultAuthor = "No author";
        name = new char[strlen(defaultName) + 1];
        author = new char[strlen(defaultAuthor) + 1];
        strcpy(name, defaultName);
        strcpy(author, defaultAuthor);
        sale = 0;
    }
    Book(const char*n, const char* a, int s){
        name = new char[strlen(n) + 1];
        author = new char[strlen(a) + 1];
        strcpy(name, n);
        strcpy(author, a);
        sale = s;
    }
    Book(const Book& bk) {
        name = new char[strlen(bk.name) + 1];
        author = new char[strlen(bk.author) + 1];
        strcpy(name, bk.name);
        strcpy(author,bk.author);
        sale = bk.sale;
    }
    void print() const {
        cout << "Name: " << name << "\tAuthor: " << author << "\tSale: " << sale;
    }
    ~Book() {
        if (name != NULL) { delete[] name; }
        if (author != NULL) { delete[] author; }
    }

};

int main()
{
    char name[110], author[110];
    int sale;
    cin.getline(name, 110);
    cin.getline(author, 110);
    cin >> sale;
    if (strcmp(name, "-1") == 0 && strcmp(author, "-1") == 0 && sale == -1) {
        Book bk1;
        bk1.print();
    }
    else if (strcmp(name, "0") == 0 && strcmp(author, "0") == 0 && sale == 0) {
        Book bk3;
        Book bk4(bk3);
        bk4.print();
    }
    else {
        Book bk2(name, author, sale);
        bk2.print();
    }
    return 0;
}


4.������
����

��֪������Ķ������£�

class Date    //������
{
private:
    int Date_year;    //��
    int Date_month;    //��
    int Date_day;    //��
public:
    Date(int year, int month, int day);
    void show() const;    //�ԡ���-��-�ա���ʽ���������
};

�������к���������Ķ���������ʾ��

class Croster    //������
{
private:
    string name;
    Date birthday;
public:
    Croster();
    Croster(string name,int year,int month,int day);
    Croster(string name, Date date);
    void show() const;//��ʾ�����ͳ�������
};

Ҫ��ʵ�����������࣬��������main�������в��ԡ�

int main()
{
    int choice;
    string name;
    int y, m, d;
    while (cin >> choice)
    {
        if (choice == 0)
        {
            Croster stu0;
            stu0.show();
            cout<<'\n';
        }
        else if (choice == 1)
        {
            cin >> name >> y >> m >> d;
            Croster stu1(name, y, m, d);
            stu1.show();
            cout<<'\n';
        }
        else if (choice == 2)
        {
            cin >> name >> y >> m >> d;
            Date m_date(y, m, d);
            Croster stu2(name, m_date);
            stu2.show();
            cout<<'\n';
        }
        else if (choice == -1)
            return 0;
    }
    return 0;
}
����Ϊ�������ݣ�

��1������Ϊ0��ʱ��ֱ��ʹ��Croster����޲ι��캯��������1�����캯����ʵ�������󣬲������Name: NULL, Birthday: 0-0-0��

��2��������Ϊ1ʱ���������������������գ�ʹ��Croster��ĺ���4�������Ĺ��캯��������2�����캯����ʵ�������󣬲��������������������2��

��3��������Ϊ2ʱ���������������������գ�ʹ��Croster��ĺ���2�������Ĺ��캯��������3�����캯����ʵ�������󣬲��������������������3��

��4��������Ϊ-1ʱ���˳�����


����

�������Ϊ0�򲻼������룬�������Ϊ-1���˳������������Ϊ1��2��������������������ա�


���

������������


�������� 1

0
������� 1

Name: NULL, Birthday: 0-0-0

�������� 2

1
Zhangsan
2025
3
1
������� 2

Name: Zhangsan, Birthday: 2025-3-1
�������� 3

2
Lisi
2025
3
2
������� 3

Name: Lisi, Birthday: 2025-3-2
��ʾ

ð�źͶ��ź����һ���ո�



#include<iostream>
#include<cstring>
using namespace std;

class Date    //������
{
private:
    int Date_year = 0;    //��
    int Date_month = 0;    //��
    int Date_day = 0;    //��
public:
    Date(int year, int month, int day) :Date_year(year),Date_month(month),Date_day(day){}
    void show() const { cout << Date_year << "-" << Date_month << "-" << Date_day; }
   //�ԡ���-��-�ա���ʽ���������
};

class Croster    //������
{
private:
    string name;
    Date birthday;
public:
    Croster():name("NULL"),birthday(0,0,0) {}
    Croster(string name, int year, int month, int day):name(name),birthday(year,month,day) {}
    Croster(string name, Date date) :name(name),birthday(date){}
    void show() const {
        cout << "Name: " << name << ",Birthday: ";
        birthday.show();
    }//��ʾ�����ͳ�������
};

int main()
{
    int choice;
    string name;
    int y, m, d;
    while (cin >> choice)
    {
        if (choice == 0)
        {
            Croster stu0;
            stu0.show();
            cout << '\n';
        }
        else if (choice == 1)
        {
            cin >> name >> y >> m >> d;
            Croster stu1(name, y, m, d);
            stu1.show();
            cout << '\n';
        }
        else if (choice == 2)
        {
            cin >> name >> y >> m >> d;
            Date m_date(y, m, d);
            Croster stu2(name, m_date);
            stu2.show();
            cout << '\n';
        }
        else if (choice == -1)
            return 0;
    }
    return 0;
}

5.��Ԫ��
����

��֪ѡ����Subject��ѧ����Student�������£�ѧ������ѡ�������Ԫ��

class Subject    //ѡ����
{
private:
    double score[3];                //3�ſγɼ�
    const int SMath, SEng, SCpp;    //3�ſε�ѧ�֣��ֱ�Ϊ4��2��2
public:
    Subject(double score_math = 0, double score_eng = 0, double score_cpp = 0);
    void Input();            //����3�ſεĳɼ�
    friend class Student;    //��Ԫ��
};

class Student
{
private:
    string ID;        //ѧ��
    string name;       //����
    double GPA;        //ƽ��ѧ�ֻ�=���ɼ�1xѧ��1+�ɼ�2xѧ��2+�ɼ�3xѧ��3��/��ѧ��1+ѧ��2+ѧ��3��
public:
    Student();
    void CalculateGPA(const Subject &sub);    //����ƽ��ѧ�ֻ�
    void Input();                            //����ѧ�ź�����
    void Show(const Subject &sub)const;        //���������Ϣ
};

��ʵ�����������࣬��������main�������в��ԣ�

int main()
{
    int n;        //ѧ������
    cin >> n;
    Student *stu = new Student[n];
    Subject *sub = new Subject[n];
    for (int i = 0; i < n; i++)
    {
        stu[i].Input();
        sub[i].Input();
    }
    for (int i = 0; i < n; i++)
    {
        stu[i].CalculateGPA(sub[i]);
        stu[i].Show(sub[i]);
    }
    delete [] stu;
    delete [] sub;
    return 0;
}


����

��һ������ѧ������n��������������n��ѧ����ѧ�š�������3�ſεĳɼ�


���

���������


�������� 1

2
001
Jack
100
89
90
002
Mary
78
69
90
������� 1

ID: 001, Name: Jack
Math Eng Cpp
100 89 90
GPA: 94.75
ID: 002, Name: Mary
Math Eng Cpp
78 69 90
GPA: 78.75
�������� 2

3
001
Jack
100
80
90
002
Mary
100
98
99
003
Selina
99
98
98
������� 2

ID: 001, Name: Jack
Math Eng Cpp
100 80 90
GPA: 92.5
ID: 002, Name: Mary
Math Eng Cpp
100 98 99
GPA: 99.25
ID: 003, Name: Selina
Math Eng Cpp
99 98 98
GPA: 98.5
��ʾ

���ʱ��ð�źͶ��ź����һ���ո�ÿ�ſγɼ��������һ���ո񣬿γ�����֮����һ���ո񣬡�Cpp�����޿ո�


#include<iostream>
using namespace std;


class Subject    //ѡ����
{
private:
    double score[3];                //3�ſγɼ�
    const int SMath = 4;
    const int SEng = 2;
    const int SCpp = 2;
   //3�ſε�ѧ�֣��ֱ�Ϊ4��2��2
public:
    Subject(double score_math = 0, double score_eng = 0, double score_cpp = 0) :score{score_eng,score_eng,score_cpp}{}
    void Input() { for (int i = 0; i < 3; ++i) cin >> score[i]; }           //����3�ſεĳɼ�
    friend class Student;    //��Ԫ��
};

class Student
{
private:
    string ID;        //ѧ��
    string name;       //����
    double GPA = 0;        //ƽ��ѧ�ֻ�=���ɼ�1xѧ��1+�ɼ�2xѧ��2+�ɼ�3xѧ��3��/��ѧ��1+ѧ��2+ѧ��3��
public:
    Student() {}
    void CalculateGPA(const Subject& sub) { GPA = (sub.score[0] * double(sub.SMath) + sub.score[1] * double(sub.SEng) +sub.score[2] * double(sub.SCpp)) / (double(sub.SMath)+ double(sub.SEng) + double(sub.SCpp)); }  //����ƽ��ѧ�ֻ�
    void Input() { cin >> ID >> name; }                            //����ѧ�ź�����
    void Show(const Subject & sub)const {
            cout << "ID: " << ID << ", " << "Name: " << name << endl;
            cout << "Math Eng Cpp" << endl;
            cout << sub.score[0] << " " << sub.score[1] << " " << sub.score[2] << " " << endl;
            cout << "GPA: " << GPA << endl;
        }      //���������Ϣ
};


int main()
{
    int n;        //ѧ������
    cin >> n;
    Student* stu = new Student[n];
    Subject* sub = new Subject[n];
    for (int i = 0; i < n; i++)
    {
        stu[i].Input();
        sub[i].Input();
    }
    for (int i = 0; i < n; i++)
    {
        stu[i].CalculateGPA(sub[i]);
        stu[i].Show(sub[i]);
    }
    delete[] stu;
    delete[] sub;
    return 0;
}
6.�ù�����ͳ��
����

��д����ͳ��ĳ�ù�ס�޿��˵�������Ҫ��������˵�������������˵ı�ţ����Ⱥ�˳���Զ����ɣ��������Լ���������

ʹ������main�����Գ�����в���

int main(){
    Hotel h[100];
    h[0].add("Susan");
    h[1].add("Peter");
    h[2].add("John");
    h[3].add("Mary");
    h[4].add("Alice");
    string name;
    cin>>name;

    for(int i=0;i<Hotel::getTotal();i++)
    {
        if(h[i].getName()==name)
        {
            h[i].print();
            break;
        }
    }

    return 0;
}

����

����һ�У�������˵�����(������100���ַ�����Ӣ�Ĵ�Сд��ĸ��ɵ��ַ���)��


���

���һ�У�������˵ı�ţ����������������ո�ָ���


�������� 1

Peter
������� 1

2 Peter 5


#include<iostream>
#include<cstring>
using namespace std;

class Hotel {
private:
    static int total;
    string name;
    int ID;

public:
    Hotel(const string n="", int id=0) :name(n), ID(id) {}
    static int getTotal() { return total; }
    void add(const string &n) {
        name = n;
        ID = total + 1;
        ++total;
    }
    void print() { cout << ID << " " << name << " " << total << endl; }
    string getName() { return name; }

};

int main() {
    Hotel h[100];
    h[0].add("Susan");
    h[1].add("Peter");
    h[2].add("John");
    h[3].add("Mary");
    h[4].add("Alice");
    string name;
    cin >> name;

    for (int i = 0; i < Hotel::getTotal(); i++)
    {
        if (h[i].getName() == name)
        {
            h[i].print();
            break;
        }
    }

    return 0;
}
int Hotel::total = 0;

7.TestConstClass
����

��������print������main���������岢ʵ��TestConstClass�࣬ͨ����Ŀ�Ĳ��ԡ�

void print(const TestConstClass & tcs) {
    cout << tcs.get() << '\n';
}

int main() {
    string tmp;
    TestConstClass tcs;
    while (cin >> tmp) {
        tcs.set(tmp);
        print(tcs);
    }

    return 0;
}

����

�������ɸ��ַ���


���

���������ÿ���ַ�����ԭ���������ַ�����ÿ�����ռһ��


�������� 1

test
������� 1

test
��Դ

xyy

#include<iostream>
using namespace std;

class TestConstClass {
public:
    string String;
    TestConstClass() :String("") {}
    string get() const{ return String; }
    void set(const string &s) {
        String = s;
    }

};
void print(const TestConstClass& tcs) {
    cout << tcs.get() << '\n';
}

int main() {
    string tmp;
    TestConstClass tcs;
    while (cin >> tmp) {
        tcs.set(tmp);
        print(tcs);
    }

    return 0;
}
8.TableTennisPlayer
����

��дTableTennisPlayer���RatedPlayer�ࣨRatedPlayer��̳�TableTennisPlayer�ࣩ������TableTennisPlayer��Ķ���������ʾ��

class TableTennisPlayer {
private:
    string firstname;
    string lastname;
    bool hasTable;
public:
    TableTennisPlayer(const string&, const string&, bool);
    string FirstName() const;
    string LastName() const;
    bool HasTable() const;
};
ʵ�ֺ�ͨ������main�����Ĳ��ԣ�

int main() {
    string firstname, lastname;
    bool hasTable;
    int rating;
    char flag;
    while (cin >> flag) {
        if (flag == 'T') {
            cin >> firstname >> lastname >> hasTable;
            TableTennisPlayer tp(firstname, lastname, hasTable);
            if (tp.HasTable())
                cout << tp.FirstName() << " " << tp.LastName() << " has a table.\n";
            else
                cout << tp.FirstName() << " " << tp.LastName() << " hasn't a table.\n";
        }
        else if (flag == 'R') {
            cin >> firstname >> lastname >> hasTable >> rating;
            RatedPlayer rp(rating, firstname, lastname, hasTable);
            if (rp.HasTable())
                cout << rp.FirstName() << " " << rp.LastName() << " has a table. The rating is " << rp.Rating() << ".\n";
            else
                cout << rp.FirstName() << " " << rp.LastName() << " doesn't have a table. The rating is " << rp.Rating() << ".\n";
        }
    }
    return 0;
}

����

������У�ÿһ����'T'��'R'��ͷ��'T'��ʾ���н���������һ��TableTennisPlayer�������Ϣ������ firstname��lastname �� hasTable���Ƿ���ƹ����̨����'R'��ʾ���н���������һ��RatedPlayer�������Ϣ������ firstname��lastname��hasTable �� rating��ѡ�ֵĵ÷֣���


���

һ�������Ӧһ�������������main����


�������� 1

T Bill Gates 1
������� 1

Bill Gates has a table.
�������� 2

R Jike Zhang 0 19000
������� 2

Jike Zhang doesen't have a table. The rating is 19000.
��ʾ

bool���͵����룺0��ʾfalse��1��ʾtrue

��Դ

xuyanyan

#include<iostream>
#include<cstring>
using namespace std;

class TableTennisPlayer {
private:
    string firstname;
    string lastname;
    bool hasTable;
public:
    TableTennisPlayer(const string &fname, const string &lname, bool hTable) :firstname(fname),lastname(lname),hasTable(hTable){}
    string FirstName() const { return firstname; }
    string LastName() const { return lastname; }
    bool HasTable() const { return hasTable; }
    };
    class RatedPlayer :public TableTennisPlayer {
    private:
        int rating;
    public:
        RatedPlayer(int rate,const string& fname, const string& lname, bool hTable) :TableTennisPlayer(fname, lname, hTable), rating(rate) {}
        int Rating() { return rating; }
    };
int main() {
    string firstname, lastname;
    bool hasTable;
    int rating;
    char flag;
    while (cin >> flag) {
        if (flag == 'T') {
            cin >> firstname >> lastname >> hasTable;
            TableTennisPlayer tp(firstname, lastname, hasTable);
            if (tp.HasTable())
                cout << tp.FirstName() << " " << tp.LastName() << " has a table.\n";
            else
                cout << tp.FirstName() << " " << tp.LastName() << " hasn't a table.\n";
        }
        else if (flag == 'R') {
            cin >> firstname >> lastname >> hasTable >> rating;
            RatedPlayer rp(rating, firstname, lastname, hasTable);
            if (rp.HasTable())
                cout << rp.FirstName() << " " << rp.LastName() << " has a table. The rating is " << rp.Rating() << ".\n";
            else
                cout << rp.FirstName() << " " << rp.LastName() << " doesn't have a table. The rating is " << rp.Rating() << ".\n";
        }
    }
    return 0;
}

8.Person��Student
����

ʵ��һ��Person�࣬��ʵ��һ��Student�࣬Ҫ��Student��̳�Person�࣬ͨ�����²��ԣ�

int main(){
    Person * p;

    p = new Person;
    p->input();
    p->display();
    delete p;

    p = new Student;
    p->input();
    p->display();
    delete p;

    return 0;
}

����

����������У���һ��Ϊһ���������������ո񣩣��ڶ���Ϊһ��ѧ�ź�һ��������ѧ�š��������������ո񣩣�ѧ�ź�����֮���ÿո���


���

���Ϊ���У���һ��Ϊһ���������ڶ���Ϊѧ�ź�������ѧ�ź�����֮���ÿո���


�������� 1

Mary
001 Mary
������� 1

Mary
001 Mary


#include<cstring>
#include<iostream>
using namespace std;

class Person{
protected:
    string name;
public:
    Person() {}
    virtual void input() { cin >> name; }
    virtual void display() { cout << name; }
    virtual ~Person() {}
};

class Student :public Person {
private:
    string ID;
public:
    Student() {}
    void input()override { cin  >> ID >> name; }
    void display()override { cout << ID << " "  << name; }
};

int main() {
    Person* p;

    p = new Person;
    p->input();
    p->display();
    delete p;

    p = new Student;
    p->input();
    p->display();
    delete p;

    return 0;
}

9.ͼ����Ʒ
����

��д�����࣬��һ�����ǣ�

class Item_base {
protected:
    string ISBN;
    double price;
public:
    Item_base(const string& book_ISBN = "", double sales_price = 0.0);
    string get_ISBN() const;
    virtual double net_price(int) const;
    virtual ~Item_base();
};
�ڶ������ǣ�

class Bulk_Item : public Item_base {
public:
    Bulk_Item(const string& book_ISBN = "", double sales_price = 0.0, int min_qty = 0, double discount = 0.0);
    double net_price(int) const;
private:
    int min_qty;
    double discount;
};
ʵ�����������࣬ͨ������main�����Ĳ���

int main()
{
    Item_base book("0-001-0001-1", 10.0);
    Bulk_Item bulk1("0-001-0001-1", 10.0, 5, 0.1);
    Bulk_Item bulk2("0-001-0001-1", 10.0, 10, 0.2);

    int num;
    while (cin >> num) {

        cout << bulk1.get_ISBN() << "\t" << num << "\t";

        Item_base* p;
        if (num >= 10) p = &bulk2;
        else if (num >= 5) p = &bulk1;
        else p = &book;

        cout << p->net_price(num) << "\n";
    }

    return 0;
}

����

ͼ���������


���

��������ͼ���ISBN, ���������Լ��ܵļ۸񡣣����main������


�������� 1

2
6
11
������� 1

0 - 001 - 0001 - 1     2     20
0 - 001 - 0001 - 1     6     54
0 - 001 - 0001 - 1     11    88

10.Vehicle��
����

���һ��������Vehicle��������������Car����Truck����Car�������ơ���ɫ���ؿ����������ݳ�Ա����Truck�������ơ���ɫ���������������ݳ�Ա��

ʹ������main���������Ĳ���:

int main(){
    Vehicle *p;
    char type;
    char name[110],color[110];
    int pas;
    double cap;
    while(cin>>type){
        cin>>name>>color;
        if(type == 'C'){
            cin>>pas;
            Car car(name,color,pas);
            p = &car;
            p->display();
        }else if(type == 'T'){
            cin>>cap;
            Truck truck(name,color,cap);
            p = &truck;
            p->display();
        }
    }
    return 0;
}


����

�������룬ÿ������Ŀ�ͷ��'C'����'T'��'C'��ʾCar��'T'��ʾTruck������������Car��Truck����Ϣ��Car����Ϣ�������ƣ���ɫ���ؿ�����Truck����Ϣ�������ƣ���ɫ��������������ʱ���ó�����Vehicle��ָ��ָ�����������ʵ�ֲ�ͬ����display()�����Ķ�̬��


���

���ݲ�ͬ�����࣬�����ͬ��Ϣ����������������


�������� 1

C Benz black 3
T Dongfeng white 8.5
������� 1

Car name:Benz Car color:black Car passager:3
Truck name:Dongfeng Truck color:white Truck capacity:8.5
��ʾ

Vehicle�пɰ������ƺ���ɫ���ݳ�Ա�������д��麯�����ṩ�ӿ������Ϣ����ʾ����������Car��Truck�и�����Ҫʵ�ִ��麯���Լ���ӳ�Ա�����麯����const�޶����﷨Ϊ��virtual void display() const = 0;

��ϸ����������ĸ�ʽ�����Ϊ���У�ÿ�еĲ�ͬ��Ŀ֮����һ���ո������


#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

class Vehicle {
protected:
    char type[110];
    char color[110];
public:
    Vehicle(const char* type, const char* color) {
        strcpy(this->type,type);
        strcpy(this->color, color);
    }
    virtual void display()const = 0;
    virtual ~Vehicle() {};
};

class Car :public Vehicle{
private:
    int passenger;
public:
    Car(const char* type, const char* color, const int passenger):Vehicle(type, color),passenger(passenger) {}
    void display()const override{ cout << "Car name:" << type << " Car color:" << color << " Car passager:" << passenger << endl; }
};

class Truck: public Vehicle{
private:
    double capacity;
public:
    Truck(const char* type, const char* color, double capacity) :Vehicle(type, color), capacity(capacity) {}
    void display()const override { cout << "Truck name:" << type << " Truck color:" << color << " Truck capacity:" << capacity << endl; }
};

int main() {
    Vehicle* p;
    char type;
    char name[110], color[110];
    int pas;
    double cap;
    while (cin >> type) {
        cin >> name >> color;
        if (type == 'C') {
            cin >> pas;
            Car car(name, color, pas);
            p = &car;
            p->display();
        }
        else if (type == 'T') {
            cin >> cap;
            Truck truck(name, color, cap);
            p = &truck;
            p->display();
        }
    }
    return 0;
}
11.��ά��״��3DShape��
����

��д���򣬼��㳤���塢Բ�������ı�����������Ҫ���ȶ���һ��������C3DShape���£�

class C3DShape {
public:
    C3DShape() {}
    virtual double area() const = 0;
    virtual void input() = 0;
    virtual double volume() const = 0;
    virtual ~C3DShape() {}
};

ʹ��C3DShape���������������ࡢԲ�����ࡢ���࣬������������ʵ�ִ�C3DShape��̳����Ĵ��麯����ʹ�����´���ͨ�����ԡ�

void work(C3DShape *s) {
    s->input();
    cout << s->area() << " " << s->volume() << endl;
    delete s;
}

int main(){
    char c;
    while (cin >> c){
        switch (c){
        case 'y':
            work(new Cylinder());
            break;
        case 'c':
            work(new Cuboid());
            break;
        case 'q':
            work(new Ball());
            break;
        default:
            break;
        }
    }
    return 0;
}


����

����������У�ÿ��������һ���ַ�'c'��'y'��'q'���ֱ��ʾ���볤���塢Բ����������Ϣ���������Ƕ�Ӧ�����롣


���

ÿ�������Ӧһ���������ʾ����״�ı������������Կո�ָ���


�������� 1

c 3 4 5
y 3 5
q 5
������� 1

94 60
150.796 141.372
314.159 523.599
��ʾ

pi�ľ���Ҫ�㹻������ʹ�� const double pi = acos(-1);

#include <iostream>
#include <cmath>
using namespace std;

const double pi = acos(-1.0);
class C3DShape {
public:
    C3DShape() {}
    virtual double area() const = 0;
    virtual void input() = 0;
    virtual double volume() const = 0;
    virtual ~C3DShape() {}
};

class Cylinder:public C3DShape {
private:
    double r;
    double h;
public:
    Cylinder(){}
    double area()const override{ return pi * r * r * 2 + 2 * pi * r * h; }
    void input()override { cin >> r >> h; }
    double volume() const override { return pi * r * r * h; }
    ~Cylinder() {}
};

class Cuboid:public C3DShape {
private:
    double l;
    double w;
    double h;
public:
    Cuboid(){}
    double area()const override { return l * w * 2 + w * h * 2 + l * h * 2; }
    void input()override { cin >> l >> w >> h; }
    double volume() const override { return l * w * h; }
    ~Cuboid() {}
};

class Ball:public C3DShape {
private:
    double r;
public:
    Ball(){}
    double area()const override { return 4 * pi * r * r; }
    void input()override { cin >> r; }
    double volume() const override { return 4 * pi * r * r * r / 3; }
    ~Ball() {}
};

void work(C3DShape* s) {
    s->input();
    cout << s->area() << " " << s->volume() << endl;
    delete s;
}

int main() {
    char c;
    while (cin >> c) {
        switch (c) {
        case 'y':
            work(new Cylinder());
            break;
        case 'c':
            work(new Cuboid());
            break;
        case 'q':
            work(new Ball());
            break;
        default:
            break;
        }
    }
    return 0;
}

12.Singer��
����

ʵ��һ��Singer�࣬ͨ�����²��ԣ�

int main(){
    Singer s1,s2;
    cin>>s1>>s2;
    cout<<s1<<"\n"<<s2<<"\n";

    if(s1>s2)
        cout<<s1.getName()<<"'s score is higher than "<<s2.getName()<<"'s.\n";
    else if(s1==s2)
        cout<<s1.getName()<<"'s score is equal to "<<s2.getName()<<"'s.\n";
    else
        cout<<s1.getName()<<"'s score is lower than "<<s2.getName()<<"'s.\n";

    return 0;
}


����

����������У�ǰ����Ϊ����s1����Ϣ��������Ϊ����s2����Ϣ��ÿλ���ֵ���Ϣ�����������������ܰ����ո񣩡��Ա�char���ͣ������䣨int���ͣ� �� ������float��double���ͣ����������������


���

���Ϊ���У�ǰ���зֱ��Ǹ���s1��s2����Ϣ�������и���s1��s2�ȽϽ�������s1��s2�ıȽϽ�������ǵķ����ıȽϽ��һ�£�������μ�������


�������� 1

Wang Xiaohua
F 28 99.5
Zhang Dali
M 26 98
������� 1

Wang Xiaohua F 28 99.5
Zhang Dali M 26 98
Wang Xiaohua's score is higher than Zhang Dali's.
��ʾ

C++������������ignore()��������������������еĻ��з����Լ�����ε���

#include <iostream>
#include <string>

using namespace std;

class Singer {
private:
    string name;
    char gender;
    int age;
    double score;

public:

    friend istream& operator>>(istream& is, Singer& s) {
        getline(is, s.name);
        is >> s.gender >> s.age >> s.score;
        is.ignore();
        return is;
    }


    friend ostream& operator<<(ostream& os, const Singer& s) {
        os << s.name << " " << s.gender << " " << s.age << " " << s.score;
        return os;
    }


    bool operator>(const Singer& other) const {
        return score > other.score;
    }


    bool operator==(const Singer& other) const {
        return score == other.score;
    }


    string getName() const {
        return name;
    }
};

int main() {
    Singer s1, s2;
    cin >> s1 >> s2;
    cout << s1 << "\n" << s2 << "\n";

    if (s1 > s2)
        cout << s1.getName() << "'s score is higher than " << s2.getName() << "'s.\n";
    else if (s1 == s2)
        cout << s1.getName() << "'s score is equal to " << s2.getName() << "'s.\n";
    else
        cout << s1.getName() << "'s score is lower than " << s2.getName() << "'s.\n";

    return 0;
}

13.Sales_data��
����

ʵ������Sales_data�ࣨ����������Ԫ��������

class Sales_data {
//������š�����������
friend istream & operator>>(istream&, Sales_data &);
//�����š�����������;���
friend ostream & operator<<(ostream &, const Sales_data &);
friend bool operator==(const Sales_data &, const Sales_data &);
friend bool operator!=(const Sales_data &, const Sales_data &);
// for "+", assume that both objects refer to the same book
friend Sales_data operator+(const Sales_data &, const Sales_data &);

public:
    Sales_data(): units_sold(0), revenue(0.0) {}
    Sales_data(const string & s, unsigned n, double r): bookNo(s), units_sold(n), revenue(r) {}
    string get_bookNo() const;
    // for "+=", assume that both objects refer to the same book
    Sales_data & operator+=(const Sales_data &);

private:
    double avg_price() const;  //������ۣ�������������������
    string bookNo;        //���
    unsigned units_sold; //����
    double revenue;      //����
};
ͨ������main�����Ĳ���

int main(){
    Sales_data item1,item2;
    while(cin>>item1>>item2){
        cout<<item1<<"\n"<<item2<<"\n";
        if(item1==item2)
            cout<<item1.get_bookNo()<<" equals "<<item2.get_bookNo()<<"\n";
        if(item1!=item2)
            cout<<item1.get_bookNo()<<" doesn't equal "<<item2.get_bookNo()<<"\n";
        cout<<(item1+item2)<<"\n";
        item1 += item2;
        cout<<item1<<"\n";
    }
    return 0;
}

����

����������ݣ�ÿ���������У�ÿ�б�ʾ1��Sales_data������������š�����������


���

����ÿ�����ݣ����5�У�����μ�main�������������


�������� 1

001 10 100.0
001 10 100.0
������� 1

001 10 100 10
001 10 100 10
001 equals 001
001 20 200 10
001 20 200 10
�������� 2

002 5 250
003 8 400
������� 2

002 5 250 50
003 8 400 50
002 doesn't equal 003
002 13 650 50
002 13 650 50
��ʾ

��̨����main�������ύʱȥ��main����

��Դ

xyy


#include<iostream>
#include<string>
using namespace std;

class Sales_data {
    //������š�����������
    friend istream& operator>>(istream&, Sales_data&);//
    //�����š�����������;���
    friend ostream& operator<<(ostream&, const Sales_data&);//
    friend bool operator==(const Sales_data&, const Sales_data&);//
    friend bool operator!=(const Sales_data&, const Sales_data&);//
    // for "+", assume that both objects refer to the same book
    friend Sales_data operator+(const Sales_data&, const Sales_data&);//

public:
    Sales_data() : units_sold(0), revenue(0.0) {}
    Sales_data(const string& s, unsigned n, double r) : bookNo(s), units_sold(n), revenue(r) {}
    string get_bookNo() const;
    // for "+=", assume that both objects refer to the same book
    Sales_data& operator+=(const Sales_data&);//

private:
    double avg_price() const;  //������ۣ������������������� //
    string bookNo;        //���
    unsigned units_sold; //����
    double revenue;      //����
};

istream& operator>>(istream& is, Sales_data& item) {
    is >> item.bookNo >> item.units_sold >> item.revenue;
    return is;
}
//�����š�����������;���
ostream& operator<<(ostream&os, const Sales_data&item) {
    os << item.bookNo << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();
    return os;
}
bool operator==(const Sales_data&lhs, const Sales_data&rhs) {
    return lhs.bookNo == rhs.bookNo;
}
bool operator!=(const Sales_data&lhs, const Sales_data&rhs) {
    return !(lhs == rhs);
}
// for "+", assume that both objects refer to the same book
Sales_data operator+(const Sales_data& lhs, const Sales_data& rhs) {
    Sales_data sum = lhs;
    sum += rhs;
    return sum;
}

Sales_data& Sales_data:: operator+=(const Sales_data&rhs) {
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

double Sales_data::avg_price() const {
    if (units_sold == 0)return 0.0;
    return revenue / units_sold;
}

string Sales_data::get_bookNo() const{
    return bookNo;
}

int main() {
    Sales_data item1, item2;
    while (cin >> item1 >> item2) {
        cout << item1 << "\n" << item2 << "\n";
        if (item1 == item2)
            cout << item1.get_bookNo() << " equals " << item2.get_bookNo() << "\n";
        if (item1 != item2)
            cout << item1.get_bookNo() << " doesn't equal " << item2.get_bookNo() << "\n";
        cout << (item1 + item2) << "\n";
        item1 += item2;
        cout << item1 << "\n";
    }
    return 0;
}

14.Complex
����

ʵ�����¸�����Complex��ͨ��������ؽأ�ʵ�ָ�������������Լ�������㡣

class Complex{
private:
    double x;
    double y;
public:
    Complex(double x = 0.0, double y = 0.0);
    Complex & operator+=(const Complex &);
    Complex & operator-=(const Complex &);
    Complex & operator*=(const Complex &);
    Complex & operator/=(const Complex &);
    friend Complex operator+(const Complex &, const Complex &);
    friend Complex operator-(const Complex &, const Complex &);
    friend Complex operator*(const Complex &, const Complex &);
    friend Complex operator/(const Complex &, const Complex &);
    friend bool operator==(const Complex &, const Complex &);
    friend bool operator!=(const Complex &, const Complex &);
    friend ostream & operator<<(ostream &, const Complex &);
    friend istream & operator>>(istream &, Complex &);
};
ͨ���������������ԣ�

int main(){
    Complex c1, c2;
    cin >> c1 >> c2;

    cout << "c1 = " << c1 << "\n" << "c2 = " << c2 << "\n";
    cout << "c1+c2 = " << c1 + c2 << "\n";
    cout << "c1-c2 = " << c1 - c2 << "\n";
    cout << "c1*c2 = " << c1 * c2 << "\n";
    cout << "c1/c2 = " << c1 / c2 << "\n";
    cout << (c1 += c2) << "\n";
    cout << (c1 -= c2) << "\n";
    cout << (c1 *= c2) << "\n";
    cout << (c1 /= c2) << "\n";
    cout << (c1 == c2) << " " << (c1 != c2) << endl;

    return 0;
}

����

���������У�ÿ��Ϊ�������������ֱ��ʾһ��������ʵ�����鲿��


���

���һ����11�У��ֱ��ʾ����֮��ĸ������������μ����������������


�������� 1

-4 6
2 5
������� 1

c1 = -4 + 6i
c2 = 2 + 5i
c1+c2 = -2 + 11i
c1-c2 = -6 + 1i
c1*c2 = -38 + -8i
c1/c2 = 0.758621 + 1.10345i
-2 + 11i
-4 + 6i
-38 + -8i
-4 + 6i
0 1
��ʾ

��̨����main�������ύʱȥ��main����

�����ӷ���ʽ��(a + bi) + (c + di) = (a + c) + (b + d)i

����������ʽ��(a + bi) - (c + di) = (a - c) + (b - d)i

�����˷���ʽ��(a + bi) * (c + di) = (ac - bd) + (ad + bc)i

����������ʽ��(a + bi) / (c + di) = [(ac + bd) / (cc + dd)] + [(bc - ad) / (cc + dd)]i


#include<iostream>
using namespace std;

class Complex {
private:
    double x;
    double y;
public:
    Complex(double x = 0.0, double y = 0.0):x(x),y(y) {}
    Complex& operator+=(const Complex&);
    Complex& operator-=(const Complex&);
    Complex& operator*=(const Complex&);
    Complex& operator/=(const Complex&);
    friend Complex operator+(const Complex&, const Complex&);
    friend Complex operator-(const Complex&, const Complex&);
    friend Complex operator*(const Complex&, const Complex&);
    friend Complex operator/(const Complex&, const Complex&);
    friend bool operator==(const Complex&, const Complex&);
    friend bool operator!=(const Complex&, const Complex&);
    friend ostream& operator<<(ostream&, const Complex&);
    friend istream& operator>>(istream&, Complex&);
};
Complex& Complex::operator+=(const Complex& other) {
    x += other.x;
    y += other.y;
    return *this;
}
Complex& Complex::operator-=(const Complex& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}
Complex& Complex::operator*=(const Complex& other) {
    double new_x = x * other.x - y * other.y;
    double new_y = x * other.y + y * other.x;
    x = new_x;
    y = new_y;
    return *this;
}
Complex& Complex::operator/=(const Complex& other) {
    double denominator = other.x * other.x + other.y * other.y;
    double new_x = (x * other.x + y * other.y) / denominator;
    double new_y = (y * other.x - x * other.y) / denominator;
    x = new_x;
    y = new_y;
    return *this;
}
Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.x + rhs.x, lhs.y + rhs.y);
}
Complex operator-(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.x - rhs.x, lhs.y - rhs.y);
}
Complex operator*(const Complex& lhs, const Complex& rhs) {
    double x = lhs.x * rhs.x - lhs.y * rhs.y;
    double y = lhs.x * rhs.y + lhs.y * rhs.x;
    return Complex(x, y);
}
Complex operator/(const Complex& lhs, const Complex& rhs) {
    double denominator = rhs.x * rhs.x + rhs.y * rhs.y;
    double x = (lhs.x * rhs.x + lhs.y * rhs.y) / denominator;
    double y = (lhs.y * rhs.x - lhs.x * rhs.y) / denominator;
    return Complex(x, y);
}
bool operator==(const Complex& lhs, const Complex& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const Complex& lhs, const Complex& rhs) {
    return !(lhs == rhs);
}
ostream& operator<<(ostream& os, const Complex& c) {
    os << c.x << " + " << c.y << "i";
    return os;
}
istream& operator>>(istream& is, Complex& c) {
is >> c.x >> c.y;
return is;
}

int main() {
    Complex c1, c2;
    cin >> c1 >> c2;

    cout << "c1 = " << c1 << "\n" << "c2 = " << c2 << "\n";
    cout << "c1+c2 = " << c1 + c2 << "\n";
    cout << "c1-c2 = " << c1 - c2 << "\n";
    cout << "c1*c2 = " << c1 * c2 << "\n";
    cout << "c1/c2 = " << c1 / c2 << "\n";
    cout << (c1 += c2) << "\n";
    cout << (c1 -= c2) << "\n";
    cout << (c1 *= c2) << "\n";
    cout << (c1 /= c2) << "\n";
    cout << (c1 == c2) << " " << (c1 != c2) << endl;

    return 0;
}
15.String��
����

ʵ������String�ࣺ

class String{
private:
    char * s;
public:
    String();
    String(const char *);
    String(const String &);
    ~String();
    String & operator=(const char *);
    String & operator=(const String &);
    String operator+(const char *);
    String operator+(const String &);
    String & operator+=(const char *);
    String & operator+=(const String &);
    friend istream & operator>>(istream &, String &);
    friend ostream & operator<<(ostream &, const String &);
    friend bool operator==(const String &, const char *);
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const char *);
    friend bool operator!=(const String &, const String &);
};
ʹ������main�������в��ԣ�

int main(){
     String s;
     s += "hello";
     cout<<s<<"\n";

     String s1("String1");
     String s2("copy of ");
     s2 += "String1";
     cout << s1 << "\n" << s2 << "\n";

     String s3;
     cin >> s3;
     cout << s3 << "\n";

     String s4("String4"), s5(s4);
     cout << (s5 == s4) << "\n";
     cout << (s5 != s4) << "\n";

     String s6("End of "), s7("my string.");
     s6 += s7;
     cout << s6 << endl;

     return 0;
};

����

s3��ֵ


���

������������������


�������� 1

String3
������� 1

hello
String1
copy of String1
String3
1
0
End of my string.
��ʾ

��̨����main�������ύʱȥ��main����

��Դ

xyy


#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
using namespace std;

class String {
private:
    char* s;
public:
    String() {
        s = new char[1];
        s[0] = '\0';
    }
    String(const char* str) {
        s = new char[strlen(str) + 1];
        strcpy(s, str);
    }
    String(const String& other) {
        s = new char[strlen(other.s) + 1];
        strcpy(s, other.s);
    }
    ~String() {
        if (s != NULL)delete[] s;
    }
    String& operator=(const char* str) {
        if (s)delete[] s;
        s = new char[strlen(str) + 1];
        strcpy(s, str);
        return *this;
    }
    String& operator=(const String& other) {
        if (s)delete[] s;
        s = new char[strlen(other.s) + 1];
        strcpy(s, other.s);
        return *this;
    }
    String operator+(const char* str) {
        String result;
        delete[] result.s;
        result.s = new char[strlen(s) + strlen(str) + 1];
        strcpy(result.s, s);
        strcat(result.s, str);
        return result;
    }
    String operator+(const String& other) {
        String result;
        delete[] result.s;
        result.s = new char[strlen(s) + strlen(other.s) + 1];
        strcpy(result.s, s);
        strcat(result.s, other.s);
        return result;
    }
    String& operator+=(const char* str) {
        size_t len;
        len = strlen(s) + strlen(str);
        char* new_s = new char[len + 1];
        strcpy(new_s, s);
        strcat(new_s, str);
        delete[] s;
        s = new_s;
        return *this;
    }
    String& operator+=(const String& other) {
        return *this += other.s;
    }
    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, const String&);
    friend bool operator==(const String&, const char*);
    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const char*);
    friend bool operator!=(const String&, const String&);
};
istream& operator>>(istream& is, String& other) {
    if (other.s)delete[] other.s;
    char temp[1024];
    is >> temp;
    other.s = new char[strlen(temp) + 1];
    strcpy(other.s, temp);
    return is;
}
ostream& operator<<(ostream& os, const String& other) {
    os << other.s;
    return os;
}
bool operator==(const String& lhs, const char* rhs) {
    return strcmp(lhs.s, rhs) == 0;
}
bool operator==(const String& lhs, const String& rhs) {
    return strcmp(lhs.s, rhs.s) == 0;
}
bool operator!=(const String& lhs, const char* rhs) {
    return !(lhs == rhs);
}
bool operator!=(const String& lhs, const String& rhs) {
    return !(lhs == rhs);
}

int main() {
    String s;
    s += "hello";
    cout << s << "\n";

    String s1("String1");
    String s2("copy of ");
    s2 += "String1";
    cout << s1 << "\n" << s2 << "\n";

    String s3;
    cin >> s3;
    cout << s3 << "\n";

    String s4("String4"), s5(s4);
    cout << (s5 == s4) << "\n";
    cout << (s5 != s4) << "\n";

    String s6("End of "), s7("my string.");
    s6 += s7;
    cout << s6 << endl;

    return 0;
};

16.CheckedPtr
����

����(++)���Լ�(--)�����������������������������ʵ�֣����������ṩ������ָ�����Ϊ���������е�Ԫ�ء����磬����������CheckedPtr������ָ��һ��int���鲢Ϊ�������е�Ԫ���ṩ���ʼ�顣

class CheckedPtr{
    public:
        CheckedPtr(int * b, int * e) : beg(b), end(e), curr(b){}
        CheckedPtr & operator ++(); // prefix ++
        CheckedPtr & operator --(); // prefix --
        CheckedPtr   operator ++(int); // postfix ++
        CheckedPtr   operator --(int); // postfix --
        int * GetBeg();
        int * GetEnd();
        int * GetCurr();
    private:
        int * beg;  // pointer to beginning of the array
        int * end;  // one past the end of the array
        int * curr; // current position within the array
};
ʵ��CheckedPtr�ಢͨ������main�������ԡ�

int main(){    
    int n;
    cin>>n;
    int * array = new int[n];

    for(int i=0;i<n;i++)
        cin>>array[i];

    CheckedPtr cp(array, array+n);

    for(;cp.GetCurr()<cp.GetEnd();cp++)
        cout<<*cp.GetCurr()<<" ";
    cout<<"\n";

    for(--cp;cp.GetCurr()>cp.GetBeg();cp--)
        cout<<*cp.GetCurr()<<" ";
    cout<<*cp.GetCurr()<<endl;

    delete [] array;

    return 0;
} 

����

����Ϊ���У���һ�б�ʾ����ĳ���n���ڶ��б�ʾ��n����


���

���Ϊ���У���һ�������������ĵ�0�������һ��Ԫ�أ��ڶ��з���������������Ԫ�أ��ο����������


�������� 1 

5
1 2 3 4 5
������� 1

1 2 3 4 5 
5 4 3 2 1
��ʾ

��̨����main�������ύʱȥ��main����

��Դ

xyy


#include<iostream>

using namespace std;

class CheckedPtr {
public:
    CheckedPtr(int* b, int* e) : beg(b), end(e), curr(b) {}
    CheckedPtr& operator ++() {     
        curr++;
        return *this;
    } // prefix ++
    CheckedPtr& operator --() {
        curr--;
        return *this;
    } // prefix --
    CheckedPtr   operator ++(int) {
        CheckedPtr temp(*this);
        curr++;
        return temp;
    }// postfix ++
    CheckedPtr   operator --(int) {
        CheckedPtr temp(*this);
        curr--;
        return temp;
    }// postfix --
    int* GetBeg() { return beg; }
    int* GetEnd() { return end; }
    int* GetCurr() { return curr; }
private:
    int* beg;  // pointer to beginning of the array
    int* end;  // one past the end of the array
    int* curr; // current position within the array
};

int main() {
    int n;
    cin >> n;
    int* array = new int[n];

    for (int i = 0; i < n; i++)
        cin >> array[i];

    CheckedPtr cp(array, array + n);

    for (; cp.GetCurr() < cp.GetEnd(); cp++)
        cout << *cp.GetCurr() << " ";
    cout << "\n";

    for (--cp; cp.GetCurr() > cp.GetBeg(); cp--)
        cout << *cp.GetCurr() << " ";
    cout << *cp.GetCurr() << endl;

    delete[] array;

    return 0;
}

16.Swap
����

�ú���ģ��Swapʵ�ֶԲ�ͬ���͵����ݽ��н�����

��ʹ���������������ԡ�

int main()
{
    int a1, a2;
    std::cin >> a1 >> a2;
    Swap(a1, a2);
    std::cout << a1 << "," << a2 << std::endl;

    double b1, b2;
    std::cin >> b1 >> b2;
    Swap(b1, b2);
    std::cout << b1 << "," << b2 << std::endl;

    char c1, c2;
    std::cin >> c1 >> c2;
    Swap(c1, c2);
    std::cout << c1 << "," << c2 << std::endl;

    return 0;
}

ע�⣬����ֻ��Ҫ�ύSwap�������룬ͷ�ļ���main����ϵͳ�Ѿ��ṩ��


����

���빲���С���һ�����������ڶ����������������������ַ�


���

��������С�ÿһ��Ϊ��Ӧ���봦���Ľ����������������ö��Ÿ���


�������� 1 

2 3
1.2 2.3
a b
������� 1

3,2
2.3,1.2
b,a


#include<iostream>
using namespace std;

template<typename T>
void Swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

int main()
{
    int a1, a2;
    std::cin >> a1 >> a2;
    Swap(a1, a2);
    std::cout << a1 << "," << a2 << std::endl;

    double b1, b2;
    std::cin >> b1 >> b2;
    Swap(b1, b2);
    std::cout << b1 << "," << b2 << std::endl;

    char c1, c2;
    std::cin >> c1 >> c2;
    Swap(c1, c2);
    std::cout << c1 << "," << c2 << std::endl;

    return 0;
}

17.SortFunctionTemplate
����

�ú���ģ��ʵ����������롢�������������������������ԣ�

int main()
{
    const int LEN = 5;
    int type;
    while (std::cin >> type)
    {
        switch (type) 
        {
            case 0: 
            {
                int a1[LEN];
                Input<int>(a1, LEN); Sort<int>(a1, LEN); Output<int>(a1, LEN);
                break;
            }
            case 1: 
            {
                char a2[LEN];
                Input(a2, LEN); Sort(a2, LEN); Output(a2, LEN); 
                break; 
            }
            case 2: 
            {
                double a3[LEN];
                Input(a3, LEN); Sort(a3, LEN); Output(a3, LEN);
                break;
            }
        }
    }

    return 0;
}

ע�⣺����ֻ�ύInput��Sort�� Output����ģ����롣���ಿ��ϵͳ�Ѱ�����


����

�����������������ݡ�ÿ������Ϊ���У���һ������type(0��1��2)���ڶ���Ϊ��Ӧ�����5��Ԫ�ء�


���

����ÿһ��������ݣ������������һ�������������Ԫ���ö��żӿո���룬���һ��Ԫ�غ��滻�С�


�������� 1 

0 
3 6 1 4 5
1 
A B C B A
������� 1

1, 3, 4, 5, 6
A, A, B, B, C

#include<iostream>
#include<algorithm>
using namespace std; 

template<typename T>
void Input(T arr[], int len) {
    for (int i = 0; i < len; ++i) {
        cin >> arr[i];
    }
}
template<typename T>
void Sort(T arr[], int len) {
    sort(arr, arr + len);
}
template<typename T>
void Output(T arr[], int len) {
    for (int i = 0; i < len; ++i) {
        if(i==0)cout << arr[i];
        else cout << ", " << arr[i];
    }
    cout << endl;
}

int main()
{
    const int LEN = 5;
    int type;
    while (std::cin >> type)
    {
        switch (type)
        {
        case 0:
        {
            int a1[LEN];
            Input<int>(a1, LEN); Sort<int>(a1, LEN); Output<int>(a1, LEN);
            break;
        }
        case 1:
        {
            char a2[LEN];
            Input(a2, LEN); Sort(a2, LEN); Output(a2, LEN);
            break;
        }
        case 2:
        {
            double a3[LEN];
            Input(a3, LEN); Sort(a3, LEN); Output(a3, LEN);
            break;
        }
        }
    }

    return 0;
}

18.Search
����

���һ��ģ�庯����ʵ����һ�������������в��Ҹ��������Ƿ���ڣ�����������������������������С���±꣬��������ڣ����-1

int main()
{
    int n;
    std::cin >> n;
    int *nValues  = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> nValues[i];
    }
    int d;
    std::cin >> d;
    std::cout << Search(nValues, n, d) << std::endl;
    delete[] nValues;

    double f;
    std::cin >> n;
    double *dValues = new double[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> dValues[i];
    }
    std::cin >> f;
    std::cout << Search(dValues, n, f) << std::endl;
    delete[] dValues;

    std::cin >> n;
    char *cValues = new char[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> cValues[i];
    }
    char c;
    std::cin >> c;
    std::cout << Search(cValues, n, c) << std::endl;
    delete[] cValues;

    return 0;
}


����

���빲�������ݣ�ÿ������ռ���С�

��һ���һ������n1���ڶ�����n1�������������д���������n

�ڶ����һ������n2���ڶ�����n2���������������д����Ҹ�����d

�������һ������n3���ڶ�����n3���ַ��������д������ַ�c


���

����ÿһ�����룬����������ݴ��ڣ����������С�±�(�±��0��ʼ��)���������-1��


�������� 1

7
1 1 2 5 8 10 13
8
5
-1.0 1.1 1.2 1000.10101 8.9
3.5
4
B J F U
j
������� 1

4
-1
-1
��ʾ

ʹ��ģ�庯��

template <class T>
int Search(const T * array, int arrayLen, const T & value)

#include<iostream>
using namespace std;

template <class T>
int Search(const T* array, int arrayLen, const T& value) {
    for (int i = 0; i < arrayLen; ++i) {
        if (array[i] == value)return i;
    }
    return -1;
}

int main()
{
    int n;
    std::cin >> n;
    int* nValues = new int[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> nValues[i];
    }
    int d;
    std::cin >> d;
    std::cout << Search(nValues, n, d) << std::endl;
    delete[] nValues;

    double f;
    std::cin >> n;
    double* dValues = new double[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> dValues[i];
    }
    std::cin >> f;
    std::cout << Search(dValues, n, f) << std::endl;
    delete[] dValues;

    std::cin >> n;
    char* cValues = new char[n];
    for (int i = 0; i < n; i++)
    {
        std::cin >> cValues[i];
    }
    char c;
    std::cin >> c;
    std::cout << Search(cValues, n, c) << std::endl;
    delete[] cValues;

    return 0;
}

19.TVector3
����

����һ����ģ�壨Vector�������ݳ�Ա���£�

template<typename T>
class Vector
{
private:
    T x, y, z;
//...
}
���Vector��������������������

int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;
    Vector<double> v1(a, b, c), v2(v1), v3, v4;
    double d;
    std::cin >> d;
    v4 = d * v1 + v2;

    std::cout << v4 <<std::endl;

    Vector<double>  v;
    std::cin >> v;

    int flag = (v4 == v);
    std::cout << flag << std::endl; 

    return 0;
}


����

������


���

������


�������� 1 

3 4 5
2.2
9.6 12.8 16
������� 1

9.6 12.8 16
1
��ʾ

��������������Ȳ�Ҫʹ��==�������� fabs(a - b) < epsilon������epsilon�����òο���ĿҪ��ľ��ȣ����籾�� 1e-6 �Ϳ���

��Դ

xyy


#include<iostream>
#include<cmath>
using namespace std;

template<typename T>
class Vector;
template<typename T>
ostream& operator<<(ostream& os, Vector<T>& v);
template<typename T>
istream& operator>>(istream& is, Vector<T>& v);
template<typename T>
Vector<T> operator*(T d, Vector<T> v);
template<typename T>
bool operator==(Vector<T> lhs, Vector<T> rhs);
template<typename T>
Vector<T> operator+(Vector<T> lhs, Vector<T> rhs);

template<typename T>
class Vector
{
private:
    T x, y, z;
public:
    Vector(T a = 0, T b = 0, T c = 0) :x(a), y(b), z(c) {}
    friend ostream& operator<< <>(ostream& os, Vector<T>& v);
    friend istream& operator>> <>(istream& is, Vector<T>& v);
    friend Vector<T> operator* <>(T d, Vector<T> v);
    friend bool operator== <>(Vector<T> lhs, Vector<T> rhs);
    friend Vector<T> operator+ <>(Vector<T> lhs, Vector<T> rhs);
};
template<typename T>
ostream& operator<<(ostream& os, Vector<T>& v) {
    os << v.x << " " << v.y << " " << v.z;
    return os;
}
template<typename T>
istream& operator>>(istream& is, Vector<T>& v) {
    is >> v.x >> v.y >> v.z;
    return is;
}
template<typename T>
Vector<T> operator*(T d, Vector<T> v) {
    return Vector<T>(v.x * d, v.y * d, v.z * d);
}
template<typename T>
bool operator==(Vector<T> lhs, Vector<T> rhs) {
    const double epsilon = 1e-6;
    return fabs(lhs.x - rhs.x) < epsilon &&
        fabs(lhs.y - rhs.y) < epsilon &&
        fabs(lhs.z - rhs.z) < epsilon;
}
template<typename T>
Vector<T> operator+(Vector<T> lhs, Vector<T> rhs) {
    return Vector<T>(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

int main()
{
    double a, b, c;
    std::cin >> a >> b >> c;
    Vector<double> v1(a, b, c), v2(v1), v3, v4;
    double d;
    std::cin >> d;
    v4 = d * v1 + v2;

    std::cout << v4 << std::endl;

    Vector<double>  v;
    std::cin >> v;

    int flag = (v4 == v);
    std::cout << flag << std::endl;

    return 0;
}

20.StackClassTemplate
����

ʵ��һ��Stack��ģ�岢������һģ��

template<class T, int SIZE = 20>
class Stack
{
private: 
    T array[SIZE];        //���飬���ڴ��ջ��Ԫ��
    int top;                //ջ��λ�ã������±꣩
public:
    Stack();                //���캯������ʼ��ջ
    void Push(const T & );  //Ԫ����ջ
    T Pop();                //ջ��Ԫ�س�ջ
    void Clear();           //��ջ���
    const T & Top() const;  //����ջ��Ԫ��
    bool Empty() const;     //����ջ�Ƿ�Ϊ��
    bool Full() const;     //�����Ƿ�ջ��
    int Size();            //���ص�ǰջ��Ԫ�ظ���
};

���Ժ�����

int main()
{
    Stack<int, 10> intStack;

    int n;
    cin >> n; //���뱣֤ n<=10
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        intStack.Push(temp);
    }

    for (int i = 0; i < n; i++)
    {
        cout << intStack.Top() << " ";
        intStack.Pop();
    }
    cout<<endl;

    if(intStack.Empty())
        cout<<"Now, intStack is empty."<<endl;

    Stack<string,5> stringStack;
    stringStack.Push("One");
    stringStack.Push("Two");
    stringStack.Push("Three");
    stringStack.Push("Four");
    stringStack.Push("Five");
    cout<<"There are "<<stringStack.Size()<<" elements in stringStack."<<endl;
    stringStack.Clear();
    if(stringStack.Empty()) 
        cout<<"Now, there are no elements in stringStack"<<endl;

    return 0;
}


����

�ο�����


���

�ο�����


�������� 1 

3
1
2
3
������� 1

3 2 1 
Now, intStack is empty.
There are 5 elements in stringStack.
Now, there are no elements in stringStack
��ʾ

��1��ջ�Ĳ�����ջ�����У�������ջ������洢��top��ʾ�����±꣬array������ջ��Ԫ�ء�

��2�����캯����ջ���г�ʼ������Ϊû���βΣ����������ｫtop��ֵ��-1��Ҳ����ջΪ�ա�����Ȼ��Ҳ�ɽ�top��ֵ��0�������ж�ջ�Ƿ�Ϊ�պ���ջ����Ӧ�����������ı䣩

��3��push�����ǽ�Ԫ����ջ���ں����������ж�ջ�Ƿ������������Ļ���Ԫ����ջ�������Ҫ�޸�array�����top�±ꡣ

(4��pop������ջ��Ԫ�س�ջ���ں����������ж�ջ�Ƿ�Ϊ�գ����ռ���ջ��Ԫ�س�ջ��������ջ����Ԫ��ֵ���޸��±��ֵ���������˳�������exit��1����䣩��

��5��clear�������ջ������top���¸�ֵΪ-1��

��6��Top��������ջ��Ԫ�أ����ջ���գ���ջ��Ԫ�ط��أ������˳�������exit��1����䣩��

��7��empty�����ж�ջ�Ƿ�Ϊ�գ����top==-1��գ����򲻿ա�

��8��full���������Ƿ�ջ�������top==SIZE-1��������������

��9��size�������ص�ǰջ��Ԫ�ظ��������������ĸ���Ա���Ա�ʾջ��Ԫ�ظ�������������ֵ���ɡ�


#include<iostream>
using namespace std;

template<class T, int SIZE = 20>
class Stack
{
private:
    T array[SIZE];        //���飬���ڴ��ջ��Ԫ��
    int top;                //ջ��λ�ã������±꣩
public:
    Stack() { top = -1; }                //���캯������ʼ��ջ
    void Push(const T& t) {
        if(!Full())array[++top] = t;
    }  //Ԫ����ջ
    T Pop() {
        if(!Empty())return array[top--];
    }                //ջ��Ԫ�س�ջ
    void Clear() { top = -1; }           //��ջ���
    const T& Top() const {
        return array[top];
    }  //����ջ��Ԫ��
    bool Empty() const {
        return top == -1;
    }     //����ջ�Ƿ�Ϊ��
    bool Full() const {
        return top == SIZE - 1;
    }     //�����Ƿ�ջ��
    int Size() {
        return top + 1;
    }           //���ص�ǰջ��Ԫ�ظ���
};

int main()
{
    Stack<int, 10> intStack;

    int n;
    cin >> n; //���뱣֤ n<=10
    for (int i = 0; i < n; i++)
    {
        int temp;
        cin >> temp;
        intStack.Push(temp);
    }

    for (int i = 0; i < n; i++)
    {
        cout << intStack.Top() << " ";
        intStack.Pop();
    }
    cout << endl;

    if (intStack.Empty())
        cout << "Now, intStack is empty." << endl;

    Stack<string, 5> stringStack;
    stringStack.Push("One");
    stringStack.Push("Two");
    stringStack.Push("Three");
    stringStack.Push("Four");
    stringStack.Push("Five");
    cout << "There are " << stringStack.Size() << " elements in stringStack." << endl;
    stringStack.Clear();
    if (stringStack.Empty())
        cout << "Now, there are no elements in stringStack" << endl;

    return 0;
}

21.MyQueue��ѡ����
����

���һ��MyQueue��ģ�壬��ģ��˵�����£�

template <typename T> class MyQueue;//ǰ������
template <typename T> std::ostream & operator<<(std::ostream &, const MyQueue<T> &); 

template <typename T> 
class QueueItem
{
public:
    QueueItem(const T & t) :item(t), next(0)
    {} 
private:
    T item; //value stored in this element
    QueueItem *next; // pointer to next element in the MyQueue

    friend class MyQueue<T>;//��Ԫ��    
    //ͨ����Ԫ��������<<�����ģ�庯����Ҫд��<<���<Type>
    friend ostream & operator<< <T> (ostream & os, const MyQueue<T> & q);
};

template <typename T> 
class MyQueue
{
public:
    MyQueue() : head(0), tail(0) {} // Empty MyQueue

    MyQueue(const MyQueue &Q) //�������캯��
        :head(0), tail(0) 
    { CopyElements(Q); };

    ~MyQueue() { Destroy(); }

    MyQueue & operator=(const MyQueue &);

    // return element from head of MyQueue
    T & Front() { return head->item; }
    const T & Front() const { return head->item; }
    void Push(const T &); //add element to back of MyQueue
    void Pop(); // remove element from head of MyQueue
    bool Empty() const { return head == 0; }
    void Display() const;
private:
    QueueItem<T> *head;
    QueueItem<T> *tail;
    void Destroy(); //delete all the elements
    void CopyElements(const MyQueue &);

    //������Ԫ����
    friend ostream & operator<< <T> (ostream & os, const MyQueue<T> & q);
};

ʵ�������ģ���еĳ�Ա������Ȼ��ʹ��������ʾ��main()����������һ��ģ�塣

int main()
{
    MyQueue<int> qi;
    qi.Push(1);
    qi.Push(2);
    qi.Push(3);
    qi.Push(4);
    qi.Push(5);
    qi.Pop();
    qi.Display();
    cout<<"\n";
    cout<<qi;
    cout<<endl;

    MyQueue<int> qi2(qi);
    qi2.Display();
    cout<<endl;

    MyQueue<int> qi3;
    qi3 = qi;
    cout<<qi3;

    return 0;
}


����

��


���

����������


�������� 1 

null
������� 1

2 3 4 5 
< 2 3 4 5 >
2 3 4 5 
< 2 3 4 5 >
��Դ

xyy


#include<iostream>

using namespace std;

template <typename T> class MyQueue;//ǰ������
template <typename T> class QueueItem;
template <typename T> std::ostream& operator<<(std::ostream&, const MyQueue<T>&);

template <typename T>
class QueueItem
{
public:
    QueueItem(const T& t) :item(t), next(0) {}
private:
    T item; //value stored in this element
    QueueItem* next; // pointer to next element in the MyQueue

    friend class MyQueue<T>;//��Ԫ��    
    //ͨ����Ԫ��������<<�����ģ�庯����Ҫд��<<���<Type>
    friend ostream& operator<< <T> (ostream& os, const MyQueue<T>& q);
};
template<typename T>
ostream& operator<<(ostream& os, const MyQueue<T>& q) {
    os << "< ";
    QueueItem<T>* current = q.head;
    if (current != 0) {
        while (current) {
            os << current->item << " ";
            current = current->next;
        }
    }
    os << ">";
    return os;
}

template <typename T>
class MyQueue
{
public:
    MyQueue() : head(0), tail(0) {} // Empty MyQueue

    MyQueue(const MyQueue& Q) //�������캯��
        :head(0), tail(0)
    {
        CopyElements(Q);
    };

    ~MyQueue() { Destroy(); }

    MyQueue& operator=(const MyQueue& q) {
        if (this != &q) {
            Destroy();
            CopyElements(q);
        }
        return *this;
    }

    // return element from head of MyQueue
    T& Front() { return head->item; }
    const T& Front() const { return head->item; }
    void Push(const T& t) {
        QueueItem<T>* newItem = new QueueItem<T>(t);
        if (Empty()) {
            head = newItem;
            tail = newItem;
        }
        else{
            tail->next = newItem;
            tail = newItem;
        }
    } //add element to back of MyQueue
    void Pop() {
        if (Empty())return;
        QueueItem<T>* temp = head;
        head = head->next;
        if (head == 0) { tail = 0; }
        delete temp;
    } // remove element from head of MyQueue
    bool Empty() const { return head == 0; }
    void Display() const {
        QueueItem<T>* current = head;
        while (current != 0) {
            cout << current->item << " ";
            current = current->next;
        }
    }
private:
    QueueItem<T>* head;
    QueueItem<T>* tail;
    void Destroy() {
        QueueItem<T>* current = head;
        while (current) {
            QueueItem<T>* temp = current;
            current = current->next;
            delete temp;
        }
        head = 0;
        tail = 0;
    } //delete all the elements
    void CopyElements(const MyQueue& q) {
        if (q.Empty())return;
        QueueItem<T>* current = q.head;
        while (current) {
            Push(current->item);
            current = current->next;
        }
    }

    //������Ԫ����
    friend ostream& operator<< <T> (ostream& os, const MyQueue<T>& q);
};


int main()
{
    MyQueue<int> qi;
    qi.Push(1);
    qi.Push(2);
    qi.Push(3);
    qi.Push(4);
    qi.Push(5);
    qi.Pop();
    qi.Display();
    cout << "\n";
    cout << qi;
    cout << endl;

    MyQueue<int> qi2(qi);
    qi2.Display();
    cout << endl;

    MyQueue<int> qi3;
    qi3 = qi;
    cout << qi3;

    return 0;
}

22.StringSort
����

��д��������std::sort���һ���ַ���(std::string����)������(����)�������


����

����һ�У��ɴ�Сд��ĸ��������ɵ��ַ�����


���

����������ַ�����


�������� 1 

abcde
������� 1

edcba


#include<iostream>
#include<string>
#include<algorithm>

int main() {
    std::string s;
    std::cin >> s;
    sort(s.begin(), s.end(), std::greater<char>());
    std::cout << s << std::endl;
    return 0;
}

23.StringsSort
����

��д��������std::sort��������

�������ɸ�string�����ַ�������ÿ���ַ����е��ַ��������ֵ�����������A��Z, a��z�����ٶԴ���֮����ַ����������ַ������ֵ��򣨽���z��a,Z��A������

����ʹ��vector�����洢������ַ�������ϰʹ��vector��


����

�����һ��Ϊһ��������N��Ȼ����������N�������ո���ַ�����


���

�ο��������


�������� 1 

4
C++
ACM
AHa
MomoDa
������� 1

DMamoo
AHa
ACM
++C


#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

int main() {
    int N;
    std::cin >> N;
    std::vector<std::string> strings;
    for (int i = 0; i < N; ++i) {
        std::string s;
        std::cin >> s;
        strings.push_back(s);
    }
    for (auto& c : strings) { sort(c.begin(), c.end()); }
    sort(strings.begin(), strings.end(), [](const std::string& a, const std::string& b) {return a > b; });
    for (const auto& str : strings) { std::cout << str << std::endl; }
    return 0;
}

24.SimpleList
����

��д���򣬶���һ���ṹ��struct Student{ int no; string name;};��������ṹ����ϰʹ��list��������list�����Ԫ���Լ����list������Ԫ�ء�

struct Student {
    int no;
    string name;
};

��ʹ������main��������

int main()
{
    std::list<Student> li;

    Input(li); //����
    Show(li); //���

    return 0;
}

ע�⣺����ֻ���ύ Input���� �� Show���� ���롣


����

��һ��һ������n����ʾ����n��ѧ����Ϣ

������n�У�ÿ����һ��������һ���ַ������ֱ��ʾѧ����ѧ�ź�������


���

��˳�����list�е�����Ԫ�أ�ÿ���ṹ��Ԫ��ռһ�С��ṹ���Ա֮���Զ��ſո������


�������� 1 

3
1010101 zhangsan
1010102 lisi
1010103 wangwu
������� 1

1010101, zhangsan
1010102, lisi
1010103, wangwu


#include<iostream>
#include<list>
using namespace std;

struct Student {
    int no;
    string name;
};

void Input(list<Student>& li) {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Student s;
        cin >> s.no >> s.name;
        li.push_back(s);
    }
}

void Show(const list<Student>& li) {
    for (const auto& s : li) {
        cout << s.no << ", " << s.name << endl;
    }
}

int main()
{
    std::list<Student> li;

    Input(li); //����
    Show(li); //���

    return 0;
}

25.CardGame
����

������һ���ƣ��ӵ�һ���ƣ���λ�ڶ�����ƣ���ʼ�����������α��Ϊ1~n��

�����ٻ�ʣ������ʱ�������²������ѵ�һ�����ӵ���Ȼ����µĵ�һ�ŷŵ������Ƶ����

����std::queueģ��������̣��������ÿ���ӵ������Լ����ʣ�µ��Ƶı�š�


����

����������n(n<1000000)��


���

��һ�����������ÿ���ӵ������Լ����ʣ�µ��Ƶı�ţ����֮����һ���ո�����������������һ�����з���


�������� 1 

7
������� 1

1 3 5 7 4 2 6
��ʾ

������std::queueʵ�֣���ϰʹ��queue


#include<iostream>
#include<queue>
using namespace std;

int main(){
    int n;
    cin >> n;

    queue<int> q;
    for (int i = 1; i <= n; ++i) {
        q.push(i);
    }

    while (q.size() > 1) {
        cout << q.front() << " ";
        q.pop();

        int front = q.front();
        q.pop();
        q.push(front);
    }
    cout << q.front();
    return 0;
}

26.Marble
����

����N������ʯ��ÿ������ʯ��д��һ���Ǹ����������ȶ���Щ������С��������Ȼ��ش�Q�����⡣ÿ���������Ƿ���һ������ʯд��ĳ������x������ǣ��ͻش��ĸ�����ʯ��д��x������ж������ʯ�ϳ���x����ô�ش��һ�γ��ֵĴ���ʯ��ţ��������Ĵ���ʯ�����ұ��Ϊ1~N��


����

�����������������ݣ�ÿ�����ݷ����е�һ��������������N(N<100)��Q(Q<100)���ڶ�����N���Ǹ�������������Q���Ǹ�������


���

����ÿһ��ѯ��(x)������е�i������ʯ��д��x�������"x found at i"���������"x not found"����ʽ���������


�������� 1 

4 1
2 3 5 1
5
5 2
1 3 3 3 1
2 3
������� 1

5 found at 4
2 not found
3 found at 3
��ʾ

��1�������ж������룬����ʹ�� while (std::cin >> N >> Q) ѭ������������롣

��2������ʹ��algorithmͷ�ļ��е�std::sort��std::lower_bound����������ʹ�ö��ֲ��ң��书���ǲ��Ҵ��ڵ���x�ĵ�һ��λ�ã�����ʹ�÷����Լ��顣


#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main() {
    int N, Q;
    while (cin >> N >> Q) {
        vector<int> Marbles(N);
        for (int i = 0; i < N; ++i) {
            cin >> Marbles[i];
        }
        sort(Marbles.begin(), Marbles.end());

        for (int i = 0; i < Q; ++i) {
            int target;
            cin >> target;
            auto it = lower_bound(Marbles.begin(), Marbles.end(), target);
            if (it != Marbles.end() && *it == target) {
                cout << target << " found at " << it - Marbles.begin() + 1 << endl;
            }
            else { cout << target << " not found" << endl; }
            
        }
    }
    return 0;
}


27.����(ѡ��)
����

ĳ������һ����վ������������ͼ��ʾ����n�ڳ����A����ʻ�복վ������վ˳����Ϊ1~n����������������ǰ���ĳ���ض���˳�����B��������첢ʻ����վ��Ϊ�����鳵�ᣬ����Խ�����תվC������һ������ͣ�������ڳ���ĳ�վ��������ĩ�˷�գ�ʻ��C�ĳ�����밴���෴��˳��ʻ��C������ÿ�����ᣬһ����A����C���Ͳ����ٻص�A�ˣ�һ����C����B���Ͳ��ܻص�C�ˡ����仰˵������һʱ�̣�ֻ������ѡ��A->C��C->B�������жϣ��������ĳ�վ˳�򣬻��ܷ��վ��

ffd15b0ac3afe2fda2a10bc60fabfbf8.blob.png


����

�����������������ݣ�ÿ�����ݵĵ�һ����һ��������n(1<n<1000)���ڶ����ǵ�1��~��n����n��������һ��ȫ���С�


���

����ÿһ��������ݣ�����ܰ�Ҫ����ɳ������飬�������Yes��,���������No����ÿ�����ռһ�С�


�������� 1 

5
1 2 3 4 5
5
5 4 1 2 3
6
6 5 4 3 2 1
������� 1

Yes
No
Yes
��ʾ

����ʹ��stackʵ�֣���ϰʹ��stack


#include<iostream>
#include<stack>
#include<vector>
using namespace std;

bool can_depart(vector<int>& order) {
    stack<int> mid_stack;
    int n = order.size();
    int current = 1;
    for (int i = 0; i < n; ++i) {
        int target = order[i];
        while (mid_stack.empty() || mid_stack.top() != target) {
            if (current > n) { return false; }
            mid_stack.push(current++);
        }
        mid_stack.pop();
    }
    return true;
}

int main() {
    int n;
    while (cin >> n) {
        vector<int> order;
        for (int i = 0; i < n; ++i) {
            int num;
            cin >> num;
            order.push_back(num);
        }
        if (can_depart(order)) { cout << "Yes" << endl; }
        else { cout << "No" << endl; }
    }
    return 0;
}

28.Reading papers
����

����һƪ�����е�һ�����֣�ʹ��C++�ַ�����������з�����������¹��ܣ�

ͳ��������ֵĵ����������Կո�ָ�Ϊ׼��
ͳ��������ֵı�������������ǰ�Ǿ�š����š�˫���ţ�
ע�Ȿ��Ҫ��

main������д�����£�ֻ�ύreadPapers()����
ͷ�ļ������Լ�����
int main() {
    std::string content;
    std::getline(std::cin, content, '\n');
    readPapers(content);
    return 0;
}


����

һ�β����С�����š����š�˫���ŵ�Ӣ�����֡�


���

�ֱ�������������ͱ����������

30,6


�������� 1 

No matter what difficulties we encounter, don't be afraid and face them with a smile. The best way to eliminate fear is to face the fear itself. "Persistence is victory".
������� 1

30,6
��ʾ

����Ӣ����д���򣬱������뵥��֮��û�пո�
˫����Ϊ " "
����stringstream�ɿ��ٷָ��ַ���
��Դ

hlu

#include<iostream>
#include<sstream>
#include<string>

void readPapers(const std::string& content) {
    int num_of_words = 0;
    int num_of_punctuation = 0;

    std::istringstream iss(content);
    std::string word;
    while (iss >> word) {
        num_of_words++;
    }

    for (char character : content) {
        if (character == '.' || character == ',' || character == '"') {
            num_of_punctuation++;
        }
    }
    std::cout << num_of_words << "," << num_of_punctuation << std::endl;
}

int main() {
    std::string content;
    std::getline(std::cin, content, '\n');
    readPapers(content);
    return 0;
}


29.Counting words
����

����һ������ϣ���ͼ��һ�������Ľ��д�Ƶ��������ժȡ����һ�Σ���ʹ��C++�ַ�������ϳ���STL����������¹��ܣ�

ͳ��������ֵĲ��ظ��ĵ��ʸ���������γ��ֵĵ���ֻ��Ϊһ����
�����ֵĵ��ֲ���Ϊ����
ע�Ȿ��Ҫ��

main������д�����£�ֻ�ύtermFrequency()��alphabetSortedFrequency()����
ͷ�ļ������Լ�����
int main() {

    // �ӱ�׼�����ȡ�ı���
    std::string content;
    std::getline(std::cin, content, '\n');

    map<string, unsigned> msu;

    // Ҫ��termFrequencyʵ�ִַʣ�ȥ�����
    // ��ȡ���ʴ����map�У���¼��Ƶ�����ִ�����
    // ��󷵻ز��ظ��ĵ�������    
    unsigned nWords = termFrequency(content, msu);

    // ������ĸA-Z����һ��һ�������Ƶ
    // ��ʾ: mapĬ�ϰ�keyֵ����
    alphabetSortedFrequency(msu);

    return 0;
}


����

һ�β����С�����š����š�˫���ŵ�Ӣ�����֡�


���

����������ĸA-Z����һ��һ�����Сд���ʺ�Ƶ������

apple:10
banana:5
cherry:1


�������� 1 

No matter what difficulties we encounter, don't be afraid and face them with a smile. The best way to eliminate fear is to face the fear itself. "Persistence is victory".
������� 1

a:1
afraid:1
and:1
be:1
best:1
difficulties:1
don't:1
eliminate:1
encounter:1
face:2
fear:2
is:2
itself:1
matter:1
no:1
persistence:1
smile:1
the:2
them:1
to:2
victory:1
way:1
we:1
what:1
with:1
��ʾ

�����ǰ�Ǿ�š����š�˫���� " " ���ֱ��
Ӧ���Ǵ�Сд���죬�ɰ���ͷ�ļ���transform�������д�Сдת��
��ʹ��stringstream���ж��ַ����Ƿ��ʾ����


#include<iostream>
#include<sstream>
#include<string>
#include<map>
#include<algorithm>
using namespace std;

unsigned termFrequency(const string& content, map<string, unsigned>& msu) {
    unsigned unique_words = 0;

    stringstream ss(content);
    string word;
    while (ss >> word)
    {
        string filtered_word;
        for (char& c : word) {
            if (!ispunct(c)) {
                filtered_word += tolower(c);
            }
        }
        if (filtered_word.empty() || all_of(filtered_word.begin(), filtered_word.end(), isdigit)) {
            continue;
        }
        if (msu.find(filtered_word) == msu.end()) {
            msu[filtered_word] = 1;
            unique_words++;
        }
        else { msu[filtered_word]++; }
    }
    return unique_words;
}

void alphabetSortedFrequency(const map<string, unsigned>& msu) {
    auto it = msu.begin();
    while (it != msu.end())
    {
        cout << it->first << ":" << it->second;
        if (next(it) != msu.end()) {
            cout << " ";
        }
        cout << endl;
        ++it;
    }
}
int main() {

    // �ӱ�׼�����ȡ�ı���
    std::string content;
    std::getline(std::cin, content, '\n');

    map<string, unsigned> msu;

    // Ҫ��termFrequencyʵ�ִַʣ�ȥ�����
    // ��ȡ���ʴ����map�У���¼��Ƶ�����ִ�����
    // ��󷵻ز��ظ��ĵ�������    
    unsigned nWords = termFrequency(content, msu);

    // ������ĸA-Z����һ��һ�������Ƶ
    // ��ʾ: mapĬ�ϰ�keyֵ����
    alphabetSortedFrequency(msu);

    return 0;
}

30.Point cloud ��ѡ����
����

���ŷָ�ֵ��Comma-Separated Values��CSV���ļ��Դ��ı���ʽ�洢���Ʊ����ʽ�����ݣ����ֺ��ı�����points.csv�����һ������ά���� [x,y,z] ��ʾ�ĵ�����Ϣ��ÿ�б�ʾһ���㣬ÿ������3���������ֱ��ʾx��y��z���꣨��λΪ�ף���3����������ʾ��ɫRGB��Ϣ�����԰�Ƕ��ŷָ�������Ϊ�ļ�ͷ��Ϣ����ʹ��C++�ļ���ʵ�����¹��ܣ�

���������Ϣ
ͳ����Щ�������λ�ã�xyz�ֱ���ƽ��ֵ��������ͬ�����ʽ [xxxx,yyyy,zzzz] д��points.csv���һ��
�����е㳯x������ƫ��100�ף���x=x+100����y������ƫ��50�ף���ԭ˳�򡢸�ʽд��points_offset.csv
ע�Ȿ��Ҫ��

ʹ����Ŀ�·����ݱ���Ϊpoints.csv���ڱ��ز�����ȷ���ύ
main������д�����£�ֻ�ύprocessPoints()����
ͷ�ļ������Լ�����
����������Ĵ����н�����Ļ���������Ӱ��OJ���⣬�޷�AC��

int main() {
    std::cout << "Point cloud in processing..." << endl;
    processPoints();
    return 0;
}


����

���������ݱ���Ϊpoints.csv��Ϊ��ı��ز������ݣ�

X,Y,Z,R,G,B
244407.100,6010942.604,19.256,140,131,124
244407.097,6010942.547,19.244,142,131,126
244407.080,6010942.541,19.242,144,135,128
244407.124,6010942.599,19.253,144,131,126
244407.120,6010942.553,19.240,140,130,124
244407.125,6010942.565,19.241,144,133,128
244407.090,6010942.570,19.249,142,131,126
244407.072,6010942.575,19.253,145,135,126
244407.119,6010942.576,19.246,140,130,124
244407.079,6010942.575,19.248,161,151,147
244407.096,6010942.581,19.250,142,133,126
244407.089,6010942.604,19.255,140,131,124
244407.066,6010942.598,19.253,144,135,128
244407.112,6010942.599,19.252,137,128,121
244407.089,6010942.598,19.255,138,130,124
244407.067,6010942.569,19.247,149,142,133
244407.103,6010942.524,19.238,147,137,130
244407.057,6010942.512,19.240,161,153,144
244407.127,6010942.525,19.235,144,135,128
244407.074,6010942.524,19.241,154,142,135


���

Point cloud in processing...


�������� 1 

��
������� 1

Point cloud in processing...
��ʾ

�ļ������ڱ��ش���ʱ��ע��·������д��ʽ���ȿ���ʹ�����·�������ʹ�þ���·����·����ʹ��˫б�ܱ����ַ���ת�塣
������stringstream�ཫ�ַ���תΪ��������
�ļ����������setprecision��������С�����λ������ofs << fixed << setprecision(3);
���ļ�ĩβ��������ʱ��ע��ĩβ�Ƿ����л��з������޿�������ԭʼ�ļ��ڼ���
���������������ͬѧ��ϰʹ�ã����������ý�
��Դ

hlu

#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<iomanip>
#include<tuple>
using namespace std;

void processPoints() {
    string input_filename = "points.csv";
    string output_filename = "points_offset.csv";
    ifstream ifs(input_filename);
    if (!ifs.is_open()) {
        cerr << "�޷��������ļ�: " << input_filename << endl;
        return;
    }
    string header;
    getline(ifs, header);
    vector<tuple<float, float, float, int, int, int>> points;

    string line;
    while (getline(ifs, line)) {
        istringstream iss(line);
        float x, y, z;
        int r, g, b;
        char comma;

        // ����ÿ������
        if (iss >> x >> comma >> y >> comma >> z >> comma >> r >> comma >> g >> comma >> b) {
            points.emplace_back(x, y, z, r, g, b);
        }
    }
    ifs.close();

    // ��������
    float sumX = 0, sumY = 0, sumZ = 0;
    for (const auto& point : points) {
        sumX += get<0>(point);
        sumY += get<1>(point);
        sumZ += get<2>(point);
    }
    float centroidX = sumX / points.size();
    float centroidY = sumY / points.size();
    float centroidZ = sumZ / points.size();

    // ��������Ϣд��ԭ�ļ�ĩβ
    ofstream ofs(input_filename, ios::app);
    if (!ofs.is_open()) {
        cerr << "�޷��������ļ���׷��: " << input_filename << endl;
        return;
    }
    ofs << fixed << setprecision(3) << centroidX << "," << centroidY << "," << centroidZ << endl;
    ofs.close();

    // �����е�ƫ�Ʋ�д�����ļ�
    ofstream ofsOffset(output_filename);
    if (!ofsOffset.is_open()) {
        cerr << "�޷�������ļ�: " << output_filename << endl;
        return;
    }
    ofsOffset << header << endl; // д���ļ�ͷ
    for (const auto& point : points) {
        float x = get<0>(point) + 100.0f; // x ������ƫ�� 100 ��
        float y = get<1>(point) - 50.0f;  // y ������ƫ�� 50 ��
        float z = get<2>(point);
        int r = get<3>(point);
        int g = get<4>(point);
        int b = get<5>(point);
        ofsOffset << fixed << setprecision(3) << x << "," << y << "," << z << "," << r << "," << g << "," << b << endl;
    }
    ofsOffset.close();
}


int main() {
    std::cout << "Point cloud in processing..." << endl;
    processPoints();
    return 0;
}

*/