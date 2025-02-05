﻿// string 데이터를 처리할 수 있는 스택 코드를 작성하라.
// 아래 코드와 주석을 이해하고 필요한 내용을 코딩하라.
// iostream, string 헤드 파일 include
#include <iostream> 
#include <string>

using namespace std;

class MyStack {
private:
	string* element; // 스택의 메모리로 사용할 포인터
	int size;           // 스택의 최대 크기
	int tos;            // 스택의 top을 가리키는 인덱스
public:
	MyStack(int size);    // 생성자 스택의 최대 크기를 입력 받아서 element 객체 배열을 생성해줌.
	MyStack(MyStack& s);  // 깊은 복사 생성자
	~MyStack();           // 소멸자

	bool push(string item); // item을 스택에 삽입
			// 스택이 가득 차 있으면 false를, 아니면 true 리턴
	bool pop(string& item); // 스택의 탑에 있는 값을 item에 반환  그리고 top에 있는 자료 삭제
	bool peek(string& item); // 스택의 탑에 있는 값을 item에 반환
	void print_stack();  // 스택 내용 출력

};

// 위에 코드는 수정 불가

// 여기에 MyStack의 모든 멤버 함수들을 작성하라.
MyStack::MyStack(int size)
{

	this->size = size;
	this->tos = -1;
	this->element = new string[size];
	cout << "MyStack(" << size << ") 생성자 호출" << endl;
}
MyStack::MyStack(MyStack& s)
{

	this->tos = s.tos;
	this->size = s.size;
	this->element = new string[size];
	for (int i = 0; i < size; i++)
	{
		this->element[i] = s.element[i];
	}
	cout << "MyStack(MyStack & s) 복사 생성자 호출 : tos + 1 = " << s.tos + 1 << endl;
}
MyStack::~MyStack()
{
	delete[]element;
	cout << "~MyStack 소멸자 호출 : tos + 1 = " << tos + 1 << endl;

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
	for (int i = 0; i < tos + 1; i++)
	{
		cout << element[i] << " ";
	}
	cout << endl;
}


// 아래 코드는 수정 불가

int main() {

	int stack_size;

	// 스택이 저장할수 있는 최대 크기를 입력 받는다
	cout << "Enter stack size : ";
	cin >> stack_size;

	// 스택을 생성해 줌
	MyStack first_stack(stack_size);

	// 입력할 데이터의 수를 입력 받는다
	// 데이터를 숫자 만큼 입력 받고 stack에 푸시한다.
	int  input_size;
	string  item;
	cout << "Enter number of input string : ";
	cin >> input_size;
	for (int i = 0; i < input_size; ++i) {
		cout << "Enter string : ";
		cin >> item;
		first_stack.push(item);
	}

	// 스택의 자료를 출력
	cout << "first stack : ";
	first_stack.print_stack();

	// 스택을 생성해 줌
	MyStack second_stack(first_stack);

	// 스택의 자료를 출력

	cout << "second stack : ";
	second_stack.print_stack();

	first_stack.pop(item);
	cout << "first stack pop : " << item << endl;
	second_stack.peek(item);
	cout << "second stack peek : " << item << endl;

	// 스택의 자료를 출력
	cout << "first stack : ";
	first_stack.print_stack();

	cout << "second stack : ";
	second_stack.print_stack();

	cout << "second stack all pop : " << endl;
	while (second_stack.pop(item))
		cout << item << endl;

	return 0;
}

/*****************
 * 프로그램 실행 결과
 *****************/
 /*
 Enter stack size : 5
 MyStack(5) 생성자 호출
 Enter number of input string : 7
 Enter string : kim
 Enter string : yang
 Enter string : park
 Enter string : shin
 Enter string : chung
 Enter string : jung
 stack is full
 Enter string : lee
 stack is full
 first stack : kim yang park shin chung
 MyStack(MyStack & s) 복사 생성자 호출 : tos + 1 = 5
 second stack : kim yang park shin chung
 first stack pop : chung
 second stack peek : chung
 first stack : kim yang park shin
 second stack : kim yang park shin chung
 second stack all pop :
 chung
 shin
 park
 yang
 kim
 stack is empty
 ~MyStack 소멸자 호출 : tos + 1 = 0
 ~MyStack 소멸자 호출 : tos + 1 = 4
 */
