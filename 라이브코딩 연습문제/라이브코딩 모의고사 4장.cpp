#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>

using namespace std;

class Container {
private:
	string title; // �����̳� Ÿ��Ʋ
	char* author; // �����̳� �ۼ��� �̸� (���� �Ҵ�)
	int size; // �����̳ʿ� ����� ���� �迭 ũ��
	int* arr; // ������ �����ϴ� �迭 (���� �Ҵ�)
public:
	void display();
	Container(string title, char* author,
		int size, int* arr);
	~Container();
	void replace_subtitle(string from, string to);
	void replace_first_last();
};

// ���⿡ Container Ŭ���� ��� �Լ����� ������ ��
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
	cout << "Container ������ ȣ��" << endl;
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
	cout << "Container �Ҹ��� ȣ��" << endl;
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

		// replace(���� �ε��� ��ġ, ����, ���ڿ�)
		// string.find("a") => string���ڿ����� a��� ���ڸ� ã�� �� �� �ε����� ��ȯ��
	}
	display();
}
int main() {
	string title("First title long title of title Last");
	char author[] = "Chosun Universty";
	int arr[5] = { 1, 2, 3, 4, 5 };
	Container c(title, author, 5, arr);
	cout << "���񿡼� \"title\" �ܾ \"name\" �ܾ�� ��� �ٲߴϴ�." << endl;
	c.replace_subtitle("title", "name");
	cout << "������ ù �ܾ�� ������ �ܾ��� ��ġ��  �ٲߴϴ�." << endl;
	c.replace_first_last();
}