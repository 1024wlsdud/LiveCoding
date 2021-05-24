
#include <iostream>
#include <string.h>

using namespace std;
// 복사 생성자, 묵시적인 복사 생성자 호출, 값(객체)에 의한 함수호출,
// 객체 참조자에 의한 함수 호출, 객체의 리턴, 객체 참조자 리턴 등을 활용할 수 있는 능력 검증

class Container {
private:
	string title; // 컨테이너 타이틀
	char* author; // 컨테이너 작성자 이름 (동적 할당)
	int size; // 컨테이너에 저장된 정수 배열 크기
	int* arr; // 정수를 저장하는 배열 (동적 할당)
public:
	void display();
	Container(string title, const char* author,
		int size, int* arr = nullptr);
	~Container();
	Container(const Container& c);
	void replace_subtitle(string from, string to);
	void replace_first_last();
	void add(int value);
	void set_title(string title);
	void print_title();
};

// 여기에 Container 클래스 멤버 함수들을 구현할 것
Container::Container(string title, const char* author, int size, int* arr)
{
	int len = strlen(author);
	this->title = title;
	this->author = new char[len + 1];
	strcpy(this->author, author);
	this->size = size;
	this->arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		this->arr[i] = ((arr != nullptr) ? arr[i] : 0);
	}
	cout << "Container 생성자 호출" << endl;
	display();

}
Container::Container(const Container& c)
{
	int len = strlen(c.author);
	this->title = c.title;
	this->author = new char[len + 1];
	strcpy(this->author, c.author);
	this->size = c.size;
	this->arr = new int[c.size];

	for (int i = 0; i < size; i++)
	{
		this->arr[i] = c.arr[i];
	}
	cout << "Container 복사 생성자 호출" << endl;
	display();

}
void Container::display() {
	cout << "title:" << title << "," << endl;
	cout << "author:" << author << ", size:" << size << endl;
	cout << "arr[] = ";

	for (int i = 0; i < size - 1; i++)
		cout << arr[i] << ", ";
	cout << arr[size - 1];
	cout << endl << endl;

}

Container::~Container() {
	cout << "Container 소멸자 호출" << endl;
	display();
	delete author;
	delete arr;
}
void Container::replace_subtitle(string from, string to) {

	int i = title.find(from);
	while (i != -1)
	{
		title.replace(i, from.size(), to);
		i = title.find(from);
	}
	display();
}
void Container::replace_first_last() {
	int i = title.find(" ");
	if (i != -1) {
		string first = title.substr(0, i);
		i = title.rfind(" ");
		string last = title.substr(i + 1);
		title.replace(0, first.size(), last);
		title.replace(i, last.size(), first);

		// replace(시작 인덱스 위치, 길이, 문자열)
		// string.find("a") => string문자열에서 a라는 문자를 찾은 후 그 인덱스를 반환함
	}
	display();
}

void Container::add(int value) {
	for (int i = 0; i < size; ++i)
		arr[i] += value;
}
void Container::set_title(string title) {
	this->title = title;
}

void Container::print_title() {
	cout << "print_title 호출: " << title << endl << endl;
}

class Manager {
public:
	Manager();
	static void call_by_value(Container c1); // 값에 의한 호출 방식
	static void call_by_reference(Container& c1);
	static Container return_value();
	static Container &return_reference(Container& rc);
};

void Manager::call_by_value(Container c1) {
	cout << "call_by_value(Container c1)호출 " << endl;
	c1.set_title("c1");
	c1.add(100);
	c1.display();
}
void Manager::call_by_reference(Container& c1) {
	cout << "call_by_reference(Container c1)호출 " << endl;
	c1.add(200);
	c1.display();
}

Container Manager::return_value() {
	cout << "return_value() 호출" << endl << endl;
	Container c2("d", "return_value()", 3); // 4번째 인자는 디폴트 매개변수 적용
	cout << "return_value()에서 리턴" << endl << endl;
	return c2;
}

Container & Manager::return_reference(Container& rc) {
	cout << "return_reference(Container & rc) 호출" << endl;
	rc.add(3000);
	rc.display();
	return rc;
}
int main() {
	int arr[5] = { 1, 2, 3, 4, 5 };
	char author[] = "main()";
	Container c("c", "author", 5, arr);

	// 함수 인자 c는 복사 생성자에 의해 매개변수 c1로 복사됨
	Manager::call_by_value(c);
	cout << "call_by_value(c)에서 리턴되었음. 현재 객체 c의 내용:" << endl;
	c.display(); // c 객체의 내용은 변동이 없어야 함

	Manager::call_by_reference(c);
	cout << "call_by_reference(c)에서 리턴되었음. 현재 객체 c의 내용 : " << endl;
	c.display(); // c 객체의 내용이 변경되어 있어야 함

	// 묵시적인 복사 생성자 호출
	Container d = Manager::return_value();
	cout << "현재 객체 d의 내용:" << endl;
	d.display(); // d의 arrp[값이 모두 1000 확인

	cout << "return_value().print_title() 실행" << endl;
	Manager::return_value().print_title();


	Container& e = Manager::return_reference(d); // 결국 e는 d를 참조하게 된다.
	cout << "return_reference(d)에서 리턴되었음. 현재 객체 d의 내용 : " << endl;
	d.display();	// d 객체의 arr[]의 내용이 모두 3000으로 변경되어 있어야 함

	cout << "현재 참조자 e의 내용:" << endl;
	e.display();	// e는 원본 객체 d를 참조하는 참조자: d와 동일한 내용를 보여줌
	cout << "main()에서 리턴함" << endl << endl;
}