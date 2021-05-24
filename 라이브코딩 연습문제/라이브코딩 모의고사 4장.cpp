#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Container {
private:
	string title; // 컨테이너 타이틀
	char* author; // 컨테이너 작성자 이름 (동적 할당)
	int size; // 컨테이너에 저장된 정수 배열 크기
	int* arr; // 정수를 저장하는 배열 (동적 할당)
public:
	void display();
	Container(string title, char* author,
		int size, int* arr);
	~Container();
	void replace_subtitle(string from, string to);
	void replace_first_last();
};

// 여기에 Container 클래스 멤버 함수들을 구현할 것
Container::Container(string title, char* author, int size, int* arr)
{
	int len = strlen(author);
	this->title = title;
	this->author = new char[len + 1];
	strcpy(this->author, author);
	this->size = size;
	this->arr = new int[size];

	for (int i = 0; i < size; i++)
	{
		this->arr[i] = arr[i];
	}
	cout << "Container 생성자 호출" << endl;
	display();
}

void Container::display() {
	cout << "title:" << title << "," << endl;
	cout << "author:" << author << ", size:" << size << endl;
	cout << "arr[] = ";
	
	for (int i = 0; i < size - 1; i++)
		cout << arr[i] << ", ";
	cout << arr[size-1];
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
	while(i != -1)
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
		title.replace(0, first.size(),last);
		title.replace(i, last.size(), first);

		// replace(시작 인덱스 위치, 길이, 문자열)
		// string.find("a") => string문자열에서 a라는 문자를 찾은 후 그 인덱스를 반환함
	}
	display();
}
int main() {
	string title("First title long title of title Last");
	char author[] = "Chosun Universty";
	int arr[5] = { 1, 2, 3, 4, 5 };
	Container c(title, author, 5, arr);
	cout << "제목에서 \"title\" 단어를 \"name\" 단어로 모두 바꿉니다." << endl;
	c.replace_subtitle("title", "name");
	cout << "제목의 첫 단어와 마지막 단어의 위치를  바꿉니다." << endl;
	c.replace_first_last();
}