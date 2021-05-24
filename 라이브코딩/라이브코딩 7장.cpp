// string 데이터를 처리할 수 있는 스택 코드를 작성하라.
// 아래 코드와 주석을 이해하고 필요한 내용을 코딩하라.
// iostream, string 헤드 파일 include
#include <iostream> 
#include <string>

using namespace std;

class MyStack;
MyStack operator +(const MyStack& s1, const MyStack& s2);
class MyStack {
private:
    string* element; // 스택의 메모리로 사용할 포인터
    int size;           // 스택의 최대 크기
    int tos;            // 스택의 top을 가리키는 인덱스
public:
    MyStack(int size);    // 생성자 스택의 최대 크기를 입력 받아서 element 객체 배열을 생성해줌.
    MyStack(const MyStack& s);  // 깊은 복사 생성자
    ~MyStack();           // 소멸자

    bool push(string item); // item을 스택에 삽입
          // 스택이 가득 차 있으면 false를, 아니면 true 리턴
    bool pop(string& item); // 스택의 탑에 있는 값을 item에 반환  그리고 top에 있는 자료 삭제
    bool peek(string& item); // 스택의 탑에 있는 값을 item에 반환
    void print_stack();  // 스택 내용 출력
    MyStack& operator << (string item);
    MyStack& operator >> (string &item);
    bool operator !();
    MyStack& operator =(const MyStack &s);
    friend MyStack operator+(const MyStack& s1, const MyStack& s2);
};


// 위에 코드는 수정 불가

// 여기에 MyStack의 모든 멤버 함수들을 작성하라.

MyStack::MyStack(int size)
{
    this->size = size;
    this->tos = -1;
    this->element = new string[size];
}
MyStack::MyStack(const MyStack& s)
{
    this->tos = s.tos;
    this->size = s.size;
    this->element = new string[s.size];
    for (int i = 0; i < s.size; i++)
    {
        this->element[i] = s.element[i];
    }
}
MyStack::~MyStack()
{
    delete[] element;
}

bool MyStack::peek(string& item)
{
    if (tos == -1)
    {
        cout << "stack is empty" << endl;
        return false;
    }
    else
        item = element[tos];
    return true;
}
void MyStack::print_stack()
{
    for (int i = 0; i <= tos; i++)
    {
        cout << element[i] << " ";
    }
    cout << endl << endl;
}

bool MyStack::push(string item)
{
    if (tos == size - 1)
    {
        cout << "stack is full" << endl;
        return false;
    }
    else
        element[++tos] = item;
    return true;
}
bool MyStack::pop(string& item)
{
    if (tos == -1)
    {
        cout << "stack is empty" << endl;
        return false;
    }
    else
        item = element[tos--];

    return true;

}
MyStack& MyStack::operator << (string item) {
    push(item);
    return *this;
}
MyStack& MyStack::operator >> (string& item) {
    pop(item);
    return *this;
}
bool MyStack::operator !() {
    if (tos == -1)
        return true;
    return false;
}
MyStack& MyStack::operator =(const MyStack& s) {

    if(this->element)
        delete[] this->element;

    this->tos = s.tos;
    this->size = s.size;
    this->element = new string[s.size];
    for (int i = 0; i < s.size; i++)
    {
        this->element[i] = s.element[i];
    }

    return *this;
}
MyStack operator+(const MyStack& s1, const MyStack& s2) {

    int size = s1.size + s2.size;
    MyStack tmp(size);
    int i;
    for (i = 0; i <= s1.tos; i++)
    {
        tmp.push(s1.element[i]);
    }
    for (i = 0; i <= s2.tos; i++)
    {
        tmp.push(s2.element[i]);
    }

    return tmp;
}

// 아래 코드는 수정 불가

int main() {

    int size, half;
    string  item;

    cout << "Enter the first stack size : ";
    cin >> size;
    half = size / 2;

    MyStack s1(size), s2(size), s3(size);

    for (int i = 0; i < size; i++) {
        item = to_string(i + 10000); // integer -> string translation
        s1.push(item);
    }
    while (!s1 == false)
        s1.pop(item);
    cout << "After automatic push and pop, s1 is (should be empty)" << endl;
    s1.print_stack();

    for (int i = 0; i < half; i++)
        s1 << to_string(i + 100); // push
    cout << "After automatic half << (push), s1 is" << endl;
    s1.print_stack();

    s1 << "11" << "22" << "33"; // continuous push
    cout << "After s1 << \"10\" << \"20\" << \"30\";, s1 is" << endl;
    s1.print_stack();

    s2 = s1;
    cout << "After s2 = s1, s2 is" << endl;
    s2.print_stack();

    for (int i = 0; i < half; i++)
        s3 << to_string(i + 1000); // push
    cout << "After automatic push, s3 is" << endl;
    s3.print_stack();

    s3 = s1 + s2 + s3;
    cout << "After s3 = s1 + s2 + s3, s3 is" << endl;
    s3.print_stack();

    cout << "Continuous >> (pop) of s1" << endl;
    while (!s1 == false) {
        s1 >> item;
        cout << item << ' ';
    }
    cout << endl << endl;

    string i1, i2, i3;
    s2 >> i1 >> i2 >> i3;
    cout << "After s2 >> i1 >> i2 >> i3, s2 is" << endl;
    s2.print_stack();
    cout << "i1, i2, i3 are " << i1 << ", " << i2 << ", " << i3 << endl << endl;
}