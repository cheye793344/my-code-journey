/*
1.rightTriangle（直角三角形）
描述

请编写一个rightTriangle类，该类包含私有数据成员a, b, c（int类型），表示直角三角形三个边的边长。这个类需要包含一个构造函数，用于初始化数据成员的值；一个成员函数isRightTriangle()，用来判断输入的三个整数是否能构成直角三角形；还有一个成员函数area()，用于计算该直角三角形的面积。提交的代码应能通过以下主函数的测试。

int main()
{
    int a, b, c;
    while (cin >> a >> b >> c) {
        rightTriangle tri(a, b, c);
        if (tri.isRightTriangle())
            cout << tri.area() << "\n";
        else
            cout << "not right triangle\n";
    }

    return 0;
}
注意：本题的主函数部分已在后台包含，提交代码时去掉主函数部分。


输入

输入3个整数，表示直角三角形三个边的边长。输入数据保证 a < b < c。


    输出

    如果输入数据能构成直角三角形（判直角三角形的公式为aa + bb == cc），那么输出直角三角形的面积（面积计算公式为(ab) / 2.0）；否则输出"not right triangle\n"。


    输入样例 1

    3 4 5
    1 2 3
    输出样例 1

    6
    not right triangle
    提示

    此题考点为：类的定义和实现。分值：20分

    来源

    xyy
    
#include<iostream>
using namespace std;
class rightTriangle {
public:
    rightTriangle(int a, int b, int c):a(a), b(b), c(c) {}
    bool isRightTriangle();
    double area();
private:
    int a, b, c;
};
bool rightTriangle::isRightTriangle() {
    return a*a + b*b == c*c;
}
double rightTriangle::area() {
    return a * b / 2.0;
}
int main()
{
    int a, b, c;
    while (cin >> a >> b >> c) {
        rightTriangle tri(a, b, c);
        if (tri.isRightTriangle())
            cout << tri.area() << "\n";
        else
            cout << "not right triangle\n";
    }

    return 0;
}
2.freshmenSportsMeeting（新生运动会）
描述

作为大一新生，同学们需要参加新生运动会。此题要求编写程序，通过以下主函数的测试，帮助新生运动会的工作人员完成运动项目的统计。

int main(){
    sportsMeeting freshman_sports;   // 新生运动会 
    string sport_name;   // 某项运动名称 
    int number_of_participants; // 参加某项运动的人数 
    while(cin>>sport_name>>number_of_participants && number_of_participants!=0){
        freshman_sports.add_sport(sport(sport_name,number_of_participants)); // 添加某项运动到运动会项目列表中 
    }

    int number = sportsMeeting::get_number();   // 运动会中的项目数 
    const sport * sports = freshman_sports.get_sports();  // 运动会项目列表 

    cout<<number<<'\n';   // 输出运动会的项目数 
    for(int i=0;i<number;i++)  // 输出每个运动项目的名称和参加人数 
        cout<<sports[i].get_name()<<' '<<sports[i].get_number_of_participants()<<'\n';

    return 0;
}

分析：本题包含两个类。第一个是运动项目类sport，包含两个数据成员，分别是运动项目名称（string类型，中间无空格）和参加此项运动的人数（int类型）；第二个是运动会类sportsMeeting，包含两个数据成员，分别是运动会项目列表（sport类型的数组，数组大小可设置为20，输入数据保证不超过20种运动项目）和运动会的项目数（int类型）。

注意：本题的主函数部分已在后台包含，提交代码时去掉主函数部分。


输入

输入若干项运动项目，每项运动项目包括运动项目名称和参加此项运动的人数。当输入的参加某项运动的人数为0时，输入结束，最后输入的一行项目名为“end”，不统计。


输出

第一行输出新生运动会的项目数。接下来输出所有的运动项目，每个运动项目占一行，包括运动项目名称和参加此项运动的人数（中间用空格间隔）。


输入样例 1 

sprints 30
long-distance 15
hurdling 20
jumping 40
end 0
输出样例 1

4
sprints 30
long-distance 15
hurdling 20
jumping 40
提示

此题考点包括自定义类型数据成员、静态数据成员和成员函数。分值：20分

来源


#include<iostream>
#include<string>
using namespace std;

class sport {
private:
    string name;
    int number_of_participants;
public:
    sport() :name(""), number_of_participants(0) {}
    sport(string sport_name, int number_of_participants):name(sport_name), number_of_participants(number_of_participants){}
    string get_name()const;
    int get_number_of_participants()const;
};

string sport::get_name()const { return name; }
int sport::get_number_of_participants()const{ return number_of_participants; }

class sportsMeeting {
private:
    sport sports[20];
    static int number;
public:
    sportsMeeting() {}
    static int get_number();
    void add_sport(sport sport);
    const sport* get_sports()const;
};

int sportsMeeting::number = 0;
int sportsMeeting::get_number() { return number; }
void sportsMeeting::add_sport(sport sport) {
    sports[number] = sport;
    number++;
}
const sport* sportsMeeting::get_sports()const { return sports; }

int main() {
    sportsMeeting freshman_sports;   // 新生运动会 
    string sport_name;   // 某项运动名称 
    int number_of_participants; // 参加某项运动的人数 
    while (cin >> sport_name >> number_of_participants && number_of_participants != 0) {
        freshman_sports.add_sport(sport(sport_name, number_of_participants)); // 添加某项运动到运动会项目列表中 
    }

    int number = sportsMeeting::get_number();   // 运动会中的项目数 
    const sport* sports = freshman_sports.get_sports();  // 运动会项目列表 

    cout << number << '\n';   // 输出运动会的项目数 
    for (int i = 0; i < number; i++)  // 输出每个运动项目的名称和参加人数 
        cout << sports[i].get_name() << ' ' << sports[i].get_number_of_participants() << '\n';

    return 0;
} 

2.animatedCartoon（动漫）
描述

很多同学爱看动漫。此题要求同学们编写程序，通过以下两个函数的测试，完成动漫相关内容的输入和输出。

void show(const cartoon & c){
    c.print();
}

int main(){
    string name_of_voiceActor, gender_of_voiceActor; 
    cin>>name_of_voiceActor>>gender_of_voiceActor; // 输入配音演员的姓名和性别 
    const voiceActor va(name_of_voiceActor,gender_of_voiceActor); // 定义一个常配音演员对象 
    cout<<"voice actor: "<<va.get_name()<<", "<<va.get_gender()<<'\n'; // 输出配音演员的姓名和性别 

    string name_of_cartoon;
    cin>>name_of_cartoon; // 输入动漫片的名字 
    const cartoon c(name_of_cartoon,va); // 构造一个常动漫片对象 

    int number_of_seasons;
    cin>>number_of_seasons; // 输入季度动漫片的季度数（比如第7季） 
    const seasonsCartoon sc(name_of_cartoon, va, number_of_seasons); // 构造一个常季度动漫片对象 

    show(c); // 输出动漫片的名字，所用的配音演员的名字和性别（参见输出样例） 
    cout<<"\n";
    show(sc); // 输出季度动画片的名字，所用的配音演员的名字、性别，以及季度数（参见输出样例）

    return 0;
}

分析：本题包含三个类。第一个是配音演员类voiceActor，包含两个数据成员，分别是配音演员的名字（string类型，中间无空格）和性别（string类型，中间无空格）；第二个是动漫片类cartoon，也包含两个数据成员，分别是动漫片的名字（string类型，中间无空格）和所用的配音演员；第三个是季度动漫片类seasonsCartoon，它继承cartoon类，增加了一个数据成员季度数（int类型），表示该动漫片共有多少季。

注意：本题的show函数和main函数已在后台包含，提交代码时去掉这两个函数部分。


输入

首先输入配音演员的名字和性别；再输入动漫片的名字；最后输入季度动漫片的季度数。


输出

输出共六行。第一行输出配音演员的名字和性别（冒号和逗号后面各有一个空格）；第二行和第三行输出动漫片对象的信息，其中第二行输出动漫片的名字（冒号后有空格），第三行输出所用的配音演员的名字和性别；第四行到第六行输出季度动漫片的信息，其中第四行输出季度动漫片的名字，第五行输出所用的配音演员的名字和性别，第六行输出季度动漫片的季度数（冒号后有空格）。


输入样例 1 

Harley female
PeppaPig
7
输出样例 1

voice actor: Harley, female
cartoon name: PeppaPig
voice actor: Harley, female
cartoon name: PeppaPig
voice actor: Harley, female
number of seasons: 7
提示

此题考点包括常成员函数、继承和虚函数。分值：20分


#include<iostream>
#include<string>
using namespace std;

class voiceActor {
private:
    string name_of_voiceactor;
    string gender;
public:
    voiceActor(string name, string gender) :name_of_voiceactor(name), gender(gender) {}
    string get_name()const;
    string get_gender()const;
};
string voiceActor::get_name() const{ return name_of_voiceactor; }
string voiceActor::get_gender() const{ return gender; }

class cartoon {
protected:
    string name_of_cartoon;
    voiceActor cv;
public:
    cartoon(string name,const voiceActor& cv) :name_of_cartoon(name), cv(cv) {}
    virtual void print()const;
};
    void cartoon::print()const {
    cout << "cartoon name: " << name_of_cartoon << endl;
    cout << "voice actor: " << cv.get_name() << ", " << cv.get_gender();
}

class seasonsCartoon :public cartoon{
private:
    int season;
public:
    seasonsCartoon(string name, const voiceActor& cv, int s) :cartoon(name, cv), season(s) {}
    void print()const override;
};
void seasonsCartoon::print()const {
    cout << "cartoon name: " << name_of_cartoon << endl;
    cout << "voice actor: " << cv.get_name() << ", " << cv.get_gender() << endl;
    cout << "number of seasons: " << season;
}

void show(const cartoon& c) {
    c.print();
}

int main() {
    string name_of_voiceActor, gender_of_voiceActor;
    cin >> name_of_voiceActor >> gender_of_voiceActor; // 输入配音演员的姓名和性别 
    const voiceActor va(name_of_voiceActor, gender_of_voiceActor); // 定义一个常配音演员对象 
    cout << "voice actor: " << va.get_name() << ", " << va.get_gender() << '\n'; // 输出配音演员的姓名和性别 

    string name_of_cartoon;
    cin >> name_of_cartoon; // 输入动漫片的名字 
    const cartoon c(name_of_cartoon, va); // 构造一个常动漫片对象 

    int number_of_seasons;
    cin >> number_of_seasons; // 输入季度动漫片的季度数（比如第7季） 
    const seasonsCartoon sc(name_of_cartoon, va, number_of_seasons); // 构造一个常季度动漫片对象 

    show(c); // 输出动漫片的名字，所用的配音演员的名字和性别（参见输出样例） 
    cout << "\n";
    show(sc); // 输出季度动画片的名字，所用的配音演员的名字、性别，以及季度数（参见输出样例）
    
    return 0;
}

4.NArray（浮点数数组）
描述

定义并实现自定义数组NArray类。NArray类数据成员包括长度（int）以及数据指针（double *），NArray类至少包含5个成员函数，分别是构造函数、拷贝构造函数、求模函数Magnitude、重载的赋值运算符= 和 析构函数。编写代码，通过以下主函数的测试。

其中，Magnitude为数组的模，其值为数组各个元素的平方和的平方根（求平方根的函数可以用 sqrt()，需要 #include）。

int main() 
{
    double arr1[] = { 1, 2, 3 };
    // sizeof(arr1) / sizeof(double) 算出数组的长度 
    NArray test1(arr1, sizeof(arr1) / sizeof(double)); // 构造函数 
    cout << test1.Magnitude() << endl;

    NArray copytest(test1); // 拷贝构造函数 
    cout << copytest.Magnitude() << endl;

    int n;
    cin >> n;
    double * arr2 = new double[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr2[i];
    }
    NArray test2(arr2, n);
    cout << test2.Magnitude() << endl;

    NArray test3 = test2; // 拷贝构造函数 
    cout << test3.Magnitude() << endl;

    NArray test4;
    test4 = test2; // 重载赋值运算符 
    cout << test4.Magnitude() << endl;

    return 0;
}
注意：主函数已在后台包含，提交代码是去掉这部分。


输入

输入包含两行数据。第一行是整数n，表示数组的长度；第二行是n个浮点数。


输出

见输出样例


输入样例 1 

3
1.2 2.3 3.4
输出样例 1

3.74166
3.74166
4.27668
4.27668
4.27668
提示

此题考点为：构造函数、拷贝构造函数、赋值运算符重载和析构函数。

分值：20分

来源

xyy

#include<iostream>
#include<cmath>
using namespace std;

class NArray {
private:
    double* data;
    int length;
public:
    NArray() :data(nullptr), length(0) {}
    NArray(double* arr, int len): data(arr), length(len){
        data = new double[len];
        for (int i = 0; i < len; ++i) {
            data[i] = arr[i];
        }
    }
    NArray(const NArray& other) :length(other.length){
        data = new double[length];
        for (int i = 0; i < length; ++i) {
            data[i] = other.data[i];
        }
    }
    ~NArray() { if(data!=NULL)delete[] data; }
    double Magnitude() {
        double sum = 0.0;
        for (int i = 0; i < length; ++i) {
            sum += data[i] * data[i];
        }
        return sqrt(sum);
    }
    NArray& operator=(const NArray& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new double[length];
            for (int i = 0; i < length; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
};

int main()
{
    double arr1[] = { 1, 2, 3 };
    // sizeof(arr1) / sizeof(double) 算出数组的长度 
    NArray test1(arr1, sizeof(arr1) / sizeof(double)); // 构造函数 
    cout << test1.Magnitude() << endl;

    NArray copytest(test1); // 拷贝构造函数 
    cout << copytest.Magnitude() << endl;

    int n;
    cin >> n;
    double* arr2 = new double[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr2[i];
    }
    NArray test2(arr2, n);
    cout << test2.Magnitude() << endl;

    NArray test3 = test2; // 拷贝构造函数 
    cout << test3.Magnitude() << endl;

    NArray test4;
    test4 = test2; // 重载赋值运算符 
    cout << test4.Magnitude() << endl;

    return 0;
}

5.Matrix（矩阵）
描述

实现一个3*3的整型矩阵类simpleMatrix，通过以下主函数的测试。

int main(){
    simpleMatrix m1, m2; // 定义两个3*3的整型矩阵对象 
    cin>>m1>>m2; // 输入这两个矩阵 
    cout<<m1+m2; // 输出这两个矩阵相加的结果 
    return 0;
}

注意：本题的主函数部分已在后台包含，提交代码时去掉主函数部分。


输入

输入为两行，每行9个整数，每行表示一个3*3的矩阵


输出

输出为三行，每行3个整数，整数和整数之间用空格间隔，每行的最后一个整数后面没有空格，直接换行；最后一行（第3行）后面无换行符


输入样例 1 

0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1
输出样例 1

1 1 1
1 1 1
1 1 1
提示

提示：矩阵加法是把两个矩阵的对应元素一一相加

分值：20分

来源

xyy


#include<iostream>
using namespace std;

class simpleMatrix {
private:
    int matrix[3][3];
public:
    simpleMatrix() {
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                matrix[i][j] = 0;
            }
        }
    }
    friend istream& operator>>(istream& is, simpleMatrix& m);
    friend ostream& operator<<(ostream& os, const simpleMatrix& m);
    friend simpleMatrix operator+(const simpleMatrix& a, const simpleMatrix& b);
};

istream& operator>>(istream& is, simpleMatrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            is >> m.matrix[i][j];
        }
    }
    return is;
}

ostream& operator<<(ostream& os, const simpleMatrix& m) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            os << m.matrix[i][j];
            if (j < 2)os << " ";
        }
        if (i < 2)os << endl;
    }
    return os;
}

simpleMatrix operator+(const simpleMatrix& a, const simpleMatrix& b) {
    simpleMatrix result;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            result.matrix[i][j] = a.matrix[i][j] + b.matrix[i][j];
        }
    }
    return result;
}

int main() {
    simpleMatrix m1, m2; // 定义两个3*3的整型矩阵对象 
    cin >> m1 >> m2; // 输入这两个矩阵 
    cout << m1 + m2; // 输出这两个矩阵相加的结果 
    return 0;
}
*/