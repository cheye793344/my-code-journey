/*
1.rightTriangle��ֱ�������Σ�
����

���дһ��rightTriangle�࣬�������˽�����ݳ�Աa, b, c��int���ͣ�����ʾֱ�������������ߵı߳����������Ҫ����һ�����캯�������ڳ�ʼ�����ݳ�Ա��ֵ��һ����Ա����isRightTriangle()�������ж���������������Ƿ��ܹ���ֱ�������Σ�����һ����Ա����area()�����ڼ����ֱ�������ε�������ύ�Ĵ���Ӧ��ͨ�������������Ĳ��ԡ�

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
ע�⣺������������������ں�̨�������ύ����ʱȥ�����������֡�


����

����3����������ʾֱ�������������ߵı߳����������ݱ�֤ a < b < c��


    ���

    ������������ܹ���ֱ�������Σ���ֱ�������εĹ�ʽΪaa + bb == cc������ô���ֱ�������ε������������㹫ʽΪ(ab) / 2.0�����������"not right triangle\n"��


    �������� 1

    3 4 5
    1 2 3
    ������� 1

    6
    not right triangle
    ��ʾ

    ���⿼��Ϊ����Ķ����ʵ�֡���ֵ��20��

    ��Դ

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
2.freshmenSportsMeeting�������˶��ᣩ
����

��Ϊ��һ������ͬѧ����Ҫ�μ������˶��ᡣ����Ҫ���д����ͨ�������������Ĳ��ԣ����������˶���Ĺ�����Ա����˶���Ŀ��ͳ�ơ�

int main(){
    sportsMeeting freshman_sports;   // �����˶��� 
    string sport_name;   // ĳ���˶����� 
    int number_of_participants; // �μ�ĳ���˶������� 
    while(cin>>sport_name>>number_of_participants && number_of_participants!=0){
        freshman_sports.add_sport(sport(sport_name,number_of_participants)); // ���ĳ���˶����˶�����Ŀ�б��� 
    }

    int number = sportsMeeting::get_number();   // �˶����е���Ŀ�� 
    const sport * sports = freshman_sports.get_sports();  // �˶�����Ŀ�б� 

    cout<<number<<'\n';   // ����˶������Ŀ�� 
    for(int i=0;i<number;i++)  // ���ÿ���˶���Ŀ�����ƺͲμ����� 
        cout<<sports[i].get_name()<<' '<<sports[i].get_number_of_participants()<<'\n';

    return 0;
}

������������������ࡣ��һ�����˶���Ŀ��sport�������������ݳ�Ա���ֱ����˶���Ŀ���ƣ�string���ͣ��м��޿ո񣩺ͲμӴ����˶���������int���ͣ����ڶ������˶�����sportsMeeting�������������ݳ�Ա���ֱ����˶�����Ŀ�б�sport���͵����飬�����С������Ϊ20���������ݱ�֤������20���˶���Ŀ�����˶������Ŀ����int���ͣ���

ע�⣺������������������ں�̨�������ύ����ʱȥ�����������֡�


����

�����������˶���Ŀ��ÿ���˶���Ŀ�����˶���Ŀ���ƺͲμӴ����˶���������������Ĳμ�ĳ���˶�������Ϊ0ʱ�������������������һ����Ŀ��Ϊ��end������ͳ�ơ�


���

��һ����������˶������Ŀ����������������е��˶���Ŀ��ÿ���˶���Ŀռһ�У������˶���Ŀ���ƺͲμӴ����˶����������м��ÿո�������


�������� 1 

sprints 30
long-distance 15
hurdling 20
jumping 40
end 0
������� 1

4
sprints 30
long-distance 15
hurdling 20
jumping 40
��ʾ

���⿼������Զ����������ݳ�Ա����̬���ݳ�Ա�ͳ�Ա��������ֵ��20��

��Դ


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
    sportsMeeting freshman_sports;   // �����˶��� 
    string sport_name;   // ĳ���˶����� 
    int number_of_participants; // �μ�ĳ���˶������� 
    while (cin >> sport_name >> number_of_participants && number_of_participants != 0) {
        freshman_sports.add_sport(sport(sport_name, number_of_participants)); // ���ĳ���˶����˶�����Ŀ�б��� 
    }

    int number = sportsMeeting::get_number();   // �˶����е���Ŀ�� 
    const sport* sports = freshman_sports.get_sports();  // �˶�����Ŀ�б� 

    cout << number << '\n';   // ����˶������Ŀ�� 
    for (int i = 0; i < number; i++)  // ���ÿ���˶���Ŀ�����ƺͲμ����� 
        cout << sports[i].get_name() << ' ' << sports[i].get_number_of_participants() << '\n';

    return 0;
} 

2.animatedCartoon��������
����

�ܶ�ͬѧ��������������Ҫ��ͬѧ�Ǳ�д����ͨ���������������Ĳ��ԣ���ɶ���������ݵ�����������

void show(const cartoon & c){
    c.print();
}

int main(){
    string name_of_voiceActor, gender_of_voiceActor; 
    cin>>name_of_voiceActor>>gender_of_voiceActor; // ����������Ա���������Ա� 
    const voiceActor va(name_of_voiceActor,gender_of_voiceActor); // ����һ����������Ա���� 
    cout<<"voice actor: "<<va.get_name()<<", "<<va.get_gender()<<'\n'; // ���������Ա���������Ա� 

    string name_of_cartoon;
    cin>>name_of_cartoon; // ���붯��Ƭ������ 
    const cartoon c(name_of_cartoon,va); // ����һ��������Ƭ���� 

    int number_of_seasons;
    cin>>number_of_seasons; // ���뼾�ȶ���Ƭ�ļ������������7���� 
    const seasonsCartoon sc(name_of_cartoon, va, number_of_seasons); // ����һ�������ȶ���Ƭ���� 

    show(c); // �������Ƭ�����֣����õ�������Ա�����ֺ��Ա𣨲μ���������� 
    cout<<"\n";
    show(sc); // ������ȶ���Ƭ�����֣����õ�������Ա�����֡��Ա��Լ����������μ����������

    return 0;
}

������������������ࡣ��һ����������Ա��voiceActor�������������ݳ�Ա���ֱ���������Ա�����֣�string���ͣ��м��޿ո񣩺��Ա�string���ͣ��м��޿ո񣩣��ڶ����Ƕ���Ƭ��cartoon��Ҳ�����������ݳ�Ա���ֱ��Ƕ���Ƭ�����֣�string���ͣ��м��޿ո񣩺����õ�������Ա���������Ǽ��ȶ���Ƭ��seasonsCartoon�����̳�cartoon�࣬������һ�����ݳ�Ա��������int���ͣ�����ʾ�ö���Ƭ���ж��ټ���

ע�⣺�����show������main�������ں�̨�������ύ����ʱȥ���������������֡�


����

��������������Ա�����ֺ��Ա������붯��Ƭ�����֣�������뼾�ȶ���Ƭ�ļ�������


���

��������С���һ�����������Ա�����ֺ��Ա�ð�źͶ��ź������һ���ո񣩣��ڶ��к͵������������Ƭ�������Ϣ�����еڶ����������Ƭ�����֣�ð�ź��пո񣩣�������������õ�������Ա�����ֺ��Ա𣻵����е�������������ȶ���Ƭ����Ϣ�����е�����������ȶ���Ƭ�����֣�������������õ�������Ա�����ֺ��Ա𣬵�����������ȶ���Ƭ�ļ�������ð�ź��пո񣩡�


�������� 1 

Harley female
PeppaPig
7
������� 1

voice actor: Harley, female
cartoon name: PeppaPig
voice actor: Harley, female
cartoon name: PeppaPig
voice actor: Harley, female
number of seasons: 7
��ʾ

���⿼���������Ա�������̳к��麯������ֵ��20��


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
    cin >> name_of_voiceActor >> gender_of_voiceActor; // ����������Ա���������Ա� 
    const voiceActor va(name_of_voiceActor, gender_of_voiceActor); // ����һ����������Ա���� 
    cout << "voice actor: " << va.get_name() << ", " << va.get_gender() << '\n'; // ���������Ա���������Ա� 

    string name_of_cartoon;
    cin >> name_of_cartoon; // ���붯��Ƭ������ 
    const cartoon c(name_of_cartoon, va); // ����һ��������Ƭ���� 

    int number_of_seasons;
    cin >> number_of_seasons; // ���뼾�ȶ���Ƭ�ļ������������7���� 
    const seasonsCartoon sc(name_of_cartoon, va, number_of_seasons); // ����һ�������ȶ���Ƭ���� 

    show(c); // �������Ƭ�����֣����õ�������Ա�����ֺ��Ա𣨲μ���������� 
    cout << "\n";
    show(sc); // ������ȶ���Ƭ�����֣����õ�������Ա�����֡��Ա��Լ����������μ����������
    
    return 0;
}

4.NArray�����������飩
����

���岢ʵ���Զ�������NArray�ࡣNArray�����ݳ�Ա�������ȣ�int���Լ�����ָ�루double *����NArray�����ٰ���5����Ա�������ֱ��ǹ��캯�����������캯������ģ����Magnitude�����صĸ�ֵ�����= �� ������������д���룬ͨ�������������Ĳ��ԡ�

���У�MagnitudeΪ�����ģ����ֵΪ�������Ԫ�ص�ƽ���͵�ƽ��������ƽ�����ĺ��������� sqrt()����Ҫ #include����

int main() 
{
    double arr1[] = { 1, 2, 3 };
    // sizeof(arr1) / sizeof(double) �������ĳ��� 
    NArray test1(arr1, sizeof(arr1) / sizeof(double)); // ���캯�� 
    cout << test1.Magnitude() << endl;

    NArray copytest(test1); // �������캯�� 
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

    NArray test3 = test2; // �������캯�� 
    cout << test3.Magnitude() << endl;

    NArray test4;
    test4 = test2; // ���ظ�ֵ����� 
    cout << test4.Magnitude() << endl;

    return 0;
}
ע�⣺���������ں�̨�������ύ������ȥ���ⲿ�֡�


����

��������������ݡ���һ��������n����ʾ����ĳ��ȣ��ڶ�����n����������


���

���������


�������� 1 

3
1.2 2.3 3.4
������� 1

3.74166
3.74166
4.27668
4.27668
4.27668
��ʾ

���⿼��Ϊ�����캯�����������캯������ֵ��������غ�����������

��ֵ��20��

��Դ

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
    // sizeof(arr1) / sizeof(double) �������ĳ��� 
    NArray test1(arr1, sizeof(arr1) / sizeof(double)); // ���캯�� 
    cout << test1.Magnitude() << endl;

    NArray copytest(test1); // �������캯�� 
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

    NArray test3 = test2; // �������캯�� 
    cout << test3.Magnitude() << endl;

    NArray test4;
    test4 = test2; // ���ظ�ֵ����� 
    cout << test4.Magnitude() << endl;

    return 0;
}

5.Matrix������
����

ʵ��һ��3*3�����;�����simpleMatrix��ͨ�������������Ĳ��ԡ�

int main(){
    simpleMatrix m1, m2; // ��������3*3�����;������ 
    cin>>m1>>m2; // �������������� 
    cout<<m1+m2; // ���������������ӵĽ�� 
    return 0;
}

ע�⣺������������������ں�̨�������ύ����ʱȥ�����������֡�


����

����Ϊ���У�ÿ��9��������ÿ�б�ʾһ��3*3�ľ���


���

���Ϊ���У�ÿ��3������������������֮���ÿո�����ÿ�е����һ����������û�пո�ֱ�ӻ��У����һ�У���3�У������޻��з�


�������� 1 

0 0 0 0 0 0 0 0 0
1 1 1 1 1 1 1 1 1
������� 1

1 1 1
1 1 1
1 1 1
��ʾ

��ʾ������ӷ��ǰ���������Ķ�ӦԪ��һһ���

��ֵ��20��

��Դ

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
    simpleMatrix m1, m2; // ��������3*3�����;������ 
    cin >> m1 >> m2; // �������������� 
    cout << m1 + m2; // ���������������ӵĽ�� 
    return 0;
}
*/