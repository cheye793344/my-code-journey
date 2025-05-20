/*
1.计算圆面积
描述

编写一个圆类Circle，实现半径的输入、面积的计算和输出。Circle类的定义如下所示：

class Circle
{
private:
    double r;
public:
    void input();
    double area() const;
    void output() const;
};

要求实现Circle类的3个成员函数，完成输入半径、计算面积和输出面积；并用以下main函数测试。

int main()
{
    Circle myCircle;
    myCircle.input();
    myCircle.output();
    return 0;
}


输入

输入一行，输入圆的半径(double类型)。


输出

输出一行，输出圆的面积(保留小数点后两位)。


输入样例 1

3
输出样例 1

28.27
提示

1、在输出面积前使用如下语句：cout<<setiosflags(ios::fixed)<<setprecision(2);来设置输出格式，需要包含iomanip头文件

2、使用acos(-1.0)来得到圆周率的精确值，可将其设置为常量，比如：const double PI = acos（-1.0），需要包含cmath头文件

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



2.过道和栅栏的造价
描述

一矩形体育场如下图所示，现在需在其周围建一矩形过道，并在四周围安上栅栏。栅栏价格为50元/米，过道造价为240元/平方米。过道宽为1.5米，体育场的长和宽由键盘输入。

图片.png

体育场和矩形过道都是Rectangle类对象，请编写Rectangle类，用以下main函数计算并输出过道和栅栏的造价。

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


输入

体育场的长和宽


输出

输出2行

第一行是栅栏的造价

第二行是过道的造价


输入样例 1

2.4 1.2
输出样例 1

960
4752
输入样例 2

2 1
输出样例 2

900
4320
提示

体育场对象用 rect1(x, y)表示，过道外的矩形用对象 rect2(x + 3, y + 3)表示


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

3.图书类
描述

以下是图书类Book的声明。

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

请实现Book类的成员函数并用以下main函数测试Book类。

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

输入

在main函数中，输入三行数据，第一行是书的名称(长度不超过100，允许有空格)，第二行是作者的名字(长度不超过100，允许有空格),第三行是销量(整数类型)。类中有三个对应的成员变量，分别为name,author和sale。利用题目中所给的构造函数来初始化对象。需要注意的是，题目中有三个构造函数，分别是无参构造函数、有参构造函数和拷贝构造函数。

本题要求：当输入的name,author和sale都为-1的时候，使用无参构造函数来初始化对象，此时要求将name设置为"No name",author设置为"No author",sale设置为0；当输入都为0的时候，使用拷贝构造函数来处理，这种情况在main函数中的实现可以是这样的：Book bk1;Book bk2(bk1);bk2.print();其他情况一律使用有参构造函数来构造对象。


输出

使用类中的void print()函数来输出对象，要求输出的name变量和author变量的后面用'\t'间隔，sale变量后用换行符，且 Name:，Author:，Sale: 后面都有一个空格，具体参见输出样例。


输入样例 1

C++ Primer
Stanley B. Lippman, et al.
1000
输出样例 1

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


4.名单类
描述

已知日期类的定义如下：

class Date    //日期类
{
private:
    int Date_year;    //年
    int Date_month;    //月
    int Date_day;    //日
public:
    Date(int year, int month, int day);
    void show() const;    //以“年-月-日”格式输出年月日
};

名单类中含有日期类的对象，如下所示：

class Croster    //名单类
{
private:
    string name;
    Date birthday;
public:
    Croster();
    Croster(string name,int year,int month,int day);
    Croster(string name, Date date);
    void show() const;//显示姓名和出生日期
};

要求实现以上两个类，并用以下main函数进行测试。

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
输入为多组数据：

（1）输入为0的时候，直接使用Croster类的无参构造函数（即第1个构造函数）实例化对象，并输出：Name: NULL, Birthday: 0-0-0；

（2）当输入为1时，继续输入姓名和年月日，使用Croster类的含有4个参数的构造函数（即第2个构造函数）实例化对象，并进行输出，详见输出样例2；

（3）当输入为2时，继续输入姓名和年月日，使用Croster类的含有2个参数的构造函数（即第3个构造函数）实例化对象，并进行输出，详见输出样例3；

（4）当输入为-1时，退出程序


输入

如果输入为0则不继续输入，如果输入为-1则退出程序。如果输入为1或2则继续输入姓名和年月日。


输出

详见输出样例。


输入样例 1

0
输出样例 1

Name: NULL, Birthday: 0-0-0

输入样例 2

1
Zhangsan
2025
3
1
输出样例 2

Name: Zhangsan, Birthday: 2025-3-1
输入样例 3

2
Lisi
2025
3
2
输出样例 3

Name: Lisi, Birthday: 2025-3-2
提示

冒号和逗号后各有一个空格



#include<iostream>
#include<cstring>
using namespace std;

class Date    //日期类
{
private:
    int Date_year = 0;    //年
    int Date_month = 0;    //月
    int Date_day = 0;    //日
public:
    Date(int year, int month, int day) :Date_year(year),Date_month(month),Date_day(day){}
    void show() const { cout << Date_year << "-" << Date_month << "-" << Date_day; }
   //以“年-月-日”格式输出年月日
};

class Croster    //名单类
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
    }//显示姓名和出生日期
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

5.友元类
描述

已知选课类Subject和学生类Student定义如下，学生类是选课类的友元类

class Subject    //选课类
{
private:
    double score[3];                //3门课成绩
    const int SMath, SEng, SCpp;    //3门课的学分，分别为4、2、2
public:
    Subject(double score_math = 0, double score_eng = 0, double score_cpp = 0);
    void Input();            //输入3门课的成绩
    friend class Student;    //友元类
};

class Student
{
private:
    string ID;        //学号
    string name;       //姓名
    double GPA;        //平均学分积=（成绩1x学分1+成绩2x学分2+成绩3x学分3）/（学分1+学分2+学分3）
public:
    Student();
    void CalculateGPA(const Subject &sub);    //计算平均学分积
    void Input();                            //输入学号和姓名
    void Show(const Subject &sub)const;        //输出所有信息
};

请实现以上两个类，并用如下main函数进行测试：

int main()
{
    int n;        //学生人数
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


输入

第一行输入学生人数n，下面依次输入n个学生的学号、姓名、3门课的成绩


输出

见输出样例


输入样例 1

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
输出样例 1

ID: 001, Name: Jack
Math Eng Cpp
100 89 90
GPA: 94.75
ID: 002, Name: Mary
Math Eng Cpp
78 69 90
GPA: 78.75
输入样例 2

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
输出样例 2

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
提示

输出时，冒号和逗号后各有一个空格，每门课成绩后面均有一个空格，课程名称之间有一个空格，“Cpp”后无空格


#include<iostream>
using namespace std;


class Subject    //选课类
{
private:
    double score[3];                //3门课成绩
    const int SMath = 4;
    const int SEng = 2;
    const int SCpp = 2;
   //3门课的学分，分别为4、2、2
public:
    Subject(double score_math = 0, double score_eng = 0, double score_cpp = 0) :score{score_eng,score_eng,score_cpp}{}
    void Input() { for (int i = 0; i < 3; ++i) cin >> score[i]; }           //输入3门课的成绩
    friend class Student;    //友元类
};

class Student
{
private:
    string ID;        //学号
    string name;       //姓名
    double GPA = 0;        //平均学分积=（成绩1x学分1+成绩2x学分2+成绩3x学分3）/（学分1+学分2+学分3）
public:
    Student() {}
    void CalculateGPA(const Subject& sub) { GPA = (sub.score[0] * double(sub.SMath) + sub.score[1] * double(sub.SEng) +sub.score[2] * double(sub.SCpp)) / (double(sub.SMath)+ double(sub.SEng) + double(sub.SCpp)); }  //计算平均学分积
    void Input() { cin >> ID >> name; }                            //输入学号和姓名
    void Show(const Subject & sub)const {
            cout << "ID: " << ID << ", " << "Name: " << name << endl;
            cout << "Math Eng Cpp" << endl;
            cout << sub.score[0] << " " << sub.score[1] << " " << sub.score[2] << " " << endl;
            cout << "GPA: " << GPA << endl;
        }      //输出所有信息
};


int main()
{
    int n;        //学生人数
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
6.旅馆人数统计
描述

编写程序，统计某旅馆住宿客人的总数。要求输入客人的姓名，输出客人的编号（按先后顺序自动生成）、姓名以及总人数。

使用如下main函数对程序进行测试

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

输入

输入一行，输入客人的姓名(不超过100个字符的由英文大小写字母组成的字符串)。


输出

输出一行，输出客人的编号，姓名及总人数，空格分隔。


输入样例 1

Peter
输出样例 1

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
描述

给定以下print函数和main函数，定义并实现TestConstClass类，通过题目的测试。

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

输入

输入若干个字符串


输出

对于输入的每个字符串，原样输出这个字符串，每个输出占一行


输入样例 1

test
输出样例 1

test
来源

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
描述

编写TableTennisPlayer类和RatedPlayer类（RatedPlayer类继承TableTennisPlayer类），其中TableTennisPlayer类的定义如下所示：

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
实现后，通过以下main函数的测试：

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

输入

输入多行，每一行以'T'或'R'开头，'T'表示本行接下来输入一个TableTennisPlayer对象的信息，包括 firstname，lastname 和 hasTable（是否有乒乓球台）；'R'表示本行接下来输入一个RatedPlayer对象的信息，包括 firstname，lastname，hasTable 和 rating（选手的得分）。


输出

一行输入对应一行输出，输出详见main函数


输入样例 1

T Bill Gates 1
输出样例 1

Bill Gates has a table.
输入样例 2

R Jike Zhang 0 19000
输出样例 2

Jike Zhang doesen't have a table. The rating is 19000.
提示

bool类型的输入：0表示false，1表示true

来源

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

8.Person和Student
描述

实现一个Person类，再实现一个Student类，要求Student类继承Person类，通过以下测试：

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

输入

输入包含两行，第一行为一个姓名（不包含空格）；第二行为一个学号和一个姓名（学号、姓名都不包含空格），学号和姓名之间用空格间隔


输出

输出为两行，第一行为一个姓名；第二行为学号和姓名，学号和姓名之间用空格间隔


输入样例 1

Mary
001 Mary
输出样例 1

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

9.图书商品
描述

编写两个类，第一个类是：

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
第二个类是：

class Bulk_Item : public Item_base {
public:
    Bulk_Item(const string& book_ISBN = "", double sales_price = 0.0, int min_qty = 0, double discount = 0.0);
    double net_price(int) const;
private:
    int min_qty;
    double discount;
};
实现以上两个类，通过以下main函数的测试

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

输入

图书的数量。


输出

输出购买的图书的ISBN, 它的数量以及总的价格。（详见main函数）


输入样例 1

2
6
11
输出样例 1

0 - 001 - 0001 - 1     2     20
0 - 001 - 0001 - 1     6     54
0 - 001 - 0001 - 1     11    88

10.Vehicle类
描述

设计一个抽象类Vehicle，由它派生出类Car和类Truck，类Car包含名称、颜色和载客数三个数据成员，类Truck包含名称、颜色和载重量三个数据成员。

使用以下main函数完成类的测试:

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


输入

多组输入，每组输入的开头是'C'或者'T'，'C'表示Car，'T'表示Truck，接下来输入Car或Truck的信息，Car的信息包括名称，颜色和载客数，Truck的信息包括名称，颜色和载重量。测试时，用抽象类Vehicle的指针指向派生类对象，实现不同类中display()函数的多态。


输出

根据不同车种类，输出不同信息，具体见样例输出。


输入样例 1

C Benz black 3
T Dongfeng white 8.5
输出样例 1

Car name:Benz Car color:black Car passager:3
Truck name:Dongfeng Truck color:white Truck capacity:8.5
提示

Vehicle中可包含名称和颜色数据成员，并且有纯虚函数以提供接口完成信息的显示；在派生类Car和Truck中根据需要实现纯虚函数以及添加成员。纯虚函数用const限定的语法为：virtual void display() const = 0;

仔细读输出样例的格式，输出为两行，每行的不同项目之间用一个空格隔开。


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
11.三维形状（3DShape）
描述

编写程序，计算长方体、圆柱体和球的表面积和体积。要求先定义一个抽象类C3DShape如下：

class C3DShape {
public:
    C3DShape() {}
    virtual double area() const = 0;
    virtual void input() = 0;
    virtual double volume() const = 0;
    virtual ~C3DShape() {}
};

使用C3DShape类派生出长方体类、圆柱体类、球类，在这三个类里实现从C3DShape类继承来的纯虚函数。使用如下代码通过测试。

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


输入

输入包含多行，每行首先是一个字符'c'，'y'，'q'，分别表示输入长方体、圆柱体或球的信息，接下来是对应的输入。


输出

每行输入对应一行输出，表示该形状的表面积和体积，以空格分隔。


输入样例 1

c 3 4 5
y 3 5
q 5
输出样例 1

94 60
150.796 141.372
314.159 523.599
提示

pi的精度要足够，建议使用 const double pi = acos(-1);

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

12.Singer类
描述

实现一个Singer类，通过以下测试：

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


输入

输入包含四行，前两行为歌手s1的信息，后两行为歌手s2的信息；每位歌手的信息包括姓名（姓名可能包含空格）、性别（char类型）、年龄（int类型） 和 分数（float或double类型）。详见输入样例。


输出

输出为三行，前两行分别是歌手s1和s2的信息，第三行根据s1和s2比较结果输出（s1和s2的比较结果和他们的分数的比较结果一致），具体参见主函数


输入样例 1

Wang Xiaohua
F 28 99.5
Zhang Dali
M 26 98
输出样例 1

Wang Xiaohua F 28 99.5
Zhang Dali M 26 98
Wang Xiaohua's score is higher than Zhang Dali's.
提示

C++的输入流类有ignore()函数，可以清除输入流中的换行符，自己查如何调用

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

13.Sales_data类
描述

实现以下Sales_data类（包括它的友元函数）：

class Sales_data {
//输入书号、销量和收入
friend istream & operator>>(istream&, Sales_data &);
//输出书号、销量、收入和均价
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
    double avg_price() const;  //计算均价，结果等于收入除以销量
    string bookNo;        //书号
    unsigned units_sold; //销量
    double revenue;      //收入
};
通过以下main函数的测试

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

输入

输入多组数据，每组数据两行，每行表示1个Sales_data对象，依次是书号、销量和收入


输出

对于每组数据，输出5行，具体参见main函数和输出样例


输入样例 1

001 10 100.0
001 10 100.0
输出样例 1

001 10 100 10
001 10 100 10
001 equals 001
001 20 200 10
001 20 200 10
输入样例 2

002 5 250
003 8 400
输出样例 2

002 5 250 50
003 8 400 50
002 doesn't equal 003
002 13 650 50
002 13 650 50
提示

后台已有main函数，提交时去掉main函数

来源

xyy


#include<iostream>
#include<string>
using namespace std;

class Sales_data {
    //输入书号、销量和收入
    friend istream& operator>>(istream&, Sales_data&);//
    //输出书号、销量、收入和均价
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
    double avg_price() const;  //计算均价，结果等于收入除以销量 //
    string bookNo;        //书号
    unsigned units_sold; //销量
    double revenue;      //收入
};

istream& operator>>(istream& is, Sales_data& item) {
    is >> item.bookNo >> item.units_sold >> item.revenue;
    return is;
}
//输出书号、销量、收入和均价
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
描述

实现以下复数类Complex，通过运算符重截，实现复数的输入输出以及相关运算。

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
通过以下主函数测试：

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

输入

输入有两行，每行为两个浮点数，分别表示一个复数的实部和虚部。


输出

输出一共有11行，分别表示复数之间的各项操作，具体参见主函数和输出样例


输入样例 1

-4 6
2 5
输出样例 1

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
提示

后台已有main函数，提交时去掉main函数

复数加法公式：(a + bi) + (c + di) = (a + c) + (b + d)i

复数减法公式：(a + bi) - (c + di) = (a - c) + (b - d)i

复数乘法公式：(a + bi) * (c + di) = (ac - bd) + (ad + bc)i

复数除法公式：(a + bi) / (c + di) = [(ac + bd) / (cc + dd)] + [(bc - ad) / (cc + dd)]i


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
15.String类
描述

实现以下String类：

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
使用以下main函数进行测试：

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

输入

s3的值


输出

详见主函数和输出样例


输入样例 1

String3
输出样例 1

hello
String1
copy of String1
String3
1
0
End of my string.
提示

后台已有main函数，提交时去掉main函数

来源

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
描述

自增(++)和自减(--)操作符经常由诸如迭代器这样的类实现，这样的类提供类似于指针的行为访问序列中的元素。例如，定义以下类CheckedPtr，该类指向一个int数组并为该数组中的元素提供访问检查。

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
实现CheckedPtr类并通过以下main函数测试。

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

输入

输入为两行，第一行表示数组的长度n，第二行表示这n个数


输出

输出为两行，第一行依次输出数组的第0个到最后一个元素，第二行反向输出数组的所有元素（参考输出样例）


输入样例 1 

5
1 2 3 4 5
输出样例 1

1 2 3 4 5 
5 4 3 2 1
提示

后台已有main函数，提交时去掉main函数

来源

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
描述

用函数模板Swap实现对不同类型的数据进行交换。

并使用如下主函数测试。

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

注意，本题只需要提交Swap函数代码，头文件和main函数系统已经提供。


输入

输入共三行。第一行两整数，第二行两浮点数，第三行两字符


输出

输出共三行。每一行为对应输入处理后的结果，输出的两个数用逗号隔开


输入样例 1 

2 3
1.2 2.3
a b
输出样例 1

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
描述

用函数模板实现数组的输入、排序和输出。用如下主函数测试：

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

注意：本题只提交Input，Sort， Output函数模板代码。其余部分系统已包含。


输入

输入包含多组测试数据。每组数据为两行，第一行整数type(0、1、2)。第二行为相应数组的5个元素。


输出

对于每一组测试数据，将其排序后在一行内输出，相邻元素用逗号加空格分离，最后一个元素后面换行。


输入样例 1 

0 
3 6 1 4 5
1 
A B C B A
输出样例 1

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
描述

设计一个模板函数，实现在一个给定的数组中查找给定数据是否存在，如果存在则输出该数据在数组中最小的下标，如果不存在，输出-1

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


输入

输入共三组数据，每组数据占三行。

第一组第一行整数n1，第二行是n1个整数，第三行待查找整数n

第二组第一行整数n2，第二行是n2个浮点数，第三行待查找浮点数d

第三组第一行整数n3，第二行是n3个字符，第三行待查找字符c


输出

对于每一组输入，如果查找数据存在，则输出其最小下标(下标从0开始计)，否则输出-1。


输入样例 1

7
1 1 2 5 8 10 13
8
5
-1.0 1.1 1.2 1000.10101 8.9
3.5
4
B J F U
j
输出样例 1

4
-1
-1
提示

使用模板函数

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
描述

构造一个类模板（Vector），数据成员如下：

template<typename T>
class Vector
{
private:
    T x, y, z;
//...
}
完成Vector，并用以下主函数测试

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


输入

见样例


输出

见样例


输入样例 1 

3 4 5
2.2
9.6 12.8 16
输出样例 1

9.6 12.8 16
1
提示

判两个浮点数相等不要使用==，可以用 fabs(a - b) < epsilon，其中epsilon的设置参考题目要求的精度，比如本题 1e-6 就可以

来源

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
描述

实现一个Stack类模板并测试这一模板

template<class T, int SIZE = 20>
class Stack
{
private: 
    T array[SIZE];        //数组，用于存放栈的元素
    int top;                //栈顶位置（数组下标）
public:
    Stack();                //构造函数，初始化栈
    void Push(const T & );  //元素入栈
    T Pop();                //栈顶元素出栈
    void Clear();           //将栈清空
    const T & Top() const;  //访问栈顶元素
    bool Empty() const;     //测试栈是否为空
    bool Full() const;     //测试是否栈满
    int Size();            //返回当前栈中元素个数
};

测试函数：

int main()
{
    Stack<int, 10> intStack;

    int n;
    cin >> n; //输入保证 n<=10
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


输入

参考样例


输出

参考样例


输入样例 1 

3
1
2
3
输出样例 1

3 2 1 
Now, intStack is empty.
There are 5 elements in stringStack.
Now, there are no elements in stringStack
提示

（1）栈的操作在栈顶进行，在这里栈用数组存储，top表示数组下标，array数组存放栈的元素。

（2）构造函数对栈进行初始化，因为没有形参，可以在这里将top赋值成-1，也就是栈为空。（当然，也可将top赋值成0，但是判断栈是否为空和入栈等相应函数均有所改变）

（3）push函数是将元素入栈。在函数中首先判断栈是否已满，不满的话将元素入栈，因此需要修改array数组和top下标。

(4）pop函数将栈顶元素出栈。在函数中首先判断栈是否为空，不空即将栈顶元素出栈（即返回栈顶的元素值，修改下标的值）；否则退出（可用exit（1）语句）。

（5）clear函数清空栈，即将top重新赋值为-1。

（6）Top函数访问栈顶元素，如果栈不空，将栈顶元素返回；否则退出（可用exit（1）语句）。

（7）empty函数判断栈是否为空，如果top==-1则空，否则不空。

（8）full函数测试是否栈满，如果top==SIZE-1则满，否则不满。

（9）size函数返回当前栈中元素个数，考虑类中哪个成员可以表示栈中元素个数？返回它的值即可。


#include<iostream>
using namespace std;

template<class T, int SIZE = 20>
class Stack
{
private:
    T array[SIZE];        //数组，用于存放栈的元素
    int top;                //栈顶位置（数组下标）
public:
    Stack() { top = -1; }                //构造函数，初始化栈
    void Push(const T& t) {
        if(!Full())array[++top] = t;
    }  //元素入栈
    T Pop() {
        if(!Empty())return array[top--];
    }                //栈顶元素出栈
    void Clear() { top = -1; }           //将栈清空
    const T& Top() const {
        return array[top];
    }  //访问栈顶元素
    bool Empty() const {
        return top == -1;
    }     //测试栈是否为空
    bool Full() const {
        return top == SIZE - 1;
    }     //测试是否栈满
    int Size() {
        return top + 1;
    }           //返回当前栈中元素个数
};

int main()
{
    Stack<int, 10> intStack;

    int n;
    cin >> n; //输入保证 n<=10
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

21.MyQueue（选做）
描述

设计一个MyQueue类模板，类模板说明如下：

template <typename T> class MyQueue;//前置声明
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

    friend class MyQueue<T>;//友元类    
    //通过友元函数重载<<运算符模板函数，要写上<<后的<Type>
    friend ostream & operator<< <T> (ostream & os, const MyQueue<T> & q);
};

template <typename T> 
class MyQueue
{
public:
    MyQueue() : head(0), tail(0) {} // Empty MyQueue

    MyQueue(const MyQueue &Q) //拷贝构造函数
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

    //设置友元函数
    friend ostream & operator<< <T> (ostream & os, const MyQueue<T> & q);
};

实现这个类模板中的成员函数，然后使用如下所示的main()函数测试这一类模板。

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


输入

无


输出

见测试样例


输入样例 1 

null
输出样例 1

2 3 4 5 
< 2 3 4 5 >
2 3 4 5 
< 2 3 4 5 >
来源

xyy


#include<iostream>

using namespace std;

template <typename T> class MyQueue;//前置声明
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

    friend class MyQueue<T>;//友元类    
    //通过友元函数重载<<运算符模板函数，要写上<<后的<Type>
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

    MyQueue(const MyQueue& Q) //拷贝构造函数
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

    //设置友元函数
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
描述

编写程序，利用std::sort完成一个字符串(std::string类型)的排序(降序)并输出。


输入

输入一行：由大小写字母和数字组成的字符串。


输出

输出排序后的字符串。


输入样例 1 

abcde
输出样例 1

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
描述

编写程序，利用std::sort进行排序。

输入若干个string类型字符串，对每个字符串中的字符，根据字典序排序（升序，A到Z, a到z），再对处理之后的字符串，根据字符的逆字典序（降序，z到a,Z到A）排序。

建议使用vector容器存储输入的字符串，练习使用vector。


输入

输入第一行为一个正整数N，然后依次输入N个不带空格的字符串。


输出

参考输出样例


输入样例 1 

4
C++
ACM
AHa
MomoDa
输出样例 1

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
描述

编写程序，定义一个结构体struct Student{ int no; string name;};并用这个结构体练习使用list。包含往list里添加元素以及输出list的所有元素。

struct Student {
    int no;
    string name;
};

并使用以下main函数测试

int main()
{
    std::list<Student> li;

    Input(li); //输入
    Show(li); //输出

    return 0;
}

注意：本题只需提交 Input函数 和 Show函数 代码。


输入

第一行一个整数n，表示共有n个学生信息

接下来n行，每行是一个整数和一个字符串，分别表示学生的学号和姓名。


输出

按顺序输出list中的所有元素，每个结构体元素占一行。结构体成员之间以逗号空格隔开。


输入样例 1 

3
1010101 zhangsan
1010102 lisi
1010103 wangwu
输出样例 1

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

    Input(li); //输入
    Show(li); //输出

    return 0;
}

25.CardGame
描述

桌上有一叠牌，从第一张牌（即位于顶面的牌）开始从上往下依次编号为1~n。

当至少还剩两张牌时进行以下操作：把第一张牌扔掉，然后把新的第一张放到整叠牌的最后。

请用std::queue模拟这个过程，依次输出每次扔掉的牌以及最后剩下的牌的编号。


输入

输入正整数n(n<1000000)。


输出

在一行内依次输出每次扔掉的牌以及最后剩下的牌的编号，编号之间用一个空格隔开。所有输出最后加一个换行符。


输入样例 1 

7
输出样例 1

1 3 5 7 4 2 6
提示

建议用std::queue实现，练习使用queue


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
描述

现有N个大理石，每个大理石上写了一个非负整数。首先对这些整数从小到大排序，然后回答Q个问题。每个问题问是否有一个大理石写着某个整数x，如果是，就回答哪个大理石上写着x（如果有多个大理石上出现x，那么回答第一次出现的大理石编号）。排序后的大理石从左到右编号为1~N。


输入

输入包含多组测试数据，每组数据分三行第一行是两个正整数N(N<100)和Q(Q<100)，第二行是N个非负整数第三行是Q个非负整数。


输出

对于每一个询问(x)，如果有第i个大理石上写着x，则输出"x found at i"，否则输出"x not found"。格式详见样例。


输入样例 1 

4 1
2 3 5 1
5
5 2
1 3 3 3 1
2 3
输出样例 1

5 found at 4
2 not found
3 found at 3
提示

（1）本题有多组输入，可以使用 while (std::cin >> N >> Q) 循环处理多组输入。

（2）建议使用algorithm头文件中的std::sort和std::lower_bound函数，后者使用二分查找，其功能是查找大于等于x的第一个位置，具体使用方法自己查。


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


27.铁轨(选做)
描述

某城市有一个火车站，铁轨铺设如图所示。有n节车厢从A方向驶入车站，按进站顺序编号为1~n。你的任务是让它们按照某种特定的顺序进入B方向的铁轨并驶出车站。为了重组车厢，你可以借助中转站C。这是一个可以停放任意多节车厢的车站，但由于末端封闭，驶入C的车厢必须按照相反的顺序驶出C。对于每个车厢，一旦从A移入C，就不能再回到A了；一旦从C移入B，就不能回到C了。换句话说，在任一时刻，只有两种选择：A->C和C->B。请编程判断：按给定的出站顺序，火车能否出站。

ffd15b0ac3afe2fda2a10bc60fabfbf8.blob.png


输入

输入包含多组测试数据，每组数据的第一行是一个正整数n(1<n<1000)，第二行是第1个~第n个这n个整数的一个全排列。


输出

对于每一组测试数据，如果能按要求完成车厢重组，请输出“Yes”,否则输出“No”，每组输出占一行。


输入样例 1 

5
1 2 3 4 5
5
5 4 1 2 3
6
6 5 4 3 2 1
输出样例 1

Yes
No
Yes
提示

建议使用stack实现，练习使用stack


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
描述

读入一篇论文中的一段文字，使用C++字符串流对其进行分析，完成以下功能：

统计这段文字的单词总数（以空格分隔为准）
统计这段文字的标点总数（仅考虑半角句号、逗号、双引号）
注意本题要求：

main函数已写好如下，只提交readPapers()函数
头文件需由自己包含
int main() {
    std::string content;
    std::getline(std::cin, content, '\n');
    readPapers(content);
    return 0;
}


输入

一段不换行、含句号、逗号、双引号的英文文字。


输出

分别输出单词总数和标点总数，如

30,6


输入样例 1 

No matter what difficulties we encounter, don't be afraid and face them with a smile. The best way to eliminate fear is to face the fear itself. "Persistence is victory".
输出样例 1

30,6
提示

根据英文书写规则，标点符号与单词之间没有空格。
双引号为 " "
利用stringstream可快速分割字符串
来源

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
描述

在上一题基础上，试图进一步对论文进行词频分析。现摘取其中一段，请使用C++字符串流结合常用STL容器完成以下功能：

统计这段文字的不重复的单词个数（即多次出现的单词只计为一个）
纯数字的单字不作为单词
注意本题要求：

main函数已写好如下，只提交termFrequency()和alphabetSortedFrequency()函数
头文件需由自己包含
int main() {

    // 从标准输入获取文本串
    std::string content;
    std::getline(std::cin, content, '\n');

    map<string, unsigned> msu;

    // 要求termFrequency实现分词，去掉标点
    // 获取单词存放在map中，记录词频（出现次数）
    // 最后返回不重复的单词数量    
    unsigned nWords = termFrequency(content, msu);

    // 按首字母A-Z排序一行一词输出词频
    // 提示: map默认按key值排序
    alphabetSortedFrequency(msu);

    return 0;
}


输入

一段不换行、含句号、逗号、双引号的英文文字。


输出

按单词首字母A-Z排序，一行一词输出小写单词和频数，如

apple:10
banana:5
cherry:1


输入样例 1 

No matter what difficulties we encounter, don't be afraid and face them with a smile. The best way to eliminate fear is to face the fear itself. "Persistence is victory".
输出样例 1

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
提示

仅考虑半角句号、逗号、双引号 " " 三种标点
应考虑大小写差异，可包含头文件用transform函数进行大小写转换
可使用stringstream类判断字符串是否表示数字


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

    // 从标准输入获取文本串
    std::string content;
    std::getline(std::cin, content, '\n');

    map<string, unsigned> msu;

    // 要求termFrequency实现分词，去掉标点
    // 获取单词存放在map中，记录词频（出现次数）
    // 最后返回不重复的单词数量    
    unsigned nWords = termFrequency(content, msu);

    // 按首字母A-Z排序一行一词输出词频
    // 提示: map默认按key值排序
    alphabetSortedFrequency(msu);

    return 0;
}

30.Point cloud （选做）
描述

逗号分隔值（Comma-Separated Values，CSV）文件以纯文本形式存储类似表格形式的数据（数字和文本）。points.csv存放了一组由三维坐标 [x,y,z] 表示的点云信息，每行表示一个点，每个点由3个浮点数分别表示x、y和z坐标（单位为米），3个整型数表示颜色RGB信息，均以半角逗号分隔。首行为文件头信息。请使用C++文件流实现以下功能：

读入点云信息
统计这些点的重心位置（xyz分别求平均值），按相同坐标格式 [xxxx,yyyy,zzzz] 写入points.csv最后一行
将所有点朝x正方向偏移100米（即x=x+100），y负方向偏移50米，按原顺序、格式写入points_offset.csv
注意本题要求：

使用题目下方数据保存为points.csv，在本地测试正确后提交
main函数已写好如下，只提交processPoints()函数
头文件需由自己包含
绝不可在你的代码中进行屏幕输出！否则影响OJ判题，无法AC！

int main() {
    std::cout << "Point cloud in processing..." << endl;
    processPoints();
    return 0;
}


输入

将以下内容保存为points.csv作为你的本地测试数据：

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


输出

Point cloud in processing...


输入样例 1 

无
输出样例 1

Point cloud in processing...
提示

文件保存在本地磁盘时，注意路径的书写方式，既可以使用相对路径，亦可使用绝对路径。路径中使用双斜杠避免字符被转义。
可运用stringstream类将字符串转为数字类型
文件流输出可用setprecision函数控制小数点后位数，如ofs << fixed << setprecision(3);
向文件末尾附加数据时，注意末尾是否已有换行符，若无可事先在原始文件内加入
此题仅供有能力的同学练习使用，不会做不用交
来源

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
        cerr << "无法打开输入文件: " << input_filename << endl;
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

        // 解析每行数据
        if (iss >> x >> comma >> y >> comma >> z >> comma >> r >> comma >> g >> comma >> b) {
            points.emplace_back(x, y, z, r, g, b);
        }
    }
    ifs.close();

    // 计算重心
    float sumX = 0, sumY = 0, sumZ = 0;
    for (const auto& point : points) {
        sumX += get<0>(point);
        sumY += get<1>(point);
        sumZ += get<2>(point);
    }
    float centroidX = sumX / points.size();
    float centroidY = sumY / points.size();
    float centroidZ = sumZ / points.size();

    // 将重心信息写入原文件末尾
    ofstream ofs(input_filename, ios::app);
    if (!ofs.is_open()) {
        cerr << "无法打开输入文件以追加: " << input_filename << endl;
        return;
    }
    ofs << fixed << setprecision(3) << centroidX << "," << centroidY << "," << centroidZ << endl;
    ofs.close();

    // 将所有点偏移并写入新文件
    ofstream ofsOffset(output_filename);
    if (!ofsOffset.is_open()) {
        cerr << "无法打开输出文件: " << output_filename << endl;
        return;
    }
    ofsOffset << header << endl; // 写入文件头
    for (const auto& point : points) {
        float x = get<0>(point) + 100.0f; // x 正方向偏移 100 米
        float y = get<1>(point) - 50.0f;  // y 负方向偏移 50 米
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