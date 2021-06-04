#include <iostream>
#include <string>

using namespace std;

class Person {
protected:
    string varName;    // 변수 이름
    string* pName;        // 사람 이름
    int id;            // 고유한 ID 번호
    int hours;        // 일한 시간
public:
    Person(const string varName="tmp", const string name = "임시변수", int id = 0, int hours = 0);
    ~Person();
  
    void print();
    void whatAreYouDoing(); 
    Person& operator+= (int hours);
    int operator()();

};
// 여기에 Person 클래스 멤버 함수들을 구현할 것
Person::Person(const string varName, const string name, int id, int hours)
{
    cout << varName << ": Person(\"" << name << "\", " << id << ", " << hours << ")" << endl;
    this->varName = varName;
    this->pName = new string[name.length() + 1];
    *pName = name;
    this->id = id;
    this->hours = hours;
 
}
Person::~Person()
{
    cout << varName << ": ~Person()" << endl;
}
Person& Person::operator+= (int n) {
    this->hours += n;
    cout << varName << " += " << hours << endl;
    return *this;
}
void Person::print()
{
    cout << varName << ": Person::print(): [" << "이름:" << *pName << ", ID:" << id
        << ", 일한 시간:" << hours << "]" << endl;
}

int Person::operator()() {

    int pay = 6800 * hours;
    cout << varName << ": Person::operator(): 최저임금을 적용한 임금: " << pay << endl;
    return pay;
}

void Person::whatAreYouDoing() {
    cout << varName << ": Person::whatAreYouDoing(): I am taking a rest." << endl;
}

class Employee: public Person {
protected : 
    string company;        // 근무회사
    int payPerHour;        // 시간당임금
    int overtime;          // 초과근무시간 설정

public:
    Employee(string varName, string name, int id,
        string company, int payPerHour, int overtime);
    // 근무회사, 시간당임금, 초과근무시간 설정
    ~Employee();

    void printEmployee();
    void print();            // 직원 정보 출력
    void whatAreYouDoing();  // 현재하고 있는 일을 출력
    int operator () ();      // 지불해야 할 임금 계산
};

Employee::Employee(string varName, string name, int id, string company, int payPerHour, int overtime)
:Person(varName,name,id){
    cout << "    Employee(근무회사:" << company << ", 시간당임금:" << payPerHour <<
        ", 초과근무시간:" << overtime << ")" << endl;
    this->varName = varName;
    this->pName = new string[size(name) + 1];
    *pName = name;
    this->id = id;
    this->company = company;
    this->payPerHour = payPerHour;
    this->overtime = overtime;
}
Employee::~Employee()
{
    cout << varName << ": ~Employee()" << endl;
}
void Employee::printEmployee() {

    cout << "  : Employee::print(): [근무회사:" << company << ", 시간당임금:" << payPerHour <<
        ", 초과근무시간:" << overtime << "]" << endl;

}
void Employee::print() {
    Person::print();
    printEmployee();
}

int Employee::operator () () {
    int pay = (payPerHour * hours) + (overtime * payPerHour * 1.5);
    cout << varName << ": Employee::operator(): 총 임금(기본근무+초과근무): " << pay << endl;
    return pay;
}

void Employee::whatAreYouDoing() {
    cout << varName << ": Employee::whatAreYouDoing(): I am working." << endl;
}
class Student: public Person{
protected : 
    string university;    // 학생이 다니는 대학교 이름
    int year;             // 학년
    int tuition;          // 한 학기당 등록금 액수

public:
    Student(string varName, string name, int id,
        string university, int year, int tuition);
    // 대학교 이름, 학년, 학기당 등록금 액수 설정
    ~Student();

    void printStudent();
    void print();              // 학생 정보 출력
    void whatAreYouDoing();    // 현재하고 있는 일을 출력
    int operator () ();        // 지금까지 납부한 등록금 계산
};

Student::Student(string varName, string name, int id, string university, int year, int tuition) 
:Person(varName, name, id) {

    cout << "    Student(대학교명:" << university << ", 학년:" << year <<
        ", 학기당등록금:" << tuition << ")" << endl;
    this->varName = varName;
    this->pName = new string[size(name) + 1];
    *pName = name;
    this->id = id;
    this->university = university;
    this->year = year;
    this->tuition = tuition;
}

Student::~Student() {
    cout << varName << ": ~Student()" << endl;
}

void Student::printStudent() {
    cout << "  : Student::print(): [대학교명:" << university <<
        ", 학년:" << year << "학기당등록금:" << tuition <<  "]" << endl;
}
void Student::print() {
    Person::print();
    printStudent();
}
void Student::whatAreYouDoing() {
    cout << varName << ": Student::whatAreYouDoing(): I am studying." << endl;
}
int Student::operator () () {
    int scholarship = hours * 1000;
    if (scholarship >= tuition*year*2)
        scholarship = tuition * year * 2;
    cout << varName << ": Student::operator(): 총 장학금: " << scholarship << endl;
    return scholarship;
}

int main()
{
    Employee e1("e1", "홍길동 직원", 10001, "Samsung", 30000, 10);
    Student  s1("s1", "이몽룡 학생", 10002, "Chosun University", 4, 4000000);
    cout << endl;

    e1 += 200;
    s1 += 1000;              cout << endl;

    e1.print();
    s1.print();              cout << endl;

    e1();
    s1();                    cout << endl;

    e1.whatAreYouDoing();
    s1.whatAreYouDoing();    cout << endl;
}