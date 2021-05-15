#include <iostream>
#include <string>

using namespace std;

class Person;
Person operator +(int hours, Person& p);

class Person {
protected:
    string varName;    // 변수 이름
    string* pName;        // 사람 이름
    int id;            // 고유한 ID 번호
    int hours;        // 일한 시간
public:
    Person(const string varName = "tmp", const string name = "임시변수", int id = 0, int hours = 0);
    ~Person();
    Person& operator +=(int hours);
    void print();
    Person& operator =(const Person& p);
    Person operator +(int hours);
    friend Person operator +(int hours, Person& p);
    bool operator ==(Person p);
    int operator () ();
    void whatAreYouDoing();
};
// 여기에 Person 클래스 멤버 함수들을 구현할 것
Person::Person(const string varName, const string name, int id, int hours) {
    cout << varName << ": Person(\"" << name << "\", " << id << ", " << hours << ")" << endl;
    this->varName = varName;
    this->pName = new string[size(name)];
    *pName = name;
    this->id = id;
    this->hours = hours;
    
}
Person::~Person() {
    cout << varName << ": ~Person()" << endl;

};
Person& Person::operator +=(int hours)
{
    this->hours += hours;
    cout << varName << " += " << hours << endl;
    return *this;
}
void Person::print() {
    cout << varName << ": Person::print(): [" << "이름:" << *pName << ", ID:" << id
        << ", 일한 시간:" << hours << "]" << endl;
}
Person& Person::operator =(const Person& p) {
    cout << this->varName << " = " << p.varName << endl;
    this->varName = p.varName;
    *(this->pName) = *(p.pName);
    this->id = p.id;
    this->hours = p.hours;
    return *this;
}
Person Person::operator +(int hours) {

    cout << this->varName << " + " << hours << endl;
    Person tmp;
    tmp = *this;
    tmp.hours += hours;

    return tmp;
}

Person operator +(int hours, Person &p) {
    cout << hours << " + " << p.varName << endl;
    Person tmp;
    tmp = p;
    tmp.hours += hours;
    return tmp;

}
bool Person::operator ==(Person p) {
    if (*pName == *p.pName && id == p.id)
    {
        cout << varName << " == " << p.varName << endl;
        return true;
    }
    else
        return false;
}
int Person::operator () () {
    int pay;
    pay = hours * 6800;
    cout << varName << ": Person::operator(): 최저임금을 적용한 임금: " << pay << endl;
    return pay;
}
void Person::whatAreYouDoing() {
    cout << varName << ": Person::whatAreYouDoing(): I am taking a rest." << endl;
}

int main() {
    Person p1("p1", "홍길동", 10001);
    Person p2("p2", "이몽룡", 10002, 1);
    Person p3("p3", "성춘향");
    Person p4("p4", "심청");
    cout << endl;
    (p1 += 1) += 2;     p1.print();    cout << endl;

    p3 = p3 + 3 + 4;    p3.print();    cout << endl;
    p4 = 5 + p4 + 2;    p4.print();    cout << endl;
    (p2 + 3).print();   (4 + p2).print();
    cout << boolalpha << (p1 == p3) << endl << endl;
    p2 = p3;
    cout << (p2 == p3) << endl << endl;
    p1();
    p1.whatAreYouDoing();              cout << endl;
}